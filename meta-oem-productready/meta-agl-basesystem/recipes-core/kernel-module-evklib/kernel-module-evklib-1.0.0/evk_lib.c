/*
 * drivers/agl/evk_lib.c
 *
 * Event library (kernel space part)
 *
 * @copyright Copyright (c) 2016-2019 TOYOTA MOTOR CORPORATION.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <generated/autoconf.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/list.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/vmalloc.h>

#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/device.h>
#include <linux/cdev.h>

#ifndef STANDARD_INT_DEFINITIONS
#define STANDARD_INT_DEFINITIONS
typedef __u8 UINT8;
typedef __u16 UINT16;
typedef __u32 UINT32;
typedef __u64 UINT64;
typedef __s8 INT8;
typedef __s16 INT16;
typedef __s32 INT32;
typedef __s64 INT64;
#endif /* !STANDARD_INT_DEFINITIONS */

#define ENABLE_PROC_FS 1

#include <agldd/evk_lib.h>

/** @addtogroup EV_in */
/** @{ */
/** In Linux2.4, list_for_each_entry is not provided, so it is prepared by self (in 2.6)
 */
#ifdef list_for_each_entry
#define __LINUX_26_OR_HIGHER
#endif

#ifndef __LINUX_26_OR_HIGHER /* linux v2.4 */

#define list_for_each_entry(pos, head, member)                          \
        for (pos = list_entry((head)->next, typeof(*pos), member),      \
                     prefetch(pos->member.next);                        \
             &pos->member != (head);                                    \
             pos = list_entry(pos->member.next, typeof(*pos), member),  \
                     prefetch(pos->member.next))

#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

#else /* linux v2.6 */

#include <linux/jiffies.h>

#endif /* linux v2.6 */

#define EVK_assert(cond, mesg) \
  if (!(cond)) { \
    printk(KERN_ALERT "[EVK]ASSERT(pid:%d): " #cond " at %s:%d; " \
      #mesg "\n", current->pid, __FILE__, __LINE__); \
    do {} while(1); \
  }

#define EVK_BUG(mesg) \
    printk(KERN_ALERT "[EVK]BUG: " mesg); \
    do {} while(1);

#if 0
#define EVK_info0(s) printk(KERN_ALERT "[EVK]INFO: " s)
#define EVK_info1(s, t) printk(KERN_ALERT "[EVK]INFO: " s, t)
#else
#define EVK_info0(s)
#define EVK_info1(s, t)
#endif

static int devmajor = EVK_DEV_MAJOR;
static int devminor = 0;
static int nrdevs = 1;
static struct cdev cdev;
static struct class *pClass;

DEFINE_SEMAPHORE(evk_mtx);
static int down_pid;
static int down_line;
#define EVK_mutex_lock() { \
  down(&evk_mtx); \
  down_pid = current->pid; \
  down_line = __LINE__; \
}
#define EVK_mutex_unlock() (up(&evk_mtx))

#ifdef EVK_USE_KMALLOC
#define evk_malloc(s) kmalloc((s), GFP_KERNEL)
#define evk_free kfree
#else // use vmalloc (this is the default)
#define evk_malloc(s) vmalloc((s))
#define evk_free vfree
#endif

enum {
  evk_mem_user = 0,
  evk_mem_kernel,
};

enum {
  evk_enum_flag,
  evk_enum_flag64,
  evk_enum_queue,
};

#define GET_USER_OR_KERNEL(to, from) \
({ \
  int err; \
  if (mem == evk_mem_user) { \
    err = __get_user((to), &(from)); \
  } else { \
    (to) = (from); \
    err = 0; \
  } \
  err; \
})

#define PUT_USER_OR_KERNEL(value, to) \
({ \
  int err; \
  if (mem == evk_mem_user) { \
    err = __put_user((value), &(to)); \
  } else { \
    (to) = (value); \
    err = 0; \
  } \
  err; \
})


/** @brief Common part of the flag structure and message queue structure */
#define EVK_COMMON_QUEUE_ELEMS						\
  struct list_head list;	/**< List structure */			\
  wait_queue_head_t wq_head;	/**< Wait_queue of a process waiting for a queue */\
  EV_ID queueID;		/**< Flag ID/Queue ID */		\
  UINT32 seq_num;		/**< Order of event arrival */		\
  pid_t read_pid;		/**< Read process ID */ \
  pid_t pid;			/**< Owning process ID */

/** @brief Common part of the flag structure and message queue structure */
struct common_queue {
  EVK_COMMON_QUEUE_ELEMS
};

/** @brief Flag structure */
struct flag {
  EVK_COMMON_QUEUE_ELEMS
  UINT32 value;/**< Flags value */
};
#define EVK_PFLAG(queue)	((struct flag*)queue)

/** @brief 64-bit flag structure */
struct flag64 {
  EVK_COMMON_QUEUE_ELEMS
  UINT64 value;/**< Flags value */
};
#define EVK_PFLAG64(queue)	((struct flag64*)queue)

/** @brief Message queue structure */
struct message_queue {
  EVK_COMMON_QUEUE_ELEMS
  UINT8 type;/**< Type */
  UINT8 length;/**< Queue length */
  UINT8 num;/**< Number of messages stored */
  UINT8 readptr;/**< Next read position(0~length-1) */
  UINT32 max_bytes;/**< -Maximum bytes per message */
  UINT8 *message;/**< Message storage area (ring buffer) */
};
#define EVK_PQUEUE(queue)	((struct message_queue*)queue)

/** @brief Number of bytes to allocate per message
 *
 * This function allocates an area to store the number of bytes actually stored, the time of occurrence, 
 * and the senderInfo, in addition to the number of bytes specified by max_bytes.
 */
#define EVK_message_block_size(max_bytes) (sizeof(UINT32) * 3 + (max_bytes))

#define HASH_KEY 15

/** @brief Maximum number of flags used by all systems */
#define EVK_MAX_FLAGS 48
/** @brief Maximum number of 64-bit flags used by all systems */
#define EVK_MAX_FLAG64S 4
/** @brief Maximum number of message event queues used by all systems */
/* M1SP BM3547 MESSAGE_QUEUES 128->144 */
/* M9AT BM2066 MESSAGE_QUEUES 144->218 */
#define EVK_MAX_MESSAGE_QUEUES 224

/** @brief Allocate flag structure statically */
static struct flag _flag_pool[EVK_MAX_FLAGS];
/** @brief Statically allocates a 64-bit flag structure */
static struct flag64 _flag64_pool[EVK_MAX_FLAG64S];
/** @brief Beginning of the list of unused flags */
static LIST_HEAD(flag_pool);
/** @brief Beginning of the list of unused 64-bit flags */
static LIST_HEAD(flag64_pool);

/** @brief Allocate message queue structure statically */
static struct message_queue _message_queue_pool[EVK_MAX_MESSAGE_QUEUES];
/** @brief Top of the list of unused message queues */
static LIST_HEAD(message_queue_pool);

/** @brief List of Flags/Message Queues in Use
 *
 * Connects the usage flag/message queue to a list for each hash value obtained from the ID.
 * The hash value is the remainder of the ID divided by HASH_KEY.
 */
static struct list_head queue_entry[HASH_KEY];

/** @brief Sequence number to use during automatic ID assignment */
static EV_ID sequence_id = 0;

/** @brief Number to be assigned in order of occurrence of the event */
static UINT32 sequence_number = 0;

unsigned int
evk_get_queue_entry(struct list_head **entries)
{
  if (entries) {
    *entries = queue_entry;
    return HASH_KEY;
  }
  return 0;
}

static __inline__ int
calc_hash(UINT32 val)
{
  return val % HASH_KEY;
}

static __inline__
struct flag *
alloc_flag(void)
{
  struct flag *queue;
  //EVK_assert(!list_empty(&flag_pool), "flag pool empty");
  if (list_empty(&flag_pool)) {
	printk("%s ERROR: flag pool empty\n", __func__);
	return NULL;
  }
  queue = (struct flag *)flag_pool.next;
  list_del_init(&(queue->list));
  return queue;
}

static __inline__
struct flag64 *
alloc_flag64(void)
{
  struct flag64 *queue;
  //EVK_assert(!list_empty(&flag64_pool), "flag64 pool empty");
  if (list_empty(&flag64_pool)) {
	printk("%s ERROR: flag64 pool empty\n", __func__);
	return NULL;
  }
  queue = (struct flag64 *)flag64_pool.next;
  list_del_init(&(queue->list));
  return queue;
}

