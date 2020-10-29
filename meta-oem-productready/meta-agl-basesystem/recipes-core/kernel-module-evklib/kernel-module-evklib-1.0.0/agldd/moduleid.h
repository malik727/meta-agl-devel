/*
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

#include <linux/autoconf.h>
#ifndef _AGLDD_MODULEID_H_
#define _AGLDD_MODULEID_H_

/*
 * Define module ID to be used by programs in moduleid_id.h .
 * Define in the format of "#define XXX_MID ID number" (XXX is the module name).
 *
 * MID allocation policy shall be as follows.
 * - UI Application       : 0xxxh
 * - Application Service  : 1xxxh to 2xxxh
 *   + HMI                : 10xxh
 *   + AV                 : 12xxh
 *   + Radio              : 14xxh
 *   + Connectivity       : 16xxh
 *   + Navigation/Location: 18xxh
 *   + Vehicle            : 1Axxh
 *   + Communication      : 1Cxxh
 *   + BasePF             : 1Exxh
 *   + System             : 20xxh
 *   + Other              : 22xxh
 * - Common Service       : 3xxxh
 * - Extension Service    : 4xxxh
 * - System/Device Driver : 5xxxh
 */

/* UI Application       : 0xxxh */

/* Application Service  : 1xxxh to 2xxxh */
#define MODEMANAGER_MID         0x1000
#define ACTIVITYMANAGER_MID     0x1001

/* Common Service       : 3xxxh */
#define IPMANAGER_MID           0x3000
#define DEVICEMANAGER_MID       0x3001
#define MSGBRK_MID              0x3002
#define TIMERENTRYDRV_MID       0x3003
#define SOUNDAGENT_MID          0x3004
#define CAN_MID                 0x3006
#define _CWORD83__MID                 0x3007
#define SENSOR_MID              0x3008
#define GPS_MID                 0x3009
#define RESMGR_MID              0x300A
#define GRAPHICS_MID            0x300B

/* Extension Service    : 4xxxh */

/* System/Device Driver : 5xxxh */
#define  EV_MID                 0x5001
#define  RPC_MID                0x5002
#define  EVK_MID                0x5801

#endif /* !_AGLDD_MODULEID_H_ */
