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

/*
 * common path
 */

/* This definitions are matched as following document.
 * eMMC Partition Specification V1.28
 */

#ifndef _AGL_PATH_H_
#define _AGL_PATH_H_

/* Common path */

#define PF_ROOT			"/"
#define PF_NV			PF_ROOT"nv/"
#define PF_VAR			PF_ROOT"var/"
#define PF_TMP			PF_ROOT"tmp/"
#define PF_USR			PF_ROOT"usr/"
#define PF_MNT			PF_ROOT"mnt/"
#define PF_RAMD			PF_ROOT"ramd/"
#define PF_ENVPARAM		PF_ROOT"env_param/"
#define PF_NVSYSTEM		PF_ROOT"nv_system/"

#define PF_SHM			PF_TMP"shm/"
#define PF_SHARE		PF_USR"share/"
#define PF_P_SHARE		PF_USR"agl/share/"

#define PF_SYS_BS		PF_NVSYSTEM"sys_bs/"

#define PF_SYS_BACKUP	PF_NV"backup/"
#define PF_SYS_NPP		PF_NV"npp/"

#define PF_NV_REPRO		PF_NV"repro/"
#define PF_NV_LOG		PF_NV"log/"
#define PF_NV_VUI		PF_NV"vui/"
#define PF_NV_NAVI		PF_NV"navi/"
#define PF_NV_TFF		PF_NV"tff/"
#define PF_NV_FULLBROWSER		PF_NV"fullbrowser/"
#define PF_NV__CWORD8_	PF_NV"_CWORD8_/"
#define PF_NV_MANUAL	PF_NV"manual/"
#define PF_NV_LOG2		PF_NV"log2/"
#define PF_NV_PTDATA		PF_NV"ptdata/"

#define PF_NV_NORACCESS		PF_NV_PTDATA"noraccess/"
#define PF_NV_SEC		PF_NV_PTDATA"sec/"
#define PF_NVPT_GRAPHICS		PF_NV_PTDATA"graphics/"
#define PF_NVPT_HMI		PF_NV_PTDATA"hmi/"
#define PF_NVPT_VEHICLE		PF_NV_PTDATA"vehicle/"
#define PF_NVPT_CONNECTIVITY		PF_NV_PTDATA"connectivity/"
#define PF_NVPT_WLAN		PF_NV_PTDATA"wlan/"
#define PF_NVPT_SI		PF_NV_PTDATA"si/"

#define PF_NVLOG_AGLLOG		PF_NV_LOG"agllog/"
#define PF_NVLOG_WORK		PF_NV_LOG"work/"
#define PF_NVLOG_AWLOG		PF_NV_LOG2"awlog/"
#define PF_NVLOG_CORE		PF_NV_LOG2"core/"


/* Component domain */

#define DOM_GRAPHICS		"graphics"
#define DOM_SOUND		"sound"
#define DOM_NS_STORAGE		"ns_storage"
#define DOM_NS_IMAGESTORAGE	"ns_imagestorage"
#define DOM_BS			"bs"
#define DOM__CWORD24_		"_CWORD24_"
#define DOM_HMI			"hmi"
#define DOM_WLAN		"wlan"
#define DOM_BT			"bt"
#define DOM_CINEMO		"cinemo"
#define DOM_MEDIASRV		"mediasrv"
#define DOM_CONTENTMGR		"contentmgr"
#define DOM_USBAUDIO		"usbaudio"
#define DOM_CDDVD		"cddvd"
#define DOM_AV			"av"
#define DOM_DATASRV		"datasrv"
#define DOM_RADIO		"radio"
#define DOM_BTOOTH		"Bluetooth"
#define DOM__CWORD57_		"_CWORD57_"
#define DOM_REMOTESERVICE	"remoteservice"
#define DOM_CONNECTIVITY	"connectivity"
#define DOM_NAVIGATION		"navigation"
#define DOM_VEHICLE		"vehicle"
#define DOM_ROMACCESS		"romaccess"
#define DOM_AUDIOMGR		"audiomgr"
#define DOM_BACKUP			"backup"
#define DOM_NPP		"npp"

#define DOM_DCMSERVICE		"dcmservice"
#define DOM_NETWORKMANAGER	"NetworkManager"

/* Others */
#define DOM_AGLLOG		"agllog"
#define DOM_AWLOG		"awlog"
#define DOM_WORK		"work"
#define DOM_CORE		"core"

#define DOM_NORACCESS		"noraccess"
#define DOM_SEC			"sec"
#define DOM_DIAG		"diag"


/* For WebDAV */