static __inline__ void
free_flag(struct flag *queue)
{
  list_add((struct list_head *)queue, &flag_pool);
}

static __inline__ void
free_flag64(struct flag64 *queue)
{
  list_add((struct list_head *)queue, &flag64_pool);
}

static __inline__
struct message_queue *
alloc_message_queue(void)
{
  struct message_queue *queue;
  //EVK_assert(!list_empty(&message_queue_pool), "message queue pool empty");
  if (list_empty(&message_queue_pool)) {
	printk("%s ERROR: message queue pool empty\n", __func__);
	return NULL;
  }
  queue = (struct message_queue *)message_queue_pool.next;
  list_del_init(&(queue->list));
  queue->message = NULL;
  return queue;
}

static __inline__ void
free_message_queue(struct message_queue *queue)
{
  if (queue->message != NULL) {
    evk_free(queue->message);
    queue->message = NULL;
  }
  list_add((struct list_head *)queue, &message_queue_pool);
}

static __inline__
struct common_queue *
find_queue_entry(EV_ID queueID)
{
  struct list_head *list;
  struct common_queue *queue;
  int hash = calc_hash(queueID);
  list = &(queue_entry[hash]);
  list_for_each_entry(queue, list, list) {	/* pgr0060 */ /* pgr0039 */
    if (queue->queueID == queueID) {
      return queue;
    }
  }
  return NULL;
}

static __inline__ void
attach_queue_entry(struct common_queue *queue, EV_ID queueID)
{
  int hash = calc_hash(queueID);
  list_add_tail((struct list_head *)queue, &(queue_entry[hash]));
}

static __inline__ void
detach_queue_entry(struct common_queue *queue)
{
  list_del_init((struct list_head *)queue);
}

static __inline__ void
init_common_queue(struct common_queue *queue, EV_ID queueID)
{
  queue->queueID = queueID;
  queue->pid = current->pid;
  queue->read_pid = 0;
  init_waitqueue_head(&(queue->wq_head));
}

static __inline__ void
evk_init_flag(struct flag *queue, EV_ID queueID)
{
  init_common_queue((struct common_queue *)queue, queueID);
  queue->value = 0;
}

static __inline__ void
evk_init_flag64(struct flag64 *queue, EV_ID queueID)
{
  init_common_queue((struct common_queue *)queue, queueID);
  queue->value = 0;
}

static __inline__ int
evk_init_message_queue(struct message_queue *queue, EV_ID queueID,
			 UINT8 length, UINT32 max_bytes, UINT8 type)
{
  init_common_queue((struct common_queue *)queue, queueID);
  queue->type = type;
  queue->length = length;
  queue->max_bytes = max_bytes;
  queue->num = 0;
  queue->readptr = 0;
  EVK_assert(queue->message == NULL, "message buffer was not freed");
  queue->message = evk_malloc(length * EVK_message_block_size(max_bytes));
  EVK_assert(queue->message != NULL, "can't alloc message buffer");
  return 0;
}

static void
__list_queues(void)
{
  struct list_head *list;
  struct common_queue *queue;
  int i;
  for(i = 0 ; i < HASH_KEY ; i++) {
    list = &(queue_entry[i]);
    if (!list_empty(list)) {
      printk(KERN_ALERT "%d->", i);
      list_for_each_entry(queue, list, list) {	/* pgr0060 */ /* pgr0039 */
	printk("%x[%x] ", queue->queueID, queue->seq_num);
      }
      printk("\n");
    }
  }
}

static int
evk_destroy_queue(EV_ID queueID)
{
  struct common_queue *queue;
  int err = 0;
  EVK_info1("flag destroy %x\n", queueID);

  EVK_mutex_lock(); /*************************************/
  queue = find_queue_entry(queueID);
  if (queue == NULL) {
    err = -ENOENT;
    goto finish;
  }

  detach_queue_entry(queue);

  /* wake up processes before destruction */
  wake_up_interruptible(&(queue->wq_head));

  init_common_queue(queue, EV_INVALID_ID);

  if (EV_ID_IS_FLAG(queueID)) {
    free_flag((struct flag *)queue);
  } else if (EV_ID_IS_FLAG64(queueID)) {
    free_flag64((struct flag64 *)queue);
  } else if (EV_ID_IS_QUEUE(queueID)) {
    free_message_queue((struct message_queue *)queue);
  }
  //__list_queues();
 finish:
  EVK_mutex_unlock(); /*************************************/
  return err;
}

static int
evk_open(struct inode *inode, struct file *file)
{
  // Recording of current and measures not to be read or deleted from others are required. */
  file->private_data = (void *)EV_INVALID_ID;
  return 0;
}

static int
evk_close(struct inode *inode, struct file *file)
{
  if (EV_ID_IS_VALID((EV_ID)file->private_data)) {
    evk_destroy_queue((EV_ID)file->private_data);
  }
  file->private_data = (void *)EV_INVALID_ID;
  return 0;
}

static int
evk_create_flag(EV_ID queueID)
{
  struct flag *queue;
  int err = 0;
  EVK_info1("flag create %x\n", queueID);

  EVK_mutex_lock(); /*************************************/

  queue = (struct flag *)find_queue_entry(queueID);
  if (queue != NULL) {
    err = -EEXIST;
    goto finish;
  }

  queue = alloc_flag();
  if (queue == NULL) {
    err = -ENOMEM;
    goto finish;
  }

  evk_init_flag(queue, queueID);
  attach_queue_entry((struct common_queue *)queue, queueID);

  //__list_queues();
 finish:
  EVK_mutex_unlock(); /***********************************/
  return err;
}

static int
evk_create_flag64(EV_ID queueID)
{
  struct flag64 *queue;
  int err = 0;
  EVK_info1("flag64 create %x\n", queueID);

  EVK_mutex_lock(); /*************************************/

  queue = (struct flag64 *)find_queue_entry(queueID);
  if (queue != NULL) {
    err = -EEXIST;
    goto finish;
  }

  queue = alloc_flag64();
  if (queue == NULL) {
    err = -ENOMEM;
    goto finish;
  }

  evk_init_flag64(queue, queueID);
  attach_queue_entry((struct common_queue *)queue, queueID);

  //__list_queues();
 finish:
  EVK_mutex_unlock(); /***********************************/
  return err;
}

static int
evk_create_message_queue(EV_ID queueID, UINT8 length,
			   UINT32 max_bytes, EV_Message_Queue_Type type)
{
  struct message_queue *queue;
  int err;
  EVK_info1("message create %x\n", queueID);

  err = 0;

  EVK_mutex_lock(); /*************************************/

  queue = (struct message_queue *)find_queue_entry(queueID);
  if (queue != NULL) {
    err = -EEXIST;
    goto finish;
  }

  queue = alloc_message_queue();
  if (queue == NULL) {
    err = -ENOMEM;
    goto finish;
  }

  err = evk_init_message_queue(queue, queueID, length, max_bytes, type);
  if (err == 0) {
    attach_queue_entry((struct common_queue *)queue, queueID);
  } else {
    free_message_queue(queue);
  }

  //__list_queues();
 finish:
  EVK_mutex_unlock(); /***********************************/
  return err;
}

static EV_ID
get_seq_id(void)
{
  EV_ID ret;
  sequence_id++;
  if ((sequence_id & EV_RESERVED_BIT) != 0) {/* round to 1 */
    sequence_id = 1;
    EVK_info0("auto ID rounded\n");
  }
  ret = sequence_id;
  return ret;
}

static int
evk_alloc_flagID(EV_ID *queueID)
{
  EV_ID seq_id;

  EVK_mutex_lock(); /*************************************/
  do {
    seq_id = get_seq_id();
    seq_id |= (EV_ID_BIT | EV_FLAG_BIT | EV_AUTO_ID_BIT);
  } while(find_queue_entry(seq_id) != NULL);
  EVK_mutex_unlock(); /*************************************/

  *queueID = seq_id;
  return 0;
}

static int
evk_alloc_flag64ID(EV_ID *queueID)
{
  EV_ID seq_id;

  EVK_mutex_lock(); /*************************************/
  do {
    seq_id = get_seq_id();
    seq_id |= (EV_ID_BIT | EV_FLAG64_BIT | EV_AUTO_ID_BIT);
  } while(find_queue_entry(seq_id) != NULL);
  EVK_mutex_unlock(); /*************************************/

  *queueID = seq_id;
  return 0;
}

