/**
 * @file ev_id.h
 * @brief Event library(kernel) -- Defining flag queue ID
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
#ifndef _ev_id_h_
#define _ev_id_h_

/** @addtogroup EV_ID_spec
 * @{ */

/** @brief Flag ID and queue ID types used when sending and receiving events
 *
 * Assign a 32-bit value as follows
 *
 * - Most significant 8 bits: Reserved
 * - Next 16 bits: Modue ID
 * - Lower 8 bits: Define in module
 *
 * Where module is the modules that creates the queue.
 * The modules define ID according to the above assignments using EV_Flag_ID_Base and EV_Queue_ID_Base macros.
 * @see EV_Flag_ID_Base
 * @see EV_Queue_ID_Base
 */
typedef UINT32 EV_ID;

#define EV_ID_BIT       0x80000000UL
#define EV_FLAG64_BIT   0x40000000UL
#define EV_FLAG_BIT     0x20000000UL
#define EV_QUEUE_BIT    0x10000000UL
#define EV_AUTO_ID_BIT  0x08000000UL
#define EV_RESERVED_BIT 0xff000000UL
#define EV_INVALID_ID   EV_ID_BIT
#define EV_NO_ID        EV_INVALID_ID

#define EV_ID_IS_FLAG(queueID) \
  (((queueID) & (EV_ID_BIT|EV_FLAG_BIT)) == (EV_ID_BIT|EV_FLAG_BIT))
#define EV_ID_IS_FLAG64(queueID) \
  (((queueID) & (EV_ID_BIT|EV_FLAG64_BIT)) == (EV_ID_BIT|EV_FLAG64_BIT))
#define EV_ID_IS_QUEUE(queueID) \
  (((queueID) & (EV_ID_BIT|EV_QUEUE_BIT)) == (EV_ID_BIT|EV_QUEUE_BIT))
#define EV_ID_IS_AUTO_ID(queueID) \
  (((queueID) & (EV_ID_BIT|EV_AUTO_ID_BIT)) == (EV_ID_BIT|EV_AUTO_ID_BIT))
#define EV_ID_IS_VALID(queueID) \
  (EV_ID_IS_FLAG(queueID) || EV_ID_IS_FLAG64(queueID) || EV_ID_IS_QUEUE(queueID))

/** @brief Macros for defining flag ID
 *
 * Define the module ID as an argument as follows.
 * - #define XXX_Module_ID 1
 * - #define XXX_Flag_ID_Base EV_Flag_ID_Base(XXX_Module_ID)
 * -
 * - #define XXX_Flag_foo (XXX_Flag_ID_Base + 1)
 * - #define XXX_Flag_bar (XXX_Flag_ID_Base + 2)
 *
 * The module ID is 16 bits and 0 to 65535 can be specified.
 * In addition, 0 to 255 added to Base can be defined as ID.
 */
#define EV_Flag_ID_Base(mod) (EV_ID_BIT|EV_FLAG_BIT|((mod)<<8))

/** @brief Macros for defining 64 bits flag ID
 *
 * Define the module ID as an argument as follows.
 * - #define XXX_Module_ID 1
 * - #define XXX_Flag64_ID_Base EV_Flag64_ID_Base(XXX_Module_ID)
 * -
 * - #define XXX_Flag64_foo (XXX_Flag64_ID_Base + 1)
 * - #define XXX_Flag64_bar (XXX_Flag64_ID_Base + 2)
 *
 * The module ID is 16 bits and 0 to 65535 can be specified.
 * In addition, 0 to 255 added to Base can be defined as ID.
 */
#define EV_Flag64_ID_Base(mod) (EV_ID_BIT|EV_FLAG64_BIT|((mod)<<8))

/** @brief Macros for defining mesage queue ID
 *
 * Define the module ID as an argument as follows.
 * - #define XXX_Module_ID 1
 * - #define XXX_Queue_ID_Base EV_Queue_ID_Base(XXX_Module_ID)
 * -
 * - #define XXX_Queue_foo (XXX_Queue_ID_Base + 1)
 * - #define XXX_Queue_bar (XXX_Queue_ID_Base + 2)
 *
 * The module ID is 16 bits and 0 to 65535 can be specified.
 * In addition, 0 to 255 added to Base can be defined as ID.
 */
#define EV_Queue_ID_Base(mod) (EV_ID_BIT|EV_QUEUE_BIT|((mod)<<8))

/** @} */

#endif /* ! _ev_id_h_ */