#define PF_EXP_INTR				PF_NV"export/Internal/"
#define PF_EXPINT_AUDIO			PF_EXP_INTR"Audio/"
#define PF_EXPINT_DATASERV		PF_EXP_INTR"DataService/"
#define PF_EXPINT_SCREENCAP		PF_EXP_INTR"ScreenCapture/"
#define PF_EXPINT_REPRO			PF_EXP_INTR"Repro/"
#define PF_EXPINT_VEHICLEINFO	PF_EXP_INTR"VehicleInfoDraw/"
#define PF_EXPINT_VEHICLEPARA	PF_EXP_INTR"VehicleParameter/"
#define PF_EXPINT_VR			PF_EXP_INTR"VR/"
#define PF_EXPINT_NAVI			PF_EXP_INTR"Navi/"
#define PF_EXPINT_TFF			PF_EXP_INTR"TFF/"
#define PF_EXPINT_OSS			PF_EXP_INTR"OSS/"
#define PF_EXPINT_SMARTPHONE		PF_EXP_INTR"Smartphone/"

/* For RAMD */
#define PF_RAMD_LOG				PF_RAMD"log/"
#define PF_RAMD_BKUP			PF_RAMD"bkup/"

#define PF_RAMD_AWLOG			PF_RAMD_LOG"awlog/"
#define PF_RAMD_AGLLOG			PF_RAMD_LOG"agllog/"

#define PF_RAMD_COMMUNICATION	PF_RAMD_AGLLOG"communication/"
#define PF_RAMD_RADIO			PF_RAMD_AGLLOG"radio/"
#define PF_RAMD_CONNECTIVITY	PF_RAMD_AGLLOG"connectivity/"
#define PF_RAMD_DIAG    	PF_RAMD_AGLLOG"diag/"
#define PF_RAMD_SYSLOG    	PF_RAMD_AGLLOG"syslog/"
#define PF_RAMD_APPFW    	PF_RAMD_AGLLOG"appfw/"



/* For Loopback */
#define PF_MNTLOOP				PF_ROOT"mnt_loop/"

#define PF_MNTLOOP_AW0			PF_MNTLOOP"loopaw0/"
#define PF_MNTLOOP_AW1			PF_MNTLOOP"loopaw1/"
#define PF_MNTLOOP_AW2			PF_MNTLOOP"loopaw2/"
#define PF_MNTLOOP_AW3			PF_MNTLOOP"loopaw3/"
#define PF_MNTLOOP_AW4			PF_MNTLOOP"loopaw4/"
#define PF_MNTLOOP_AW5			PF_MNTLOOP"loopaw5/"
#define PF_MNTLOOP_AW6			PF_MNTLOOP"loopaw6/"
#define PF_MNTLOOP_AW7			PF_MNTLOOP"loopaw7/"
#define PF_MNTLOOP_AW8			PF_MNTLOOP"loopaw8/"
#define PF_MNTLOOP_AW9			PF_MNTLOOP"loopaw9/"
#define PF_MNTLOOP_AW10			PF_MNTLOOP"loopaw10/"
#define PF_MNTLOOP_AW11			PF_MNTLOOP"loopaw11/"
#define PF_MNTLOOP_AW12			PF_MNTLOOP"loopaw12/"
#define PF_MNTLOOP_AW13			PF_MNTLOOP"loopaw13/"
#define PF_MNTLOOP_AW14			PF_MNTLOOP"loopaw14/"
#define PF_MNTLOOP_AW15			PF_MNTLOOP"loopaw15/"
#define PF_MNTLOOP_AW16			PF_MNTLOOP"loopaw16/"
#define PF_MNTLOOP_AW17			PF_MNTLOOP"loopaw17/"
#define PF_MNTLOOP_AW18			PF_MNTLOOP"loopaw18/"
#define PF_MNTLOOP_AW19			PF_MNTLOOP"loopaw19/"
#define PF_MNTLOOP_AW20			PF_MNTLOOP"loopaw20/"

/* For Tmpfs mount */
#define PF_MNTTMPFS                     PF_ROOT"mnt_tmpfs/"
#define PF_MNTTMPFS_AW0                 PF_MNTTMPFS"tmpfsaw0/"


/* DONT USE FOLLOWING DEFINITION !! */
/* These will be deleted in the future */

#define PF_NV_P3	PF_NV"p3/"
#define PF_NV_P4	PF_NV"p4/"
#define PF_NV_P5	PF_NV"p5/"
#define PF_NV_P6	PF_NV"p6/"

#define PF_NPP	  	PF_NV_P3"npp/"
#define PF_BS		PF_NV_P3"bs/"

#define DOM__CWORD8_		"_CWORD8_"
#define DOM_BLUETOOTH		"bluetooth"
#define DOM_VR				"vr"
#define DOM_ENTUNE			"entune"

#define PF_RAMD_GRAPHICS		PF_RAMD_BKUP"graphics/"

#define PF_EXPINT_TRAFFIC		PF_EXP_INTR"Traffic/"

#endif/* _AGL_PATH_H_ */