static int
evk_alloc_queueID(EV_ID *queueID)
{
  EV_ID seq_id;

  EVK_mutex_lock(); /*************************************/
  do {
    seq_id = get_seq_id();
    seq_id |= (EV_ID_BIT | EV_QUEUE_BIT | EV_AUTO_ID_BIT);
  } while(find_queue_entry(seq_id) != NULL);
  EVK_mutex_unlock(); /*************************************/

  *queueID = seq_id;
  return 0;
}

static int
evk_store_flag(EV_Flag *ev, int mem)
{
  struct flag *queue;
  int ret = 0;
  EV_ID flagID;
  UINT32 bits;

  if (GET_USER_OR_KERNEL(flagID, ev->flagID)) /* pgr0039 */
    return -EFAULT;
  if (GET_USER_OR_KERNEL(bits, ev->bits)) /* pgr0039 */
    return -EFAULT;

  EVK_mutex_lock(); /*************************************/

  queue = (struct flag *)find_queue_entry(flagID);	/* pgr0000 */
  if (queue == NULL) {
    EVK_info1("set_flag: No such ID %x\n", flagID);
    ret = -ENOENT;
    goto finish;
  }

  if (queue->value == 0) {
    queue->seq_num = sequence_number++;
  }
  queue->value |= bits;	/* pgr0000 */

  wake_up_interruptible(&(queue->wq_head));

 finish:
  EVK_mutex_unlock(); /***********************************/
  return ret;
}

static int
evk_store_flag64(EV_Flag64 *ev, int mem)
{
  struct flag64 *queue;
  int ret = 0;
  EV_ID flagID;
  UINT64 bits = 0;

  if (GET_USER_OR_KERNEL(flagID, ev->flagID)) /* pgr0039 */
    return -EFAULT;
  //GET_USER_OR_KERNEL(bits, ev->bits); /* pgr0039 */
  if (mem == evk_mem_user) {
    if (copy_from_user(&bits, &(ev->bits), sizeof(bits)))
      return -EFAULT;
  } else {
    bits = ev->bits;
  }

  EVK_mutex_lock(); /*************************************/

  queue = (struct flag64 *)find_queue_entry(flagID);	/* pgr0000 */
  if (queue == NULL) {
    EVK_info1("set_flag64: No such ID %x\n", flagID);
    ret = -ENOENT;
    goto finish;
  }

  if (queue->value == 0) {
    queue->seq_num = sequence_number++;
  }
  queue->value |= bits;	/* pgr0000 */

  wake_up_interruptible(&(queue->wq_head));

 finish:
  EVK_mutex_unlock(); /***********************************/
  return ret;
}

static int
evk_store_message(EV_Message *ev, int mem)
{
  struct message_queue *queue;
  UINT8 *ptr;
  UINT8 writeptr;
  int ret = 0;
  EV_ID queueID;
  UINT32 length, senderInfo, seq;

  if (GET_USER_OR_KERNEL(queueID, ev->queueID)) /* pgr0039 */
    return -EFAULT;
  if (GET_USER_OR_KERNEL(length, ev->length)) /* pgr0039 */
    return -EFAULT;
  if (GET_USER_OR_KERNEL(senderInfo, ev->senderInfo)) /* pgr0039 */
    return -EFAULT;

  EVK_mutex_lock(); /*************************************/

  queue = (struct message_queue *)find_queue_entry(queueID);	/* pgr0000 */
  if (queue == NULL) {
    EVK_info1("store_message: No such queueID %x\n", queueID);
    ret = -ENOENT;
    goto finish;
  }

  if (length > queue->max_bytes) {	/* pgr0000 */
    EVK_info0("store_message: message is too long for the queue");
    ret = -EINVAL;
    goto finish;
  }

  if (queue->num == queue->length) {

    switch(queue->type) {
    case EV_MESSAGE_QUEUE_TYPE_BUSY:
      EVK_info1("store_message: queue %x BUSY\n", queueID);
      ret = -EBUSY;
      goto finish;
      break;

    case EV_MESSAGE_QUEUE_TYPE_FIFO:
      queue->readptr++;
      queue->readptr %= queue->length;
      queue->num--;
      break;

    case EV_MESSAGE_QUEUE_TYPE_REPLACE:
      queue->num--;
      break;

    default:
      EVK_BUG("internal error in store_message\n");
      ret = -EINVAL;
      goto finish;
      break;
    }
  }

  writeptr = (queue->readptr + queue->num) % queue->length;
  ptr = queue->message + writeptr * EVK_message_block_size(queue->max_bytes);

  memcpy(ptr, &length, sizeof(length));
  ptr += sizeof(length);
  memcpy(ptr, &senderInfo, sizeof(senderInfo));
  ptr += sizeof(senderInfo);
  seq = sequence_number++;
  memcpy(ptr, &seq, sizeof(seq));
  ptr += sizeof(seq);

  if (queue->num == 0) {
    queue->seq_num = seq;
  }
  queue->num++;

  if (mem == evk_mem_user) {
    if (copy_from_user(ptr, ev->message, length)) {
      ret = -EFAULT;
      goto finish;
    }
  } else {
    memcpy(ptr, ev->message, length);
  }

  wake_up_interruptible(&(queue->wq_head));

 finish:
  EVK_mutex_unlock(); /***********************************/

  return ret;
}

static int
evk_set_poll(struct file *filp, EV_ID queueID)
{
  struct common_queue *queue;
  int err = 0;

  EVK_mutex_lock(); /*************************************/

  queue = find_queue_entry(queueID);
  if (queue == NULL) {
    EVK_info1("set_poll: ID %x not found.\n", queueID);
    err = -ENOENT;
    goto finish;
  }

  filp->private_data = (void *)queueID;

 finish:
  EVK_mutex_unlock(); /*************************************/
  return err;
}

static int
evk_get_flag_event(EV_Event *ev, int peek_only, int wait, int mem)
{
  struct flag *queue, *queue2;
  int err = 0;
  int found = 0;
  EV_ID flagID;

  if (GET_USER_OR_KERNEL(flagID, ev->u.flag.flagID)) /* pgr0039 */
    return -EFAULT;

 retry:

  queue = (struct flag *)find_queue_entry(flagID);	/* pgr0000 */
  if (queue == NULL) {
    EVK_info1("get_flag: No such flag %x\n", flagID);
    err = -ENOENT;
    goto finish;
  }

  if (queue->value != 0) {
    UINT32 bits;

    if (GET_USER_OR_KERNEL(bits, ev->u.flag.bits)) { /* pgr0039 */
      err = -EFAULT;
      goto finish;
    }

    if (bits == 0 || ((bits & queue->value) != 0)) {	/* pgr0000 */

      if (PUT_USER_OR_KERNEL(EV_EVENT_Flag, ev->type)) { /* pgr0039 */
	err = -EFAULT;
	goto finish;
      }
      if (PUT_USER_OR_KERNEL(queue->value, ev->u.flag.bits)) { /* pgr0039 */
	err = -EFAULT;
	goto finish;
      }
      found = 1;

      queue->read_pid = current->pid;
      if (peek_only) {
	;
      } else {
	queue->value = 0;
      }
    }
  }
 finish:

  if (queue != NULL && wait != 0 && found == 0) {
    int wait_ret;
    EVK_mutex_unlock(); /*************************************/

    wait_ret
      = wait_event_interruptible(queue->wq_head,
				 ((queue2 = (struct flag *)find_queue_entry(flagID)) == NULL
				  || queue2->value != 0));

    EVK_mutex_lock(); /*************************************/

    if (wait_ret != 0) {
      EVK_info1("Interrupted while waiting for flag %x\n", flagID);
      err = -EINTR;
    } else if (queue2 == NULL) { /* pgr0039 */
      EVK_info1("flag %x was destroyed while waiting for it\n", flagID);
      err = -ENOENT;
    } else {
      goto retry;
    }
  }
  return err;
}

