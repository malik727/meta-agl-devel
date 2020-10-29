/**
 * @file evk_lib.h
 * @brief Event library -- API specifications for kernel modules
 *
 * @copyright Copyright (c) 2016-2019 TOYOTA MOTOR CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _evk_lib_h_
#define _evk_lib_h_

#include <agldd/ev_common.h>
#include <linux/types.h>
#include <linux/ioctl.h>

/* API definition */

/** @addtogroup EV
 * @{ */
#ifdef __KERNEL__
/* Flag message queue create/delete */
EV_ERR EVK_create_flag(EV_ID flagID);
EV_ERR EVK_create_flag64(EV_ID flagID);
EV_ERR EVK_create_queue(EV_ID queueID,
			UINT8 length,
			UINT16 max_bytes,
			EV_Message_Queue_Type type);

EV_ERR EVK_create_flag_auto_id(/* OUT */EV_ID *flagID);
EV_ERR EVK_create_flag64_auto_id(/* OUT */EV_ID *flagID);
EV_ERR EVK_create_queue_auto_id(/* OUT */EV_ID *queueID,
				UINT8 length,
				UINT16 max_bytes,
				EV_Message_Queue_Type type);

EV_ERR EVK_destroy_flag(EV_ID flagID);
EV_ERR EVK_destroy_queue(EV_ID queueID);

/* Send events */
EV_ERR EVK_set_flag(EV_ID flagID, UINT32 bits);
EV_ERR EVK_set_flag64(EV_ID flagID, UINT64 bits);
EV_ERR EVK_send_message(EV_ID queueID, UINT16 bytes, const void *message,
			UINT32 senderInfo);

/* Get event(with search conditions) */
EV_ERR EVK_get_flag(EV_ID flagID, /* OUT */EV_Flag *flag);
EV_ERR EVK_wait_flag(EV_ID flagID, /* OUT */EV_Flag *flag);/* block */
EV_ERR EVK_peek_flag(EV_ID flagID, /* OUT */EV_Flag *flag);
EV_ERR EVK_get_flag64(EV_ID flagID, /* OUT */EV_Flag64 *flag);
EV_ERR EVK_wait_flag64(EV_ID flagID, /* OUT */EV_Flag64 *flag);/* block */
EV_ERR EVK_peek_flag64(EV_ID flagID, /* OUT */EV_Flag64 *flag);

EV_ERR EVK_get_message(EV_ID queueID, /* OUT */EV_Message *message);
EV_ERR EVK_wait_message(EV_ID queueID, /* OUT */EV_Message *message);/* block */
EV_ERR EVK_peek_message(EV_ID queueID, /* OUT */EV_Message *message);

EV_ERR EVK_find_message_by_sender(EV_ID queueID, UINT32 senderInfo,
				 /* OUT */EV_Message *message);
EV_ERR EVK_find_message_by_content(EV_ID queueID, UINT16 length,
				  const void *compare_bytes,
				  /* OUT */EV_Message *message);
#endif

/** @} */

/** @addtogroup EVK_in
 * @{ */
#define EVK_NAME "evk"
#define EVK_DEV_NAME "/dev/agl/"EVK_NAME
#define EVK_DEV_MAJOR (1033 % 256)
#define EVK_IOC_MAGIC 0xE7

#define	EVK_IOC_CREATE_FLAG		_IO(EVK_IOC_MAGIC, 0x00)
#define	EVK_IOC_CREATE_FLAG64		_IO(EVK_IOC_MAGIC, 0x01)
#define	EVK_IOC_CREATE_MESSAGE_QUEUE	_IO(EVK_IOC_MAGIC, 0x02)
#define	EVK_IOC_ALLOC_FLAG_ID		_IO(EVK_IOC_MAGIC, 0x03)
#define	EVK_IOC_ALLOC_FLAG64_ID		_IO(EVK_IOC_MAGIC, 0x04)
#define	EVK_IOC_ALLOC_QUEUE_ID		_IO(EVK_IOC_MAGIC, 0x05)
#define	EVK_IOC_DESTROY_QUEUE		_IO(EVK_IOC_MAGIC, 0x06)
#define	EVK_IOC_STORE_FLAG		_IO(EVK_IOC_MAGIC, 0x07)
#define	EVK_IOC_STORE_FLAG64		_IO(EVK_IOC_MAGIC, 0x08)
#define	EVK_IOC_STORE_MESSAGE		_IO(EVK_IOC_MAGIC, 0x09)
#define	EVK_IOC_SET_POLL		_IO(EVK_IOC_MAGIC, 0x0a)
#define	EVK_IOC_GET_EVENT		_IO(EVK_IOC_MAGIC, 0x0b)
#define	EVK_IOC_PEEK_EVENT		_IO(EVK_IOC_MAGIC, 0x0c)
#define	EVK_IOC_WAIT_EVENT		_IO(EVK_IOC_MAGIC, 0x0d)
#define	EVK_IOC_GET_NEXT_EVENT		_IO(EVK_IOC_MAGIC, 0x0e)
#define	EVK_IOC_PEEK_NEXT_EVENT		_IO(EVK_IOC_MAGIC, 0x0f)
#define	EVK_IOC_DEBUG_LIST		_IO(EVK_IOC_MAGIC, 0x10)

typedef struct {
  EV_ID queueID;/**< Queue ID */
  UINT32 max_bytes;/**< Maximum number of bytes for an event */
  UINT8 length;/**< Queue length */
  EV_Message_Queue_Type type;/**< Type */
} EVK_Message_Queue_Request;

typedef struct {
  INT32 num; /**< Number of queue ID of search */
  EV_ID ids[EV_MAX_IDS_IN_PROCESS]; /**< Queue ID of search */
  EV_Event ev; /**< [OUT] First event that occured */
} EVK_Next_Event_Query;

/** @} */

#endif /* !_evk_lib_h */
