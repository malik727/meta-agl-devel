/**
 * @file ev_common.h
 * @brief Event library -- User kernel common data structure
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
#ifndef _ev_common_h_
#define _ev_common_h_

#include <agldd/ev_id.h>

/** @addtogroup EV
 * @{ */
/** @brief Maximum number of bytes for message event */
#define EV_MAX_MESSAGE_LENGTH 2048

/** @brief -Maximum number of flag queue that can be created within a thread */
#define EV_MAX_IDS_IN_THREAD		24

/** @brief -Muximum number of threads that can be registered to the EV in a process */
#define EV_MAX_THREADS_IN_PROCESS	16

/** @brief -Maximum number of flag queue that can be creat within a process
 */
#define EV_MAX_IDS_IN_PROCESS					\
		(EV_MAX_IDS_IN_THREAD * EV_MAX_THREADS_IN_PROCESS)

/** @brief Return values for even library function
 *
 * @see EV_ERR
 */
enum ev_err
{
	EV_OK = 0,		/**< Normal completion */
	EV_ERR_Exist,		/**< The specified flag message queue does exist */
	EV_ERR_Invalid_ID,	/**< The specified flag message queue does not exist */
	EV_ERR_Busy,		/**< Message queue full failed to send */
	EV_ERR_Interrupted,	/**< Waiting function was interrupted by an interrupt */
	EV_ERR_Thread_Over,	/**< Exceeding the number of threads in the process */
	EV_ERR_Invalid_Thread,	/**< Invalid thread ID */
	EV_ERR_Fatal,		/**< Fatal error */
};
/** @brief Return values type for even library function
 *
 * @see ev_err
 */
typedef INT32 EV_ERR;

/** @brief Event type
 *
 * Use in the type of EV_Event structs
 * @see ev_type
 */
typedef UINT32 EV_Type;

/** @brief Bit value representing the type of event */
enum ev_type {
  EV_EVENT_None = 0x00000000,

  /** Flag event: Judged by EV_EVENT_IS_FLAG() */
  EV_EVENT_Flag = 0x0001,
#define EV_EVENT_IS_FLAG(tp) (((tp) & EV_EVENT_Flag) != 0)

  /** Message event: Judged by EV_EVENT_IS_MESSAGE() */
  EV_EVENT_Message = 0x0002,
#define EV_EVENT_IS_MESSAGE(tp) (((tp) & EV_EVENT_Message) != 0)

  /** 64bit flag event: Judged by EV_EVENT_IS_FLAG64() */
  EV_EVENT_Flag64 = 0x0003,
#define EV_EVENT_IS_FLAG64(tp) (((tp) & EV_EVENT_Flag64) != 0)

};

/** @brief Flag event structure */
typedef struct {
  EV_ID flagID;/**< Flag ID */
  UINT32 bits;/**< Bit pattern */
} EV_Flag;

/** @brief 64bit flag event structure */
typedef struct {
  EV_ID flagID;/**< Flag ID */
  UINT64 bits;/**< Bit pattern */
} EV_Flag64;

/** @brief Message event structure */
typedef struct {
  EV_ID queueID;/**< queue ID */
  UINT32 senderInfo;/**< Source information */
  UINT32 length;/**< Number of bytes in the message */
  UINT32 dummy;/** dummy for pading */
  UINT8  message[EV_MAX_MESSAGE_LENGTH];/**< Message */
} EV_Message;

/** @brief Event structure */
typedef struct {
  EV_Type type; /**< Event type */
  union {
    EV_Flag flag; /**< Flag event structure */
    EV_Flag64 flag64; /**< Flag event structure */
    EV_Message message; /**< Message event structure */
  } u; /**< Union of structures per event type */
} EV_Event;

/** @brief Message event queue type
 *
 * Specify the action to be taken when the queue overflows (more events are received when the queue is full).
 */
enum ev_message_queue_type {
  EV_MESSAGE_QUEUE_TYPE_BUSY,/**< Return a BUSY to the source */
  EV_MESSAGE_QUEUE_TYPE_FIFO,/**< Delete the oldest event */
  EV_MESSAGE_QUEUE_TYPE_REPLACE,/**< Replace the most recent event */
};

/** @brief Messge event queue type
 *
 * @see ev_message_queue_type
 */
typedef UINT8 EV_Message_Queue_Type;

/** @} */

#endif /* !_ev_common_h_ */