static int
evk_get_flag64_event(EV_Event *ev, int peek_only, int wait, int mem)
{
  struct flag64 *queue, *queue2;
  int err = 0;
  int found = 0;
  EV_ID flagID;

  if (GET_USER_OR_KERNEL(flagID, ev->u.flag64.flagID)) /* pgr0039 */
    return -EFAULT;

 retry:

  queue = (struct flag64 *)find_queue_entry(flagID);	/* pgr0000 */
  if (queue == NULL) {
    EVK_info1("get_flag64: No such flag %x\n", flagID);
    err = -ENOENT;
    goto finish;
  }

  if (queue->value != 0) {
    UINT64 bits = 0;

    //GET_USER_OR_KERNEL(bits, ev->u.flag64.bits); /* pgr0039 */
    if (mem == evk_mem_user) {
      if (copy_from_user(&bits, &(ev->u.flag64.bits), sizeof(bits))) {
	err = -EFAULT;
	goto finish;
      }
    } else {
      bits = ev->u.flag64.bits;
    }

    if (bits == 0 || ((bits & queue->value) != 0)) {	/* pgr0000 */

      if (PUT_USER_OR_KERNEL(EV_EVENT_Flag64, ev->type)) { /* pgr0039 */
	err = -EFAULT;
	goto finish;
      }
      if (PUT_USER_OR_KERNEL(queue->value, ev->u.flag64.bits)) { /* pgr0039 */
	err = -EFAULT;
	goto finish;
      }
      found = 1;

      queue->read_pid = current->pid;
      if (peek_only) {
	;
      } else {
	queue->value = 0;
      }
    }
  }
 finish:

  if (queue != NULL && wait != 0 && found == 0) {
    int wait_ret;
    EVK_mutex_unlock(); /*************************************/

    wait_ret
      = wait_event_interruptible(queue->wq_head,
				 ((queue2 = (struct flag64 *)find_queue_entry(flagID)) == NULL
				  || queue2->value != 0));

    EVK_mutex_lock(); /*************************************/

    if (wait_ret != 0) {
      EVK_info1("Interrupted while waiting for flag %x\n", flagID);
      err = -EINTR;
    } else if (queue2 == NULL) { /* pgr0039 */
      EVK_info1("flag %x was destroyed while waiting for it\n", flagID);
      err = -ENOENT;
    } else {
      goto retry;
    }
  }
  return err;
}

static __inline__ void
remove_message_event(struct message_queue *queue, UINT8 removeptr)
{
  UINT8 *ptr;
  int i, from, to;
  UINT8 *pFrom, *pTo;
  UINT32 size;
  int offset;

  queue->num--;
  offset = (int)removeptr - (int)(queue->readptr);

  if (offset == 0) {/* To remove the head of the queue, advance the queue by one readptr only */
    queue->readptr++;
    queue->readptr %= queue->length;

    if (queue->num > 0) {
      /* Reset the occurrence time of the first message in the queue to the occurrence time of the queue. */
      ptr = (queue->message
	     + queue->readptr * EVK_message_block_size(queue->max_bytes));
      ptr += sizeof(UINT32) * 2;
      memcpy(&(queue->seq_num), ptr, sizeof(UINT32));
    }
    return;
  }
  if (offset < 0) {
    offset += queue->length;
  }
  if (offset == queue->num) {/* Do nothing to delete the end of the queue */
    return;
  }

  /* To delete a message in the middle of the queue, pack the following messages. */
  to = removeptr;
  size = EVK_message_block_size(queue->max_bytes);

  for(i = 0 ; i < queue->num - offset ; i++, to++) {
    to %= queue->length;
    from = (to + 1) % queue->length;
    pFrom = queue->message + from * size;
    pTo = queue->message + to * size;
    memcpy(pTo, pFrom, size);
  }
}

static int
evk_get_message_event(EV_Event *ev, int peek_only, int wait, int mem)
{
  struct message_queue *queue, *queue2;
  int err = 0;
  EV_ID queueID;
  UINT8 num;
  UINT8 readptr;
  UINT8 i, *ptr;
  int matched = 0;

  if (GET_USER_OR_KERNEL(queueID, ev->u.message.queueID)) /* pgr0039 */
    return -EFAULT;

 retry:
  queue = (struct message_queue *)find_queue_entry(queueID);	/* pgr0000 */
  if (queue == NULL) {
    EVK_info1("get_message: No such queue %x\n", queueID);
    err = -ENOENT;
    goto finish;
  }

  num = queue->num;
  readptr = queue->readptr;
  for(i = 0 ; i < num ; i++, readptr = (readptr + 1) % queue->length) {
    UINT32 size, senderInfo, seq;
    UINT32 length, q_senderInfo;

    ptr = (queue->message
	   + readptr * EVK_message_block_size(queue->max_bytes));

    memcpy(&size, ptr, sizeof(size));
    ptr += sizeof(size);
    memcpy(&senderInfo, ptr, sizeof(senderInfo));
    ptr += sizeof(senderInfo);
    memcpy(&seq, ptr, sizeof(seq));
    ptr += sizeof(seq);

    if (GET_USER_OR_KERNEL(length, ev->u.message.length)) { /* pgr0039 */
      err = -EFAULT;
      goto finish;
    }
    if (GET_USER_OR_KERNEL(q_senderInfo, ev->u.message.senderInfo)) { /* pgr0039 */
      err = -EFAULT;
      goto finish;
    }

    if (q_senderInfo == 0 && length == 0) {	/* pgr0000 */
      matched = 1;
    } else if (q_senderInfo != 0 && q_senderInfo == senderInfo) {
      matched = 1;
    } else if (length > 0 && size >= length) {	/* pgr0000 */

      if (mem == evk_mem_user) {
	void *compbytes;
	compbytes = evk_malloc(length);
	if (compbytes != NULL) {
	  if (copy_from_user(compbytes, &(ev->u.message.message), length)) {
	    err = -EFAULT;
	    evk_free(compbytes);
	    goto finish;
	  }
	  if (memcmp(ptr, compbytes, length) == 0) {
	    matched = 1;
	  }
	  evk_free(compbytes);
	}
      } else {
	if (memcmp(ptr, ev->u.message.message, length) == 0) {
	  matched = 1;
	}
      }
    }

    if (matched) {

      if (PUT_USER_OR_KERNEL(EV_EVENT_Message, ev->type)) { /* pgr0039 */
	err = -EFAULT;
	goto finish;
      }
      if (PUT_USER_OR_KERNEL(size, ev->u.message.length)) { /* pgr0039 */
	err = -EFAULT;
	goto finish;
      }
      if (PUT_USER_OR_KERNEL(senderInfo, ev->u.message.senderInfo)) { /* pgr0039 */
	err = -EFAULT;
	goto finish;
      }
      if (mem == evk_mem_user) {
	if (copy_to_user(ev->u.message.message, ptr, size)) {
	  err = -EFAULT;
	  goto finish;
	}
      } else {
	memcpy(ev->u.message.message, ptr, size);
      }

      queue->read_pid = current->pid;
      if (peek_only) {
	;
      } else {
	remove_message_event(queue, readptr);
      }
      goto finish;
    }
  }

 finish:

  if (queue != NULL && wait != 0 && matched == 0) {
    int wait_ret;
    EVK_mutex_unlock(); /*************************************/
    wait_ret
      = wait_event_interruptible(queue->wq_head,
				 ((queue2 = (struct message_queue *)find_queue_entry(queueID))==NULL
				  || queue2->num > 0));

    EVK_mutex_lock(); /*************************************/

    if (wait_ret != 0) {
      EVK_info1("Interrupted while waiting for queue %x\n", queueID);
      err = -EINTR;
    } else if (queue2 == NULL) { /* pgr0039 */
      EVK_info1("queue %x was destroyed while waiting for it\n", queueID);
      err = -ENOENT;
    } else {
      goto retry;
    }
  }

  return err;
}

static int
evk_get_event(EV_Event *ev, int peek_only, int wait, int mem)
{
  EV_Type type;
  int ret = -EINVAL;

  if (GET_USER_OR_KERNEL(type, ev->type)) /* pgr0039 */
    return -EFAULT;
  if (PUT_USER_OR_KERNEL(EV_EVENT_None, ev->type)) /* pgr0039 */
    return -EFAULT;

  switch(type) {	/* pgr0000 */
  case EV_EVENT_Flag:
    EVK_mutex_lock(); /*************************************/
    ret = evk_get_flag_event(ev, peek_only, wait, mem);
    EVK_mutex_unlock(); /*************************************/
    break;

  case EV_EVENT_Flag64:
    EVK_mutex_lock(); /*************************************/
    ret = evk_get_flag64_event(ev, peek_only, wait, mem);
    EVK_mutex_unlock(); /*************************************/
    break;

  case EV_EVENT_Message:
    EVK_mutex_lock(); /*************************************/
    ret = evk_get_message_event(ev, peek_only, wait, mem);
    EVK_mutex_unlock(); /*************************************/
    break;

  default:
    break;
  }
  return ret;
}

static int
evk_get_next_event(EVK_Next_Event_Query *query /* user */, int peek_only)
{
  EV_ID *ids;
  int i, num, ret, first, found;
  struct common_queue *queue;
  UINT32 seq_oldest = 0;

  ids = (EV_ID *)kmalloc( (sizeof(EV_ID)*EV_MAX_IDS_IN_PROCESS), GFP_KERNEL );
  if( ids == NULL ){
    return -ENOMEM;
  }

  if (__get_user(num, &(query->num))) { /* pgr0039 */
    ret = -EFAULT;
    goto finish0;
  }
  if (copy_from_user(&ids[0], query->ids, num * sizeof(EV_ID))) { /* pgr0039 */
    ret = -EFAULT;
    goto finish0;
  }
  if (__put_user(EV_EVENT_None, &(query->ev.type))) { /* pgr0039 */
    ret = -EFAULT;
    goto finish0;
  }

  ret = 0;
  first = 1;
  found = -1;

  EVK_mutex_lock(); /*************************************/

  for(i = 0 ; i < num /* pgr0039 */ ; i++) {
    queue = find_queue_entry(ids[i]);
    if (queue != NULL) {/* Have the specified queue ID */
      if ((EV_ID_IS_FLAG(ids[i])
	   && ((struct flag *)queue)->value != 0)
	  || (EV_ID_IS_FLAG64(ids[i])
	   && ((struct flag64 *)queue)->value != 0)
	  || (EV_ID_IS_QUEUE(ids[i])
	      && ((struct message_queue *)queue)->num > 0)) {/*There are events.*/
	/* Compare with time_before macros for round 0 */
	if (first || time_before((unsigned long)queue->seq_num,	/* pgr0006 */ /* pgr0039 */
				 (unsigned long)seq_oldest)) {
	  first = 0;
	  seq_oldest = queue->seq_num;
	  found = i;
	}
      }
    }
  }

  if (found >= 0) {
    if (EV_ID_IS_FLAG(ids[found])) {
      if (__put_user(ids[found], &(query->ev.u.flag.flagID))) { /* pgr0039 */
	ret = -EFAULT;
	goto finish1;
      }
      ret = evk_get_flag_event(&(query->ev), peek_only, 0, evk_mem_user);
    } else if (EV_ID_IS_FLAG64(ids[found])) {
      if (__put_user(ids[found], &(query->ev.u.flag64.flagID))) { /* pgr0039 */
	ret = -EFAULT;
	goto finish1;
      }
      ret = evk_get_flag64_event(&(query->ev), peek_only, 0, evk_mem_user);
    } else if (EV_ID_IS_QUEUE(ids[found])) {
      if (__put_user(ids[found], &(query->ev.u.message.queueID))) { /* pgr0039 */
	ret = -EFAULT;
	goto finish1;
      }
      ret = evk_get_message_event(&(query->ev), peek_only, 0, evk_mem_user);
    }
  }

 finish1:
  EVK_mutex_unlock(); /*************************************/
 finish0:
  kfree(ids);
  return ret;
}

static long
evk_ioctl(struct file *filp, unsigned int cmd,
	    unsigned long arg)
{
  EVK_Message_Queue_Request mesq;
  int peek_only, wait;
  EV_ID queueID;
  int ret = -EINVAL;

  //lock_kernel();

  switch(cmd) {
  case EVK_IOC_CREATE_FLAG:
    queueID = (EV_ID)arg;
    ret = evk_create_flag(queueID);
    break;

  case EVK_IOC_CREATE_FLAG64:
    queueID = (EV_ID)arg;
    ret = evk_create_flag64(queueID);
    break;

  case EVK_IOC_CREATE_MESSAGE_QUEUE:
    if (access_ok(VERIFY_READ, arg, sizeof(mesq))) { /* pgr0039 */
      if (copy_from_user(&mesq, (EV_Flag *)arg, sizeof(mesq))) {
	ret = -EFAULT;
	break;
      }

      ret = evk_create_message_queue(mesq.queueID, mesq.length,
				     mesq.max_bytes, mesq.type);
    } else {
      ret = -EFAULT;
    }
    break;

  case EVK_IOC_ALLOC_FLAG_ID:
    if (access_ok(VERIFY_WRITE, arg, sizeof(queueID))) { /* pgr0039 */
      evk_alloc_flagID(&queueID);
      if (put_user(queueID, (EV_ID *)arg)) { /* pgr0039 */
	ret = -EFAULT;
	break;
      }
      ret = 0;
    } else {
      ret = -EFAULT;
    }
    break;

  case EVK_IOC_ALLOC_FLAG64_ID:
    if (access_ok(VERIFY_WRITE, arg, sizeof(queueID))) { /* pgr0039 */
      evk_alloc_flag64ID(&queueID);
      if (put_user(queueID, (EV_ID *)arg)) { /* pgr0039 */
	ret = -EFAULT;
	break;
      }
      ret = 0;
    } else {
      ret = -EFAULT;
    }
    break;

  case EVK_IOC_ALLOC_QUEUE_ID:
    if (access_ok(VERIFY_WRITE, arg, sizeof(queueID))) { /* pgr0039 */
      evk_alloc_queueID(&queueID);
      if (put_user(queueID, (EV_ID *)arg)) { /* pgr0039 */
	ret = -EFAULT;
	break;
      }
      ret = 0;
    } else {
      ret = -EFAULT;
    }
    break;

  case EVK_IOC_DESTROY_QUEUE:
    queueID = (EV_ID)arg;
    ret = evk_destroy_queue(queueID);
    break;

  case EVK_IOC_STORE_FLAG:
    if (access_ok(VERIFY_READ, arg, sizeof(EV_Flag))) { /* pgr0039 */
      ret = evk_store_flag((EV_Flag *)arg, evk_mem_user);
    } else {
      ret = -EFAULT;
    }
    break;

  case EVK_IOC_STORE_FLAG64:
    if (access_ok(VERIFY_READ, arg, sizeof(EV_Flag64))) { /* pgr0039 */
      ret = evk_store_flag64((EV_Flag64 *)arg, evk_mem_user);
    } else {
      ret = -EFAULT;
    }
    break;

  case EVK_IOC_STORE_MESSAGE:
    if (access_ok(VERIFY_READ, arg, sizeof(EV_Message))) { /* pgr0039 */
      ret = evk_store_message((EV_Message *)arg, evk_mem_user);
    } else {
      ret = -EFAULT;
    }
    break;

  case EVK_IOC_SET_POLL:
    queueID = (EV_ID)arg;
    ret = evk_set_poll(filp, queueID);
    break;

  case EVK_IOC_PEEK_EVENT:
    peek_only = 1;
    wait = 0;
    goto get_event;
    break;

  case EVK_IOC_WAIT_EVENT:
    peek_only = 0;
    wait = 1;
    goto get_event;
    break;

  case EVK_IOC_GET_EVENT:
    peek_only = 0;
    wait = 0;
  get_event:
    if (access_ok(VERIFY_WRITE, arg, sizeof(EV_Event))) { /* pgr0039 */
      ret = evk_get_event((EV_Event *)arg, peek_only, wait, evk_mem_user);
    } else {
      ret = -EFAULT;
    }
    break;

  case EVK_IOC_PEEK_NEXT_EVENT:
    peek_only = 1;
    goto get_next;
    break;

  case EVK_IOC_GET_NEXT_EVENT:
    peek_only = 0;
  get_next:
    if (access_ok(VERIFY_WRITE, arg, sizeof(EVK_Next_Event_Query))) { /* pgr0039 */
      ret = evk_get_next_event((EVK_Next_Event_Query *)arg, peek_only);
    } else {
      ret = -EFAULT;
    }
    break;

  case EVK_IOC_DEBUG_LIST:
    __list_queues();
    //__list_message();
    ret = 0;
    break;

  default:
    ret = -EINVAL;
    break;
  }

  //unlock_kernel();
  return ret;
}

static unsigned int
evk_poll(struct file *filp, poll_table *wait)
{
  unsigned int ret = 0;
  struct common_queue *queue;

  EV_ID queueID = (EV_ID)(filp->private_data);
  // Returns errors without stopping at assert if queueID is invalid
  // (Troubleshooting for Continuous Printing)
  if (!EV_ID_IS_VALID(queueID)) {
    printk("evk_poll ERROR: invalid queueID=%x\n", queueID);
    return POLLERR|POLLHUP;
  }
  //EVK_assert(EV_ID_IS_VALID(queueID), "poll: flag/queueID not set");

  EVK_mutex_lock();/*****************************************/

  queue = find_queue_entry(queueID);
  if (queue == NULL) {
    EVK_info1("poll: No such flag/queueID %x\n", queueID);
    ret = POLLERR|POLLHUP;
    goto finish;
  }

  poll_wait(filp, &(queue->wq_head), wait);

  if (EV_ID_IS_FLAG(queueID)) {
    if (((struct flag *)queue)->value != 0) {
      ret = POLLIN;
    }
  } else if (EV_ID_IS_FLAG64(queueID)) {
    if (((struct flag64 *)queue)->value != 0) {
      ret = POLLIN;
    }
  } else {
    if (((struct message_queue *)queue)->num > 0) {
      ret = POLLIN;
    }
  }

 finish:
  EVK_mutex_unlock(); /***************************************/

  return ret;
}

/** List of system call corresponding function registrations */
static struct file_operations evk_fops = {
  .open           = evk_open,
  .release        = evk_close,
  .unlocked_ioctl = evk_ioctl,
  .poll           = evk_poll,
};

#ifdef ENABLE_PROC_FS
static int
evk_procFS_show(struct seq_file *m, int mode)
{
  int i, num;
  struct list_head *list, *entries;
  struct common_queue *queue;

  seq_printf(m, "[ev library status ");

  switch(mode) {
  case evk_enum_flag:
    seq_printf(m, "(flag)]\n");
    seq_printf(m, "PID      moduleID    flagID[hash]   value\n");
    break;
  case evk_enum_flag64:
    seq_printf(m, "(flag64)]\n");
    seq_printf(m, "PID      moduleID     flagID[hash]   value\n");
    break;
  case evk_enum_queue:
    seq_printf(m, "(queue)]\n");
    seq_printf(m, "PID      moduleID    queueID[hash]  maxbytes remain type\n");
    break;
  }

  EVK_mutex_lock();

  num = evk_get_queue_entry(&entries);

  for (i = 0 ; i < num ; i++) {
    list = &(entries[i]);
    if (!list_empty(list)) {
      list_for_each_entry(queue, list, list) {
	if ((mode == evk_enum_flag && (!EV_ID_IS_FLAG(queue->queueID)))
	    || (mode == evk_enum_flag64 && (!EV_ID_IS_FLAG64(queue->queueID)))
	    || (mode == evk_enum_queue && (!EV_ID_IS_QUEUE(queue->queueID))))
	{
	  continue;
	}

	seq_printf(m, "%08d ", queue->pid);
	seq_printf(m, "%05d(%04x) ", ((queue->queueID & 0x00ffff00) >> 8), ((queue->queueID & 0x00ffff00) >> 8));
	seq_printf(m, "0x%08x[%2d] ", queue->queueID, calc_hash(queue->queueID));

	switch(mode) {
	case evk_enum_flag:
          seq_printf(m, "0x%x", EVK_PFLAG(queue)->value);
	  break;

	case evk_enum_flag64:
          seq_printf(m, "0x%llx", EVK_PFLAG64(queue)->value);
	  break;

	case evk_enum_queue:
          seq_printf(m, "%04d %02d  ", EVK_PQUEUE(queue)->max_bytes, EVK_PQUEUE(queue)->length);
          seq_printf(m, "%02d     ", EVK_PQUEUE(queue)->num);
          seq_printf(m, "%d    ", EVK_PQUEUE(queue)->type);
	  break;
        }
        seq_printf(m, "\n");
      }
    }
  }

  EVK_mutex_unlock();
  return 0;
}

static int
evk_procFS_flag_show(struct seq_file *m, void *v)
{
  return evk_procFS_show(m, evk_enum_flag);
}

static int
evk_procFS_flag64_show(struct seq_file *m, void *v)
{
  return evk_procFS_show(m, evk_enum_flag64);
}

static int
evk_procFS_queue_show(struct seq_file *m, void *v)
{
  return evk_procFS_show(m, evk_enum_queue);
}

static int
evk_procFS_flag_open(struct inode *inode, struct file *file)
{
  return single_open(file, evk_procFS_flag_show, NULL);
}

static int
evk_procFS_flag64_open(struct inode *inode, struct file *file)
{
  return single_open(file, evk_procFS_flag64_show, NULL);
}

static int
evk_procFS_queue_open(struct inode *inode, struct file *file)
{
  return single_open(file, evk_procFS_queue_show, NULL);
}

static struct file_operations evk_proc_flag_fops = {
  .owner   = THIS_MODULE,
  .open    = evk_procFS_flag_open,
  .read    = seq_read,
  .llseek  = seq_lseek,
  .release = single_release,
};

static struct file_operations evk_proc_flag64_fops = {
  .owner   = THIS_MODULE,
  .open    = evk_procFS_flag64_open,
  .read    = seq_read,
  .llseek  = seq_lseek,
  .release = single_release,
};

static struct file_operations evk_proc_queue_fops = {
  .owner   = THIS_MODULE,
  .open    = evk_procFS_queue_open,
  .read    = seq_read,
  .llseek  = seq_lseek,
  .release = single_release,
};
#endif /*ENABLE_PROC_FS*/

__init int
EVK_init(void)
{
  int err;
#ifdef CONFIG_PROC_FS
#ifdef ENABLE_PROC_FS
  struct proc_dir_entry *ret;
#endif /* ENABLE_PROC_FS */
#endif /* CONFIG_PROC_FS */
  int i;
  dev_t dev;

  dev = MKDEV(devmajor, devminor);
  err = register_chrdev_region(dev, nrdevs, EVK_NAME);
  if (err) {
    EVK_info1("register_chrdev_region error %d\n",  -err);
    return -EBUSY;
  }

  cdev_init(&cdev, &evk_fops);
  cdev.owner = THIS_MODULE;
  cdev.ops = &evk_fops;

  err = cdev_add(&cdev, dev, 1);
  if (err) {
    EVK_info1("cdev_add error %d\n", -err);
    return -EBUSY;
  }

  /* Initialization */
  for(i = 0 ; i < EVK_MAX_FLAGS ; i++) {
    list_add_tail((struct list_head *)&(_flag_pool[i]),
		  &flag_pool);
  }
  for(i = 0 ; i < EVK_MAX_FLAG64S ; i++) {
    list_add_tail((struct list_head *)&(_flag64_pool[i]),
		  &flag64_pool);
  }
  for(i = 0 ; i < EVK_MAX_MESSAGE_QUEUES ; i++) {
    list_add_tail((struct list_head *)&(_message_queue_pool[i]),
		  &message_queue_pool);
  }
  for(i = 0 ; i < HASH_KEY ; i++) {
    INIT_LIST_HEAD(&(queue_entry[i]));
  }

#ifdef CONFIG_PROC_FS
#ifdef ENABLE_PROC_FS
  ret = proc_create("driver/ev_flag", 0, NULL, &evk_proc_flag_fops);
  if( ret == NULL ) {
    EVK_info1("Unable to initialize /proc entry %d\n",  -err);
    return -EBUSY;
  }

  ret = proc_create("driver/ev_flag64", 0, NULL, &evk_proc_flag64_fops);
  if( ret == NULL ) {
    EVK_info1("Unable to initialize /proc entry %d\n",  -err);
    return -EBUSY;
  }

  ret = proc_create("driver/ev_queue", 0, NULL, &evk_proc_queue_fops);
  if( ret == NULL ) {
    EVK_info1("Unable to initialize /proc entry %d\n",  -err);
    return -EBUSY;
  }
#endif /* ENABLE_PROC_FS */
#endif /* CONFIG_PROC_FS */

  pClass = class_create(THIS_MODULE, EVK_NAME);
  device_create(pClass, NULL, dev, NULL, "agl/"EVK_NAME);

  return 0;
}

void
//#ifndef CONFIG_COMBINE_MODULES
//__exit
//#endif
EVK_exit(void)
{
  dev_t dev = MKDEV(devmajor, devminor);
  device_destroy(pClass, dev);
  class_destroy(pClass);

  cdev_del(&cdev);

  unregister_chrdev_region(dev, nrdevs);

  remove_proc_entry( "driver/ev_flag", 0 );
  remove_proc_entry( "driver/ev_flag64", 0 );
  remove_proc_entry( "driver/ev_queue", 0 );
}

/** @} */
/** @addtogroup EV
 * @{ */
static EV_ERR
EVK_create_flag_in(EV_ID flagID)
{
  int ret = evk_create_flag(flagID);

  if (ret == -EEXIST) {
    return EV_ERR_Exist;
  } else if (ret < 0) {
    return EV_ERR_Fatal;
  } else {
    return EV_OK;
  }
}

static EV_ERR
EVK_create_flag64_in(EV_ID flagID)
{
  int ret = evk_create_flag64(flagID);

  if (ret == -EEXIST) {
    return EV_ERR_Exist;
  } else if (ret < 0) {
    return EV_ERR_Fatal;
  } else {
    return EV_OK;
  }
}

/** @see EV_create_flag */
EV_ERR
EVK_create_flag(EV_ID flagID)
{
  if (!EV_ID_IS_FLAG(flagID) || EV_ID_IS_AUTO_ID(flagID)) {
    return EV_ERR_Invalid_ID;
  }
  return EVK_create_flag_in(flagID);
}

/** @see EV_create_flag64 */
EV_ERR
EVK_create_flag64(EV_ID flagID)
{
  if (!EV_ID_IS_FLAG64(flagID) || EV_ID_IS_AUTO_ID(flagID)) {
    return EV_ERR_Invalid_ID;
  }
  return EVK_create_flag64_in(flagID);
}

static EV_ERR
EVK_create_queue_in(EV_ID queueID, UINT8 length, UINT16 max_bytes,
		    EV_Message_Queue_Type type)
{
  int ret = evk_create_message_queue(queueID, length, max_bytes, type);

  if (ret == -EEXIST) {
    return EV_ERR_Exist;
  } else if (ret < 0) {
    return EV_ERR_Fatal;
  } else {
    return EV_OK;
  }
}

/** @see EV_create_queue */
EV_ERR
EVK_create_queue(EV_ID queueID, UINT8 length, UINT16 max_bytes,
		 EV_Message_Queue_Type type)
{
  if (!EV_ID_IS_QUEUE(queueID) || EV_ID_IS_AUTO_ID(queueID)) {
    return EV_ERR_Invalid_ID;
  }
  return EVK_create_queue_in(queueID, length, max_bytes, type);
}

/** @see EV_create_flag_auto_id */
EV_ERR
EVK_create_flag_auto_id(/* OUT */EV_ID *flagID)
{
  EV_ERR err;
  EVK_assert(flagID != NULL, "NULL pointer was specified");

  if (evk_alloc_flagID(flagID) < 0) {
    return EV_ERR_Fatal;
  }

  err = EVK_create_flag_in(*flagID);
  if (err != EV_OK) {
    *flagID = EV_NO_ID;
  }
  return err;
}

/** @see EV_create_flag64_auto_id */
EV_ERR
EVK_create_flag64_auto_id(/* OUT */EV_ID *flagID)
{
  EV_ERR err;
  EVK_assert(flagID != NULL, "NULL pointer was specified");

  if (evk_alloc_flag64ID(flagID) < 0) {
    return EV_ERR_Fatal;
  }

  err = EVK_create_flag64_in(*flagID);
  if (err != EV_OK) {
    *flagID = EV_NO_ID;
  }
  return err;
}

/** @see EV_create_queue_auto_id */
EV_ERR
EVK_create_queue_auto_id(/* OUT */EV_ID *queueID, UINT8 length,
			 UINT16 max_bytes, EV_Message_Queue_Type type)
{
  EV_ERR err;
  EVK_assert(queueID != NULL, "NULL pointer was specified");

  if (evk_alloc_queueID(queueID) < 0) {
    return EV_ERR_Fatal;
  }

  err = EVK_create_queue_in(*queueID, length, max_bytes, type);
  if (err != EV_OK) {
    *queueID = EV_NO_ID;
  }
  return err;
}

/** @see EV_destroy_flag */
EV_ERR
EVK_destroy_flag(EV_ID flagID)
{
  int err;
  err = evk_destroy_queue(flagID);

  if (err == -ENOENT) {
    return EV_ERR_Invalid_ID;
  } else if (err < 0) {
    return EV_ERR_Fatal;
  } else {
    return EV_OK;
  }
}

/** @see EV_destroy_queue */
EV_ERR
EVK_destroy_queue(EV_ID queueID)
{
  return EVK_destroy_flag(queueID);
}

/* Sending the event */
/** @see EV_set_flag */
EV_ERR
EVK_set_flag(EV_ID flagID, UINT32 bits)
{
  EV_Flag flag;
  int ret;

  if (!EV_ID_IS_FLAG(flagID)) {
    return EV_ERR_Invalid_ID;
  }
  flag.flagID = flagID;
  flag.bits = bits;

  ret = evk_store_flag(&flag, evk_mem_kernel);
  if (ret == -ENOENT) {
    return EV_ERR_Invalid_ID;
  } else if (ret < 0) {
    return EV_ERR_Fatal;
  } else {
    return EV_OK;
  }
}

/** @see EV_set_flag64 */
EV_ERR
EVK_set_flag64(EV_ID flagID, UINT64 bits)
{
  EV_Flag64 flag;
  int ret;

  if (!EV_ID_IS_FLAG64(flagID)) {
    return EV_ERR_Invalid_ID;
  }
  flag.flagID = flagID;
  flag.bits = bits;

  ret = evk_store_flag64(&flag, evk_mem_kernel);
  if (ret == -ENOENT) {
    return EV_ERR_Invalid_ID;
  } else if (ret < 0) {
    return EV_ERR_Fatal;
  } else {
    return EV_OK;
  }
}

/** @see EV_send_message */
EV_ERR
EVK_send_message(EV_ID queueID, UINT16 bytes, const void *message,
		 UINT32 senderInfo)
{
  EV_Message *msg = NULL;
  EV_ERR ev_ret;
  int ret;

  msg = evk_malloc( sizeof( EV_Message ) );
  if( msg == NULL )
  {
    ev_ret = EV_ERR_Fatal;
    goto L_END;
  }

  if (!EV_ID_IS_QUEUE(queueID)) {
    ev_ret = EV_ERR_Invalid_ID;
    goto L_END;
  }
  EVK_assert(message != NULL, "NULL pointer was specified");
  EVK_assert(bytes <= EV_MAX_MESSAGE_LENGTH, "send_message: message too long");

  msg->queueID = queueID;
  msg->senderInfo = senderInfo;
  msg->length = bytes;
  memcpy(msg->message, message, bytes);

  ret = evk_store_message(msg, evk_mem_kernel);
  if (ret == -ENOENT) {
    ev_ret = EV_ERR_Invalid_ID;
  } else if (ret == -EBUSY) {
    ev_ret = EV_ERR_Busy;
  } else if (ret < 0) {
    ev_ret = EV_ERR_Fatal;
  } else {
    ev_ret = EV_OK;
  }

L_END:
  if( msg != NULL )
  {
    evk_free( msg );
  }
  return ev_ret;
}

/* Event acquisition(Order of arrival time) */
//EV_ERR EV_get_next_event(/* OUT */EV_Event *ev);

static EV_ERR
EVK_get_flag_in(EV_ID flagID, EV_Flag *flag, int peek_only, int wait)
{
  EV_Event *ev = NULL;
  EV_ERR ev_ret;
  int ret;

  ev = evk_malloc( sizeof( EV_Event ) );
  if( ev == NULL )
  {
    ev_ret = EV_ERR_Fatal;
    goto L_END;
  }

  EVK_assert(flag != NULL, "get_flag: NULL pointer was specified");
  flag->flagID = EV_NO_ID;
  flag->bits = 0;

  if (!EV_ID_IS_FLAG(flagID)) {
    ev_ret = EV_ERR_Invalid_ID;
    goto L_END;
  }

  ev->type = EV_EVENT_Flag;
  ev->u.flag.flagID = flagID;
  ev->u.flag.bits = 0;

  ret = evk_get_event(ev, peek_only, wait, evk_mem_kernel);

  if (ret < 0) {
    if (ret == -ENOENT) {
      ev_ret = EV_ERR_Invalid_ID;
    } else if (ret == -EINTR) {
      ev_ret = EV_ERR_Interrupted;
    } else {
      ev_ret = EV_ERR_Fatal;
    }
    goto L_END;
  }

  if (ev->type == EV_EVENT_Flag) {
    flag->flagID = ev->u.flag.flagID;
    flag->bits = ev->u.flag.bits;
  }
  ev_ret = EV_OK;

L_END:
  if( ev != NULL )
  {
    evk_free( ev );
  }
  return ev_ret;
}

static EV_ERR
EVK_get_flag64_in(EV_ID flagID, EV_Flag64 *flag, int peek_only, int wait)
{
  EV_Event *ev = NULL;
  EV_ERR ev_ret;
  int ret;

  ev = evk_malloc( sizeof( EV_Event ) );
  if( ev == NULL )
  {
    ev_ret = EV_ERR_Fatal;
    goto L_END;
  }

  EVK_assert(flag != NULL, "get_flag64: NULL pointer was specified");
  flag->flagID = EV_NO_ID;
  flag->bits = 0;

  if (!EV_ID_IS_FLAG64(flagID)) {
    ev_ret = EV_ERR_Invalid_ID;
    goto L_END;
  }

  ev->type = EV_EVENT_Flag64;
  ev->u.flag64.flagID = flagID;
  ev->u.flag64.bits = 0;

  ret = evk_get_event(ev, peek_only, wait, evk_mem_kernel);

  if (ret < 0) {
    if (ret == -ENOENT) {
      ev_ret = EV_ERR_Invalid_ID;
    } else if (ret == -EINTR) {
      ev_ret = EV_ERR_Interrupted;
    } else {
      ev_ret = EV_ERR_Fatal;
    }
    goto L_END;
  }

  if (ev->type == EV_EVENT_Flag64) {
    flag->flagID = ev->u.flag64.flagID;
    flag->bits = ev->u.flag64.bits;
  }
  ev_ret = EV_OK;

L_END:
  if( ev != NULL )
  {
    evk_free( ev );
  }
  return ev_ret;
}

/* Event acquisition(With Search Criteria) */
/** @see EV_get_flag */
EV_ERR
EVK_get_flag(EV_ID flagID, /* OUT */EV_Flag *flag)
{
  return EVK_get_flag_in(flagID, flag, 0, 0);
}

/** @see EV_get_flag64 */
EV_ERR
EVK_get_flag64(EV_ID flagID, /* OUT */EV_Flag64 *flag)
{
  return EVK_get_flag64_in(flagID, flag, 0, 0);
}

/** @see EV_wait_flag */
EV_ERR
EVK_wait_flag(EV_ID flagID, /* OUT */EV_Flag *flag)/* block */
{
  return EVK_get_flag_in(flagID, flag, 0, 1);
}

/** @see EV_wait_flag64 */
EV_ERR
EVK_wait_flag64(EV_ID flagID, /* OUT */EV_Flag64 *flag)/* block */
{
  return EVK_get_flag64_in(flagID, flag, 0, 1);
}

/** @see EV_peek_flag */
EV_ERR
EVK_peek_flag(EV_ID flagID, /* OUT */EV_Flag *flag)
{
  return EVK_get_flag_in(flagID, flag, 1, 0);
}

/** @see EV_peek_flag64 */
EV_ERR
EVK_peek_flag64(EV_ID flagID, /* OUT */EV_Flag64 *flag)
{
  return EVK_get_flag64_in(flagID, flag, 1, 0);
}

static EV_ERR
EVK_get_message_in(EV_ID queueID, EV_Message *message, UINT32 senderInfo,
		   UINT32 length, const void *compare_bytes,
		   int peek_only, int wait)
{
  EV_Event *ev = NULL;
  EV_ERR ev_ret;
  int ret;

  ev = evk_malloc( sizeof( EV_Event ) );
  if( ev == NULL )
  {
    ev_ret = EV_ERR_Fatal;
    goto L_END;
  }

  EVK_assert(message != NULL, "get_message: NULL pointer was specified");
  if (!EV_ID_IS_QUEUE(queueID)) {
    ev_ret = EV_ERR_Invalid_ID;
    goto L_END;
  }
  message->queueID = EV_NO_ID;
  message->senderInfo = 0;
  message->length = 0;

  ev->type = EV_EVENT_Message;
  ev->u.message.queueID = queueID;
  ev->u.message.senderInfo = senderInfo;
  if (compare_bytes != NULL) {
    ev->u.message.length = length;
    memcpy(ev->u.message.message, compare_bytes, length);
  } else {
    ev->u.message.length = 0;
  }

  ret = evk_get_event(ev, peek_only, wait, evk_mem_kernel);

  if (ret < 0) {
    if (ret == -ENOENT) {
      ev_ret = EV_ERR_Invalid_ID;
    } else if (ret == -EINTR) {
      ev_ret = EV_ERR_Interrupted;
    } else {
      ev_ret = EV_ERR_Fatal;
    }
    goto L_END;
  }

  if (ev->type == EV_EVENT_Message) {
    message->queueID = ev->u.message.queueID;
    message->senderInfo = ev->u.message.senderInfo;
    message->length = ev->u.message.length;
    memcpy(message->message, ev->u.message.message, ev->u.message.length);
  }
  ev_ret = EV_OK;

L_END:
  if( ev != NULL )
  {
    evk_free( ev );
  }
  return ev_ret;
}

/** @see EV_get_message */
EV_ERR
EVK_get_message(EV_ID queueID, /* OUT */EV_Message *message)
{
  return EVK_get_message_in(queueID, message, 0, 0, NULL, 0, 0);
}

/** @see EV_wait_message */
EV_ERR
EVK_wait_message(EV_ID queueID, /* OUT */EV_Message *message)/* block */
{
  return EVK_get_message_in(queueID, message, 0, 0, NULL, 0, 1);
}

/** @see EV_peek_message */
EV_ERR
EVK_peek_message(EV_ID queueID, /* OUT */EV_Message *message)
{
  return EVK_get_message_in(queueID, message, 0, 0, NULL, 1, 0);
}

/** @see EV_find_message_by_sender */
EV_ERR
EVK_find_message_by_sender(EV_ID queueID, UINT32 senderInfo,
			   /* OUT */EV_Message *message)
{
  // Not mounted
  return EV_ERR_Fatal;
}

/** @see EV_find_message_by_content */
EV_ERR
EVK_find_message_by_content(EV_ID queueID, UINT16 length,
			    const void *compare_bytes,
			    /* OUT */EV_Message *message)
{
  // Not mounted
  return EV_ERR_Fatal;
}
/** @} */

EXPORT_SYMBOL(evk_get_queue_entry);
EXPORT_SYMBOL(EVK_init);
EXPORT_SYMBOL(EVK_exit);

EXPORT_SYMBOL(EVK_create_flag);
EXPORT_SYMBOL(EVK_create_flag64);
EXPORT_SYMBOL(EVK_create_queue);
EXPORT_SYMBOL(EVK_create_flag_auto_id);
EXPORT_SYMBOL(EVK_create_flag64_auto_id);
EXPORT_SYMBOL(EVK_create_queue_auto_id);
EXPORT_SYMBOL(EVK_destroy_flag);
EXPORT_SYMBOL(EVK_destroy_queue);
EXPORT_SYMBOL(EVK_set_flag);
EXPORT_SYMBOL(EVK_set_flag64);
EXPORT_SYMBOL(EVK_send_message);
EXPORT_SYMBOL(EVK_get_flag);
EXPORT_SYMBOL(EVK_wait_flag);
EXPORT_SYMBOL(EVK_peek_flag);
EXPORT_SYMBOL(EVK_get_flag64);
EXPORT_SYMBOL(EVK_wait_flag64);
EXPORT_SYMBOL(EVK_peek_flag64);
EXPORT_SYMBOL(EVK_get_message);
EXPORT_SYMBOL(EVK_wait_message);
EXPORT_SYMBOL(EVK_peek_message);

#ifndef CONFIG_COMBINE_MODULES
//MODULE_LICENSE("proprietary");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("EVent library for Kernel");
//MODULE_SUPPORTED_DEVICE(name);
//MODULE_PARM(var,type)
//MODULE_PARM_DESC(var,desc)
module_init(EVK_init);
module_exit(EVK_exit);
#endif /* !CONFIG_COMBINE_MODULES */
