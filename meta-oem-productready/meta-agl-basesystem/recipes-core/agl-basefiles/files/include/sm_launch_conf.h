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

#ifndef __AGL_THREAD_H__
#define __AGL_THREAD_H__

//MACRO
#define PR_TSS_S    "0"
#define PR_TSS      0

/*
  Main thread name. It need to be same as service name in sm_launch.xml or tskm_launch.xml
  Max name length is 15
  #define MN_XXXXX   "MainName"  

  Thread name
  Max name length is 15
  #define TN_XXXXX        "ThreadName" 

  Thread priority 0:TSS   1-99:FIFO
  #define PR_XXXXX_S     "(0-99)"    //for xml
  #define PR_XXXXX       0-99        //for program
*/

#define MN_SS_SYSMANAGER      "SS_SysManager"
#define PR_SS_SYSMANAGER_S    "0"
#define PR_SS_SYSMANAGER      (0)

  #define TN_SMHEARTBEAT        "SM.Heartbeat"
  #define PR_SMHEARTBEAT_S      "0"
  #define PR_SMHEARTBEAT        (0)

  #define TN_SMPROCLAUNCH       "SM.ProcLaunch"
  #define PR_SMPROCLAUNCH_S     "0"
  #define PR_SMPROCLAUNCH       (0)

  #define TN_SMLOWMEMMON        "SM.LowMemMon"
  #define PR_SMLOWMEMMON_S      "0"
  #define PR_SMLOWMEMMON        (0)

  #define TN_LOGGERRTIME        "LoggerRtime"
  #define PR_LOGGERRTIME_S      PR_TSS_S
  #define PR_LOGGERRTIME        PR_TSS


//======= exec from system manager =============
#define MN_NS_SHAREDMEM       "NS_SharedMem"
#define PR_NS_SHAREDMEM_S     "0"
#define PR_NS_SHAREDMEM       (0)


#define MN_NS_NPPSERVICE      "NS_NPPService"
#define PR_NS_NPPSERVICE_S    "0"
#define PR_NS_NPPSERVICE      (0)

  #define TN_NS_NPPREADWKR    "NS_NPPReadWkr"
  #define PR_NS_NPPREADWKR_S  "0"
  #define PR_NS_NPPREADWKR    (0)

  #define TN_NS_NPPWRITEWKR   "NS_NPPWriteWkr"
  #define PR_NS_NPPWRITEWKR_S "0"
  #define PR_NS_NPPWRITEWKR   (0)

  #define TN_NS_NPPIPWKR      "NS_NPPIPWkr"
  #define PR_NS_NPPIPWKR_S    "0"
  #define PR_NS_NPPIPWKR      (0)

#define MN_NS_BACKUPMGR       "NS_BackupMgr"
#define PR_NS_BACKUPMGR_S     "0"
#define PR_NS_BACKUPMGR       (0)

  #define TN_NS_BKUPNAND      "NS_BkupNAND"
  #define PR_NS_BKUPNAND_S    "0"
  #define PR_NS_BKUPNAND      (0)

  #define TN_NS_BKUPDELAY     "NS_BkupDelay"
  #define PR_NS_BKUPDELAY_S   "0"
  #define PR_NS_BKUPDELAY     (0)

#define MN_SS_DEVDETECTSRV    "SS_DevDetectSrv"
#define PR_SS_DEVDETECTSRV_S  "0"
#define PR_SS_DEVDETECTSRV    (0)

  #define TN_SS_DETECT_USB    "SS_Detect_USB"
  #define PR_SS_DETECT_USB_S  "0"
  #define PR_SS_DETECT_USB    (0)

  #define TN_SS_DETECT_SD     "SS_Detect_SD"
  #define PR_SS_DETECT_SD_S   "0"
  #define PR_SS_DETECT_SD     (0)

  #define TN_SS_MONITOR_OVC     "SS_Monitor_OVC"
  #define PR_SS_MONITOR_OVC_S   "0"
  #define PR_SS_MONITOR_OVC     (0)

#define MN_SS_LOGGERSRV       "SS_LoggerSrv"
#define PR_SS_LOGGERSRV_S     PR_TSS_S
#define PR_SS_LOGGERSRV       PR_TSS

  #define TN_PDGLOGQUER       "pdg.LogQueR"
  #define PR_PDGLOGQUER_S     PR_TSS_S
  #define PR_PDGLOGQUER       PR_TSS

  #define TN_PDGTRANSQUER     "pdg.TransQueR"
  #define PR_PDGTRANSQUER_S   PR_TSS_S
  #define PR_PDGTRANSQUER     PR_TSS

  #define TN_PDGEVNTLOGQUE    "pdg.EvntLogQue"
  #define PR_PDGEVNTLOGQUE_S  PR_TSS_S
  #define PR_PDGEVNTLOGQUE    PR_TSS

  #define TN_SSLOGGERSTRAGE   "SSLoggerStrage"
  #define PR_SSLOGGERSTRAGE_S PR_TSS_S
  #define PR_SSLOGGERSTRAGE   PR_TSS

  #define TN_PFDRECTHREAD     "PFDRECThread"
  #define PR_PFDRECTHREAD_S   PR_TSS_S
  #define PR_PFDRECTHREAD     PR_TSS

#define MN_PS_LOGGERSHADOW    "PS_LoggerShadow"
  #define PR_PSLOGGERSHADOW_S   PR_TSS_S
  #define PR_PSLOGGERSHADOW     PR_TSS

#define MN_UDEVD              "udevd"
#define PR_UDEVD_S            "1"
#define PR_UDEVD              (1)

#define MN_COMMUNICATION      "Communication"
#define PR_COMMUNICATION_S    "0"
#define PR_COMMUNICATION      (0)

  #define TN_DEV_SYSCOM_TMR   "DEV_SYSCOM_TMR"
  #define PR_DEV_SYSCOM_TMR_S "0"
  #define PR_DEV_SYSCOM_TMR   (0)

  #define TN_DEV_SYSCOM_RCV   "DEV_SYSCOM_RCV"
  #define PR_DEV_SYSCOM_RCV_S "0"
  #define PR_DEV_SYSCOM_RCV   (0)

  #define TN_DEV_SYSCOM_MAIN    "DEV_SYSCOM_MAIN"
  #define PR_DEV_SYSCOM_MAIN_S  "0"
  #define PR_DEV_SYSCOM_MAIN    (0)

  #define TN_TGWCOM           "TGWCOM"
  #define PR_TGWCOM_S         "0"
  #define PR_TGWCOM           (0)

  #define TN__CWORD83_              "_CWORD83_"
  #define PR__CWORD83__S            "0"
  #define PR__CWORD83_              (0)

  #define TN_CAN_COM_PROT     "CAN_COM_PROT"
  #define PR_CAN_COM_PROT_S   "0"
  #define PR_CAN_COM_PROT     (0)

#define MN_PS_PSMSHADOW       "PS_PSMShadow"
#define PR_PS_PSMSHADOW_S     "0"
#define PR_PS_PSMSHADOW       (0)

#define MN_COMMSH4A           "CommSH4A"
#define PR_COMMSH4A_S         "0"
#define PR_COMMSH4A           (0)

  #define TN_DEV_SH4A_SND     "DEV_SH4ACOM_SND"
  #define PR_DEV_SH4A_SND_S   "0"
  #define PR_DEV_SH4A_SND     (0)

  #define TN_DEV_SH4A_RCV     "DEV_SH4ACOM_RCV"
  #define PR_DEV_SH4A_RCV_S   "0"
  #define PR_DEV_SH4A_RCV     (0)

  #define TN_DEV_SH4A_MON     "DEV_SH4ACOM_MON"
  #define PR_DEV_SH4A_MON_S   "0"
  #define PR_DEV_SH4A_MON     (0)

#define MN_PS_COMMUSB         "PS_CommUSB"
#define PR_PS_COMMUSB_S       "0"
#define PR_PS_COMMUSB         (0)

  #define TN_COMMUSB_RCV      "COMMUSB_RCV"
  #define PR_COMMUSB_RCV_S    "0"
  #define PR_COMMUSB_RCV      (0)

  #define TN_COMMUSB_DIAG    "COMMUSB_DIAG"
  #define PR_COMMUSB_DIAG_S  "0"
  #define PR_COMMUSB_DIAG    (0)

#define MN_PS_CANGW_M        "CANGW_M"
#define PR_PS_CANGW_M_S       PR_TSS_S
#define PR_PS_CANGW_M         PR_TSS

  #define TN_CANGW_M_RCV       "CANGW_M_RCV"
  #define PR_CANGW_M_RCV_S     PR_TSS_S
  #define PR_CANGW_M_RCV       PR_TSS

  #define TN_CANGW_M_DIAG      "CANGW_M_DIAG"
  #define PR_CANGW_M_DIAG_S    PR_TSS_S
  #define PR_CANGW_M_DIAG      PR_TSS

#define MN_PS_CANGW_S         "CANGW_S"
#define PR_PS_CANGW_S_S       PR_TSS_S
#define PR_PS_CANGW_S         PR_TSS

  #define TN_CANGW_S_SND       "CANGW_S_SND"
  #define PR_CANGW_S_SND_S     PR_TSS_S
  #define PR_CANGW_S_SND       PR_TSS

  #define TN_CANGW_S_DIAG      "CANGW_S_DIAG"
  #define PR_CANGW_S_DIAG_S    PR_TSS_S
  #define PR_CANGW_S_DIAG      PR_TSS

#define MN_LANSERVER          "LanServer"
#define PR_LANSERVER_S        "0"
#define PR_LANSERVER          (0)

#define MN_PS_CDR             "ps_cdr"
#define PR_PS_CDR_S           PR_TSS_S
#define PR_PS_CDR             PR_TSS

  #define TN_PS_CDR_NBD         "ps_cdr_nbd"
  #define PR_PS_CDR_NBD_S       PR_TSS_S
  #define PR_PS_CDR_NBD         PR_TSS

  #define TN_PS_CDR_DOIT        "ps_cdr_doit"
  #define PR_PS_CDR_DOIT_S      PR_TSS_S
  #define PR_PS_CDR_DOIT        PR_TSS

  #define TN_PS_CDR_READ        "ps_cdr_read"
  #define PR_PS_CDR_READ_S      PR_TSS_S
  #define PR_PS_CDR_READ        PR_TSS

#define MN_POSITIONING        "Positioning"
#define PR_POSITIONING_S      PR_TSS_S
#define PR_POSITIONING        PR_TSS

  #define TN_POSITIONING_GPS_MAIN     "POS_Main"
  #define PR_POSITIONING_GPS_MAIN_S   PR_TSS_S
  #define PR_POSITIONING_GPS_MAIN     PR_TSS

  #define TN_POSITIONING_GPS_RECV     "POS_Gps_Recv"
  #define PR_POSITIONING_GPS_RECV_S   PR_TSS_S
  #define PR_POSITIONING_GPS_RECV     PR_TSS

  #define TN_POSITIONING_GPS     "POS_Gps"
  #define PR_POSITIONING_GPS_S   PR_TSS_S
  #define PR_POSITIONING_GPS     PR_TSS

  #define TN_POSITIONING_SENS     "POS_Sens"
  #define PR_POSITIONING_SENS_S   PR_TSS_S
  #define PR_POSITIONING_SENS     PR_TSS

  #define TN_POSITIONING_GPS_ROLOVR     "POS_Gps_Rolovr"
  #define PR_POSITIONING_GPS_ROLOVR_S   PR_TSS_S
  #define PR_POSITIONING_GPS_ROLOVR     PR_TSS

#define MN_CLOCK              "clock"
#define PR_CLOCK_S            "0"
#define PR_CLOCK              (0)

  #define TN_CLOCK_MNG        "ClockMng"
  #define PR_CLOCK_MNG_S      "0"
  #define PR_CLOCK_MNG        (0)

#define MN_VEHICLE            "vehicle"
#define PR_VEHICLE_S          "0"
#define PR_VEHICLE            (0)

  #define TN_VEHICLE_SENS     "VehicleSens"
  #define PR_VEHICLE_SENS_S   "0"
  #define PR_VEHICLE_SENS     (0)

  #define TN_LINE_SENS_DRV    "LineSensDrv"
  #define PR_LINE_SENS_DRV_S  "0"
  #define PR_LINE_SENS_DRV    (0)

#define MN_SS_POWERSERVICE    "SS_PowerService"
#define PR_SS_POWERSERVICE_S  "0"
#define PR_SS_POWERSERVICE    (0)

#define MN_SS_TASKMANAGER     "SS_TaskManager"
#define PR_SS_TASKMANAGER_S   "0"
#define PR_SS_TASKMANAGER     (0)

  #define TN_SS_TSKMTIMER     "SS_TskmTimer"
  #define PR_SS_TSKMTIMER_S   "0"
  #define PR_SS_TSKMTIMER     (0)

#define MN_SOUND              "Sound"
#define PR_SOUND_S            "0"
#define PR_SOUND              (0)

  #define TN_VG_SNDSRCMGR     "VG_SNDSRCMGR"
  #define PR_VG_SNDSRCMGR_S   "0"
  #define PR_VG_SNDSRCMGR     (0)
  
  #define TN_SND_INPUTCTRL    "SND_INPUTCTRL"
  #define PR_SND_INPUTCTRL_S  "0"
  #define PR_SND_INPUTCTRL    (0)
  
  #define TN_SND_DEVCTRL      "SND_DEVCTRL"
  #define PR_SND_DEVCTRL_S    "0"
  #define PR_SND_DEVCTRL      (0)
  
  #define TN_SND_VCETRFCTRL   "SND_VCETRFCTRL"
  #define PR_SND_VCETRFCTRL_S "0"
  #define PR_SND_VCETRFCTRL   (0)

  #define TN_SND_VCETRFWRT1   "SND_VCETRFWRT1"
  #define PR_SND_VCETRFWRT1_S "0"
  #define PR_SND_VCETRFWRT1   (0)

  #define TN_SND_VCETRFWRT2   "SND_VCETRFWRT2"
  #define PR_SND_VCETRFWRT2_S "0"
  #define PR_SND_VCETRFWRT2   (0)
  
  #define TN_VG_SNDCTRL_BSCF    "VG_SNDCTRL_BSCF"
  #define PR_VG_SNDCTRL_BSCF_S  "0"
  #define PR_VG_SNDCTRL_BSCF    (0)
  
  #define TN_VG_SNDCTRL_BSCR    "VG_SNDCTRL_BSCR"
  #define PR_VG_SNDCTRL_BSCR_S  "0"
  #define PR_VG_SNDCTRL_BSCR    (0)
  
  #define TN_VG_SNDCTRL_ITRT    "VG_SNDCTRL_ITRT"
  #define PR_VG_SNDCTRL_ITRT_S  "0"
  #define PR_VG_SNDCTRL_ITRT    (0)
  
  #define TN_CVRS_OPRT_OUT_1    "CVRS_OPRT_OUT_1"
  #define PR_CVRS_OPRT_OUT_1_S  "0"
  #define PR_CVRS_OPRT_OUT_1    (0)
  
  #define TN_CVRS_OPRT_OUT_2    "CVRS_OPRT_OUT_2"
  #define PR_CVRS_OPRT_OUT_2_S  "0"
  #define PR_CVRS_OPRT_OUT_2    (0)
  
  #define TN_CVRS_OPRT_OUT_3    "CVRS_OPRT_OUT_3"
  #define PR_CVRS_OPRT_OUT_3_S  "0"
  #define PR_CVRS_OPRT_OUT_3    (0)

  #define TN_CVRS_OPRT_OUT_4    "CVRS_OPRT_OUT_4"
  #define PR_CVRS_OPRT_OUT_4_S  "0"
  #define PR_CVRS_OPRT_OUT_4    (0)
  
  #define TN_CVRS_OPRT_IN_1    "CVRS_OPRT_IN_1"
  #define PR_CVRS_OPRT_IN_1_S  "0"
  #define PR_CVRS_OPRT_IN_1    (0)

  #define TN_CVRS_OPRT_IN_2    "CVRS_OPRT_IN_2"
  #define PR_CVRS_OPRT_IN_2_S  "0"
  #define PR_CVRS_OPRT_IN_2    (0)

  #define TN_CVRS_OPRT_IN_3    "CVRS_OPRT_IN_3"
  #define PR_CVRS_OPRT_IN_3_S  "0"
  #define PR_CVRS_OPRT_IN_3    (0)

  #define TN_CVRS_OPRT_IN_4    "CVRS_OPRT_IN_4"
  #define PR_CVRS_OPRT_IN_4_S  "0"
  #define PR_CVRS_OPRT_IN_4    (0)

  #define TN_CVRS_OPRT_IN_5    "CVRS_OPRT_IN_5"
  #define PR_CVRS_OPRT_IN_5_S  "0"
  #define PR_CVRS_OPRT_IN_5    (0)

  #define TN_CVRS_OPRT_IN_6    "CVRS_OPRT_IN_6"
  #define PR_CVRS_OPRT_IN_6_S  "0"
  #define PR_CVRS_OPRT_IN_6    (0)

  #define TN_CVRS_OPRT_IN_7    "CVRS_OPRT_IN_7"
  #define PR_CVRS_OPRT_IN_7_S  "0"
  #define PR_CVRS_OPRT_IN_7    (0)

  #define TN_CVRS_OPRT_IN_8    "CVRS_OPRT_IN_8"
  #define PR_CVRS_OPRT_IN_8_S  "0"
  #define PR_CVRS_OPRT_IN_8    (0)

  #define TN_CVRS_OPRT_BS_I     "CVRS_OPRT_BS_I"
  #define PR_CVRS_OPRT_BS_I_S   "0"
  #define PR_CVRS_OPRT_BS_I     (0)
  
  #define TN_VR_NVR_RECO        "VR_NVR_RECO"
  #define PR_VR_NVR_RECO_S      "0"
  #define PR_VR_NVR_RECO        (0)
  
  #define TN_SND_ECNR       "SND_ECNR"
  #define PR_SND_ECNR_S     "0"
  #define PR_SND_ECNR       (0)

  #define TN_SNDAGENT_000       "SNDAGENT_000"
  #define PR_SNDAGENT_000_S     "0"
  #define PR_SNDAGENT_000       (0)

  #define TN_SNDAGENT_001       "SNDAGENT_001"
  #define PR_SNDAGENT_001_S     "0"
  #define PR_SNDAGENT_001       (0)

  #define TN_SNDAGENT_002       "SNDAGENT_002"
  #define PR_SNDAGENT_002_S     "0"
  #define PR_SNDAGENT_002       (0)

  #define TN_SNDAGENT_003       "SNDAGENT_003"
  #define PR_SNDAGENT_003_S     "0"
  #define PR_SNDAGENT_003       (0)

  #define TN_SNDAGENT_004       "SNDAGENT_004"
  #define PR_SNDAGENT_004_S     "0"
  #define PR_SNDAGENT_004       (0)

  #define TN_SNDAGENT_005       "SNDAGENT_005"
  #define PR_SNDAGENT_005_S     "0"
  #define PR_SNDAGENT_005       (0)

  #define TN_SNDAGENT_006       "SNDAGENT_006"
  #define PR_SNDAGENT_006_S     "0"
  #define PR_SNDAGENT_006       (0)

  #define TN_SNDAGENT_007       "SNDAGENT_007"
  #define PR_SNDAGENT_007_S     "0"
  #define PR_SNDAGENT_007       (0)

  #define TN_SNDAGENT_008       "SNDAGENT_008"
  #define PR_SNDAGENT_008_S     "0"
  #define PR_SNDAGENT_008       (0)

  #define TN_SNDAGENT_009       "SNDAGENT_009"
  #define PR_SNDAGENT_009_S     "0"
  #define PR_SNDAGENT_009       (0)

  #define TN_SNDAGENT_010       "SNDAGENT_010"
  #define PR_SNDAGENT_010_S     "0"
  #define PR_SNDAGENT_010       (0)

  #define TN_SNDAGENT_011       "SNDAGENT_011"
  #define PR_SNDAGENT_011_S     "0"
  #define PR_SNDAGENT_011       (0)

  #define TN_SNDAGENT_012       "SNDAGENT_012"
  #define PR_SNDAGENT_012_S     "0"
  #define PR_SNDAGENT_012       (0)

  #define TN_SNDAGENT_013       "SNDAGENT_013"
  #define PR_SNDAGENT_013_S     "0"
  #define PR_SNDAGENT_013       (0)

  #define TN_SNDAGENT_014       "SNDAGENT_014"
  #define PR_SNDAGENT_014_S     "0"
  #define PR_SNDAGENT_014       (0)

  #define TN_SNDAGENT_015       "SNDAGENT_015"
  #define PR_SNDAGENT_015_S     "0"
  #define PR_SNDAGENT_015       (0)

  #define TN_SNDAGENT_016       "SNDAGENT_016"
  #define PR_SNDAGENT_016_S     "0"
  #define PR_SNDAGENT_016       (0)

  #define TN_SNDAGENT_017       "SNDAGENT_017"
  #define PR_SNDAGENT_017_S     "0"
  #define PR_SNDAGENT_017       (0)

  #define TN_SNDAGENT_018       "SNDAGENT_018"
  #define PR_SNDAGENT_018_S     "0"
  #define PR_SNDAGENT_018       (0)

  #define TN_SNDAGENT_019       "SNDAGENT_019"
  #define PR_SNDAGENT_019_S     "0"
  #define PR_SNDAGENT_019       (0)

  #define TN_SNDAGENT_020       "SNDAGENT_020"
  #define PR_SNDAGENT_020_S     "0"
  #define PR_SNDAGENT_020       (0)

  #define TN_SNDAGENT_021       "SNDAGENT_021"
  #define PR_SNDAGENT_021_S     "0"
  #define PR_SNDAGENT_021       (0)

  #define TN_SNDAGENT_022       "SNDAGENT_022"
  #define PR_SNDAGENT_022_S     "0"
  #define PR_SNDAGENT_022       (0)

  #define TN_SNDAGENT_023       "SNDAGENT_023"
  #define PR_SNDAGENT_023_S     "0"
  #define PR_SNDAGENT_023       (0)

  #define TN_SNDAGENT_024       "SNDAGENT_024"
  #define PR_SNDAGENT_024_S     "0"
  #define PR_SNDAGENT_024       (0)

  #define TN_SNDAGENT_025       "SNDAGENT_025"
  #define PR_SNDAGENT_025_S     "0"
  #define PR_SNDAGENT_025       (0)

#define MN_SS_RESOURCEMGR     "SS_ResourceMgr"
#define PR_SS_RESOURCEMGR_S   "0"
#define PR_SS_RESOURCEMGR     (0)

  #define TN_RESOURCEHWDT     "ResourceHWDT"
  #define PR_RESOURCEHWDT_S   "0"
  #define PR_RESOURCEHWDT     (0)

#define MN_AS_AUDIOMANAGER    "AS_AudioManager"
#define PR_AS_AUDIOMANAGER_S  PR_TSS_S
#define PR_AS_AUDIOMANAGER    PR_TSS

  #define TN_AS_SOUNDBEEP	"AS_SoundBeep"
  #define PR_AS_SOUNDBEEP_S     PR_TSS_S
  #define PR_AS_SOUNDBEEP	PR_TSS

#define MN_GRAPHICS           "Graphics"
#define PR_GRAPHICS_S         "0"
#define PR_GRAPHICS           (0)

  #define TN_GR_MAIN_CTRL     "Graphics_main"
  #define PR_GR_MAIN_CTRL_S   PR_TSS_S
  #define PR_GR_MAIN_CTRL     PR_TSS

  #define TN_GR_SEQ_CTRL      "Graphics_seq"
  #define PR_GR_SEQ_CTRL_S    PR_TSS_S
  #define PR_GR_SEQ_CTRL      PR_TSS

  #define TN_GR_DEV_RCV_CTRL     "Graphics_rcv"
  #define PR_GR_DEV_RCV_CTRL_S   PR_TSS_S
  #define PR_GR_DEV_RCV_CTRL     PR_TSS

  #define TN_GR_VCAP1_CTRL    "Graphics_cap1"
  #define PR_GR_VCAP1_CTRL_S   "0"
  #define PR_GR_VCAP1_CTRL     (0)

  #define TN_GR_VCAP2_CTRL    "Graphics_cap2"
  #define PR_GR_VCAP2_CTRL_S   "0"
  #define PR_GR_VCAP2_CTRL     (0)

#define MN_VUPSERVICE         "vupservice"
#define PR_VUPSERVICE_S       PR_TSS_S
#define PR_VUPSERVICE         PR_TSS

#define MN_SS_UPDATESERVICE   "UpdateService"
#define PR_SS_UPDATESERVICE_S PR_TSS_S
#define PR_SS_UPDATESERVICE   PR_TSS

  #define TN_UPSERVICE_VERI     "t_update_veri"
  #define PR_UPSERVICE_VERI_S   PR_TSS_S
  #define PR_UPSERVICE_VERI     PR_TSS

#define MN_NW_MICSERVICE      "NW_MicService"
#define PR_NW_MICSERVICE_S    PR_TSS_S
#define PR_NW_MICSERVICE      PR_TSS

#define MN_NS_LOCKMGR         "LockMgr"
#define PR_NS_LOCKMGR_S       PR_TSS_S
#define PR_NS_LOCKMGR         PR_TSS

#define MN_PS_SWITCHHANDLER      "SwitchHandler"
#define PR_PS_SWITCHHANDLER_S    "0"
#define PR_PS_SWITCHHANDLER      (0)

#define MN_SS_WINSYS          "SS_WinSys"
#define PR_SS_WINSYS_S        "0"
#define PR_SS_WINSYS          0

#define MN_MODEMANAGER        "modemanager"
#define PR_MODEMANAGER_S      PR_TSS_S
#define PR_MODEMANAGER        PR_TSS

#define MN_BTSTACKMAIN        "btstackmain"
#define PR_BTSTACKMAIN_S      PR_TSS_S
#define PR_BTSTACKMAIN        PR_TSS

#define MN_MEDIASERVICE       "MediaService"
#define PR_MEDIASERVICE_S     PR_TSS_S
#define PR_MEDIASERVICE       PR_TSS

// REPRO START
#define MN_REPROSERVICE       "ReproService"
#define PR_REPROSERVICE_S      PR_TSS_S
#define PR_REPROSERVICE        PR_TSS

  #define TN_REPROSEQUENCER     "RPRS_Sequencer"
  #define PR_REPROSEQUENCER_S   PR_TSS_S
  #define PR_REPROSEQUENCER     PR_TSS

  #define TN_REPROCTRL          "RPRS_Control"
  #define PR_REPROCTRL_S        PR_TSS_S
  #define PR_REPROCTRL          PR_TSS

  #define TN_REPROCENTERCOMM    "RPRS_CenterComm"
  #define PR_REPROCENTERCOMM_S  PR_TSS_S
  #define PR_REPROCENTERCOMM    PR_TSS

  #define TN_REPROUNITCOMM      "RPRS_UnitComm"
  #define PR_REPROUNITCOMM_S    PR_TSS_S
  #define PR_REPROUNITCOMM      PR_TSS

  #define TN_REPROWEBDAVMGR     "RPRS_WebDAVMgr"
  #define PR_REPROWEBDAVMGR_S   PR_TSS_S
  #define PR_REPROWEBDAVMGR     PR_TSS

#define MN_REPROAENDTEST       "Repro_Testpro_Sender"
#define PR_REPROAENDTEST_S      PR_TSS_S
#define PR_REPROAENDTEST        PR_TSS

  #define TN_REPROAENDTESTTN       "Repro_TestproT"
  #define PR_REPROAENDTESTTN_S      PR_TSS_S
  #define PR_REPROAENDTESTTN        PR_TSS

#define MN_REPROBACKVUP        "BackVupCtrl"
#define PR_REPROBACKVUP_S       PR_TSS_S
#define PR_REPROBACKVUP         PR_TSS

#define MN_REPRODEVELOP        "DevReproService"
#define PR_REPRODEVELOP_S       PR_TSS_S
#define PR_REPRODEVELOP         PR_TSS
// REPRO END

  #define TN_MED_MMCOM_PLAY      "mmcom_play"
  #define PR_MED_MMCOM_PLAY_S    PR_TSS_S
  #define PR_MED_MMCOM_PLAY      PR_TSS

  #define TN_MED_MMCOM_MEDIA     "mmcom_media"
  #define PR_MED_MMCOM_MEDIA_S   PR_TSS_S
  #define PR_MED_MMCOM_MEDIA     PR_TSS

  #define TN_MED_MMCOM_DB        "mmcom_db"
  #define PR_MED_MMCOM_DB_S      PR_TSS_S
  #define PR_MED_MMCOM_DB        PR_TSS

  #define TN_MED_MMCOM_LIST      "mmcom_list"
  #define PR_MED_MMCOM_LIST_S    PR_TSS_S
  #define PR_MED_MMCOM_LIST      PR_TSS
  
  #define TN_MED_MMCOM_DBUSB      "mmcom_dbusb"
  #define PR_MED_MMCOM_DBUSB_S    PR_TSS_S
  #define PR_MED_MMCOM_DBUSB      PR_TSS

  #define TN_MED_MMCOM_DBSD      "mmcom_dbsd"
  #define PR_MED_MMCOM_DBSD_S    PR_TSS_S
  #define PR_MED_MMCOM_DBSD      PR_TSS

  #define TN_MED_MMCOM_DBCD      "mmcom_dbcd"
  #define PR_MED_MMCOM_DBCD_S    PR_TSS_S
  #define PR_MED_MMCOM_DBCD      PR_TSS

  #define TN_MED_MMCOM_PLAYRCV   "mmcom_playrcv"
  #define PR_MED_MMCOM_PLAYRCV_S PR_TSS_S
  #define PR_MED_MMCOM_PLAYRCV   PR_TSS

  #define TN_MED_RIPCOM_MNG      "MngRipComm"
  #define PR_MED_RIPCOM_MNG_S    PR_TSS_S
  #define PR_MED_RIPCOM_MNG      PR_TSS

  #define TN_MED_RIPCOM_EXE01    "ExeRipComm01"
  #define PR_MED_RIPCOM_EXE01_S  PR_TSS_S
  #define PR_MED_RIPCOM_EXE01    PR_TSS

  #define TN_MED_RIPCOM_EXE02    "ExeRipComm02"
  #define PR_MED_RIPCOM_EXE02_S  PR_TSS_S
  #define PR_MED_RIPCOM_EXE02    PR_TSS

  #define TN_MED_DISCCOM_MAIN    "disccom_main"
  #define PR_MED_DISCCOM_MAIN_S  PR_TSS_S
  #define PR_MED_DISCCOM_MAIN    PR_TSS

  #define TN_MED_DISCCOM_DB      "disccom_db"
  #define PR_MED_DISCCOM_DB_S    PR_TSS_S
  #define PR_MED_DISCCOM_DB      PR_TSS

#define MN_PLAYBACKSERVICE    "PlaybackService"
#define PR_PLAYBACKSERVICE_S  PR_TSS_S
#define PR_PLAYBACKSERVICE    PR_TSS

  #define TN_PLAYSRV_AUDIO       "playsrv_audio"
  #define PR_PLAYSRV_AUDIO_S     PR_TSS_S
  #define PR_PLAYSRV_AUDIO       PR_TSS

  #define TN_PLAYSRV_RIP         "playsrv_rip"
  #define PR_PLAYSRV_RIP_S       PR_TSS_S
  #define PR_PLAYSRV_RIP         PR_TSS

  #define TN_PLAYSRV_PLAY        "playsrv_play"
  #define PR_PLAYSRV_PLAY_S      PR_TSS_S
  #define PR_PLAYSRV_PLAY        PR_TSS

  #define TN_PLAYSRV_DISC        "playsrv_disc"
  #define PR_PLAYSRV_DISC_S      PR_TSS_S
  #define PR_PLAYSRV_DISC        PR_TSS

  #define TN_PLAYSRV_ARTWORK     "playsrv_artwork"
  #define PR_PLAYSRV_ARTWORK_S   PR_TSS_S
  #define PR_PLAYSRV_ARTWORK     PR_TSS

#define MN_DISCSERVICE        "DiscService"
#define PR_DISCSERVICE_S      PR_TSS_S
#define PR_DISCSERVICE        PR_TSS

#define MN_RADIOSERVICE       "RadioService"
#define PR_RADIOSERVICE_S     PR_TSS_S
#define PR_RADIOSERVICE       PR_TSS

#define MN_RADIOHDARBITER     "RadioHDArbiter"
#define PR_RADIOHDARBITER_S   "0"
#define PR_RADIOHDARBITER     (0)

#define MN_HRDS_MANAGER     "hrds_manager"
#define PR_HRDS_MANAGER_S   PR_TSS_S
#define PR_HRDS_MANAGER     PR_TSS

  #define TN_HRDS_HDMNG      "hrds_hdmng"
  #define PR_HRDS_HDMNG_S    PR_TSS_S
  #define PR_HRDS_HDMNG      PR_TSS

  #define TN_HRDS_HDDEC      "hrds_hddec"
  #define PR_HRDS_HDDEC_S    PR_TSS_S
  #define PR_HRDS_HDDEC      PR_TSS

  #define TN_HRDS_WEBMNG      "hrds_webmng"
  #define PR_HRDS_WEBMNG_S    PR_TSS_S
  #define PR_HRDS_WEBMNG      PR_TSS

  #define TN_HRDS_WEBCOM      "hrds_webcom"
  #define PR_HRDS_WEBCOM_S    PR_TSS_S
  #define PR_HRDS_WEBCOM      PR_TSS

#define MN_BT_CONNECTIONSERVICE      "BT_CnctSrv"
#define PR_BT_CONNECTIONSERVICE_S    PR_TSS_S
#define PR_BT_CONNECTIONSERVICE      PR_TSS

#define MN_BT_PHONESERVICE           "BT_PhoneSrv"
#define PR_BT_PHONESERVICE_S         PR_TSS_S
#define PR_BT_PHONESERVICE           PR_TSS

#define MN_BT_PHONEBOOKSERVICE       "BT_PbkSrv"
#define PR_BT_PHONEBOOKSERVICE_S     PR_TSS_S
#define PR_BT_PHONEBOOKSERVICE       PR_TSS

#define MN_BT_MESSAGINGSERVICE       "BT_MsgSrv"
#define PR_BT_MESSAGINGSERVICE_S     PR_TSS_S
#define PR_BT_MESSAGINGSERVICE       PR_TSS

#define MN_BT_BLLSERVICE             "TEL_BLLSrv"
#define PR_BT_BLLSERVICE_S           PR_TSS_S
#define PR_BT_BLLSERVICE             PR_TSS

#define MN_BT_DCMPHONESERVICE        "DCM_PhoneSrv"
#define PR_BT_DCMPHONESERVICE_S      PR_TSS_S
#define PR_BT_DCMPHONESERVICE        PR_TSS

  #define TN_BT_CONSRV_HFPMULTIQ1      "HFPMultiQ1"
  #define PR_TN_BT_CONSRV_HFPMULTIQ1_S PR_TSS_S
  #define PR_TN_BT_CONSRV_HFPMULTIQ1   PR_TSS

  #define TN_BT_CONSRV_HFPMULTIQ2      "HFPMultiQ2"
  #define PR_TN_BT_CONSRV_HFPMULTIQ2_S PR_TSS_S
  #define PR_TN_BT_CONSRV_HFPMULTIQ2   PR_TSS

  #define TN_BT_PBKSRV_DATABASE             "BTPB_Database"
  #define PR_TN_BT_PBKSRV_DATABASE_S        PR_TSS_S
  #define PR_TN_BT_PBKSRV_DATABASE          PR_TSS

  #define TN_BT_PBKSRV_LOCALPBINST          "LocalPBINST"
  #define PR_TN_BT_PBKSRV_LOCALPBINST_S     PR_TSS_S
  #define PR_TN_BT_PBKSRV_LOCALPBINST       PR_TSS

  #define TN_BT_PBKSRV_RESOLVENAME          "ResolveName"
  #define PR_TN_BT_PBKSRV_RESOLVENAME_S     PR_TSS_S
  #define PR_TN_BT_PBKSRV_RESOLVENAME       PR_TSS

  #define TN_BT_PBKSRV_PBAPMULTIQ1          "PBAPMultiQ1"
  #define PR_TN_BT_PBKSRV_PBAPMULTIQ1_S     PR_TSS_S
  #define PR_TN_BT_PBKSRV_PBAPMULTIQ1       PR_TSS

  #define TN_BT_PBKSRV_OPPMULTI             "OPPMulti"
  #define PR_TN_BT_PBKSRV_OPPMULTI_S        PR_TSS_S
  #define PR_TN_BT_PBKSRV_OPPMULTI          PR_TSS
  
  #define TN_BT_PBKSRV_VCARDPARSER          "VCardParser"
  #define PR_TN_BT_PBKSRV_VCARDPARSER_S     PR_TSS_S
  #define PR_TN_BT_PBKSRV_VCARDPARSER       PR_TSS

  #define TN_BT_MSGSRV_MSGCNTRLTHREAD0      "MsgCntrlThread0"
  #define PR_TN_BT_MSGSRV_MSGCNTRLTHREAD0_S PR_TSS_S
  #define PR_TN_BT_MSGSRV_MSGCNTRLTHREAD0   PR_TSS

  #define TN_BT_MSGSRV_MSGCNTRLTHREAD1      "MsgCntrlThread1"
  #define PR_TN_BT_MSGSRV_MSGCNTRLTHREAD1_S PR_TSS_S
  #define PR_TN_BT_MSGSRV_MSGCNTRLTHREAD1   PR_TSS

  #define TN_BT_MSGSRV_MAPMULTI             "MapMulti"
  #define PR_TN_BT_MSGSRV_MAPMULTI_S        PR_TSS_S
  #define PR_TN_BT_MSGSRV_MAPMULTI          PR_TSS

#define MN_DTVSERVICE         "DtvService"
#define PR_DTVSERVICE_S       PR_TSS_S
#define PR_DTVSERVICE         PR_TSS

  #define TN_DTVTNC_TX        "dtvtnc_tx"
  #define PR_DTVTNC_TX_S      PR_TSS_S
  #define PR_DTVTNC_TX        PR_TSS

  #define TN_DTVTNC_RCV       "dtvtnc_rcv"
  #define PR_DTVTNC_RCV_S     PR_TSS_S
  #define PR_DTVTNC_RCV       PR_TSS

  #define TN_DTVTNC_TIMER     "dtvtnc_timer"
  #define PR_DTVTNC_TIMER_S   PR_TSS_S
  #define PR_DTVTNC_TIMER     PR_TSS

  #define TN_DTVTNC_CTL       "dtvtnc_ctl"
  #define PR_DTVTNC_CTL_S     PR_TSS_S
  #define PR_DTVTNC_CTL       PR_TSS

#define MN_DTVVUPSERVICE      "DtvVupService"
#define PR_DTVVUPSERVICE_S    PR_TSS_S
#define PR_DTVVUPSERVICE      PR_TSS

#define MN_SETTINGSERVICE     "SettingService"
#define PR_SETTINGSERVICE_S   PR_TSS_S
#define PR_SETTINGSERVICE     PR_TSS

#define MN_INFOSETTINGSRV     "InfoSettingSrv"
#define PR_INFOSETTINGSRV_S   PR_TSS_S
#define PR_INFOSETTINGSRV     PR_TSS

  #define TN_INFS_UIC         "infs_uic"
  #define PR_INFS_UIC_S       PR_TSS_S
  #define PR_INFS_UIC         PR_TSS
 
#define MN_DELPERSONALSRV     "DelPersonalSrv"
#define PR_DELPERSONALSRV_S   PR_TSS_S
#define PR_DELPERSONALSRV     PR_TSS

#define MN_MENUSERVICE        "MenuService"
#define PR_MENUSERVICE_S      PR_TSS_S
#define PR_MENUSERVICE        PR_TSS

#define MN_NAVIPROXY          "NaviProxy"
#define PR_NAVIPROXY_S        PR_TSS_S
#define PR_NAVIPROXY          PR_TSS

#define MN_AWBPROXY           "AwbProxy"
#define PR_AWBPROXY_S         PR_TSS_S
#define PR_AWBPROXY           PR_TSS

#define MN_TFFPROXY           "TFFProxy"
#define PR_TFFPROXY_S         PR_TSS_S
#define PR_TFFPROXY           PR_TSS

#define MN_TFFPROXYSLAVE      "TFFProxySlave"
#define PR_TFFPROXYSLAVE_S    PR_TSS_S
#define PR_TFFPROXYSLAVE      PR_TSS

#define MN_AWNPRIMARY         "AwnPrimary"
#define PR_AWNPRIMARY_S       PR_TSS_S
#define PR_AWNPRIMARY         PR_TSS

#define MN_AWBPRIMARY         "AwbPrimary"
#define PR_AWBPRIMARY_S       PR_TSS_S
#define PR_AWBPRIMARY         PR_TSS

#define MN_AWMPRIMARY         "AwmPrimary"
#define PR_AWMPRIMARY_S       PR_TSS_S
#define PR_AWMPRIMARY         PR_TSS

#define MN_AWTPRIMARY         "AwtPrimary"
#define PR_AWTPRIMARY_S       PR_TSS_S
#define PR_AWTPRIMARY         PR_TSS

#define MN_MISINKSERVICE      "MisinkService"
#define PR_MISINKSERVICE_S    PR_TSS_S
#define PR_MISINKSERVICE      PR_TSS

#define MN_TEXTCONVERTER      "TextConverter"
#define PR_TEXTCONVERTER_S    PR_TSS_S
#define PR_TEXTCONVERTER      PR_TSS

#define MN_HANDWRITING        "HandWriting"
#define PR_HANDWRITING_S      PR_TSS_S
#define PR_HANDWRITING        PR_TSS

#define MN_EXTUNITAUTH_D      "EXTUNITAUTH_D"
#define PR_EXTUNITAUTH_D_S    "0"
#define PR_EXTUNITAUTH_D      0

  #define TN_VPSVC__CWORD84_        "VPSVC_D"
  #define PR_VPSVC__CWORD84__S      PR_TSS_S
  #define PR_VPSVC__CWORD84_        PR_TSS

#define MN_PROXYSERVICE       "ProxyService"
#define PR_PROXYSERVICE_S     PR_TSS_S
#define PR_PROXYSERVICE       PR_TSS

#define MN_FUELSERVICE        "VS_FUCSrv"
#define PR_FUELSERVICE_S      PR_TSS_S
#define PR_FUELSERVICE        PR_TSS

#define MN_ENERGYSERVICE      "VS_ENMSrv"
#define PR_ENERGYSERVICE_S    PR_TSS_S
#define PR_ENERGYSERVICE      PR_TSS

#define MN_CUSTOMIZESERVICE   "VS_VSDSrv"
#define PR_CUSTOMIZESERVICE_S PR_TSS_S
#define PR_CUSTOMIZESERVICE   PR_TSS

#define MN_DMSSERVICE         "VS_DMSSrv"
#define PR_DMSSERVICE_S       PR_TSS_S
#define PR_DMSSERVICE         PR_TSS

#define MN_AIRCONSERVICE      "VS_ACNSrv"
#define PR_AIRCONSERVICE_S    PR_TSS_S
#define PR_AIRCONSERVICE      PR_TSS

#define MN_SEATSERVICE        "VS_NMSSrv"
#define PR_SEATSERVICE_S      PR_TSS_S
#define PR_SEATSERVICE        PR_TSS

#define MN_CAMERASERVICE      "VS_CMRSrv"
#define PR_CAMERASERVICE_S    PR_TSS_S
#define PR_CAMERASERVICE      PR_TSS

  #define TN_CAMERAQUICKRVC   "QuickRVCThread"
  #define PR_CAMERAQUICKRVC_S PR_TSS_S
  #define PR_CAMERAQUICKRVC   PR_TSS

#define MN_METSERVICE         "VS_METSrv"
#define PR_METSERVICE_S       PR_TSS_S
#define PR_METSERVICE         PR_TSS

#define MN_TMCSERVICE         "VS_TMCSrv"
#define PR_TMCSERVICE_S       PR_TSS_S
#define PR_TMCSERVICE         PR_TSS

#define MN_DASSERVICE         "VS_DASSrv"
#define PR_DASSERVICE_S       PR_TSS_S
#define PR_DASSERVICE         PR_TSS

#define MN_EXTUNITAUTH_M      "EXTUNITAUTH_M"
#define PR_EXTUNITAUTH_M_S    "0"
#define PR_EXTUNITAUTH_M      0

#define MN_DUMMYREAD         "DummyRead"
#define PR_DUMMYREAD_S       PR_TSS_S
#define PR_DUMMYREAD         PR_TSS

#define MN_SSTSERVICE         "storage_access"
#define PR_SSTSERVICE_S       PR_TSS_S
#define PR_SSTSERVICE         PR_TSS

#define MN_CCSAUDITD         "ccs-auditd"
#define PR_CCSAUDITD_S       PR_TSS_S
#define PR_CCSAUDITD         PR_TSS

//exec from task manager
#define MN_ACTIVITYMANAGER    "ActivityManager"
#define PR_ACTIVITYMANAGER_S  PR_TSS_S
#define PR_ACTIVITYMANAGER    PR_TSS

#define MN_RESIDENT_SVC       "RESIDENT_SVC"
#define PR_RESIDENT_SVC_S     PR_TSS_S
#define PR_RESIDENT_SVC       PR_TSS

#define MN_TRANSIENT_SVC      "TRANSIENT_SVC"
#define PR_TRANSIENT_SVC_S    PR_TSS_S
#define PR_TRANSIENT_SVC      PR_TSS

#define MN_WLANSERVICE        "wlan_ctrl_0700"
#define PR_WLANSERVICE_S      PR_TSS_S
#define PR_WLANSERVICE        PR_TSS

#define MN_WLANEVTTHR         "WlanEvtThr"
#define PR_WLANEVTTHR_S       PR_TSS_S
#define PR_WLANEVTTHR         PR_TSS

#define MN_WLANMIDDLESERVICE     "WlanMiddle"
#define PR_WLANMIDDLESERVICE_S   PR_TSS_S
#define PR_WLANMIDDLESERVICE     PR_TSS

  #define TN_WLANMIDDLESERVICE0    "WM_MsgCtrlTh0"
  #define PR_WLANMIDDLESERVICE0_S  PR_TSS_S
  #define PR_WLANMIDDLESERVICE0    PR_TSS

  #define TN_WLANMIDDLESERVICE1    "WM_MsgCtrlTh1"
  #define PR_WLANMIDDLESERVICE1_S  PR_TSS_S
  #define PR_WLANMIDDLESERVICE1    PR_TSS

  #define TN_WLANMIDDLESERVICE2    "WM_MsgCtrlTh2"
  #define PR_WLANMIDDLESERVICE2_S  PR_TSS_S
  #define PR_WLANMIDDLESERVICE2    PR_TSS

#define MN_WLANSERVICE2       "wlan_ctrl_0701"
#define PR_WLANSERVICE2_S     PR_TSS_S
#define PR_WLANSERVICE2       PR_TSS

#define MN_WLANEVTTHR2        "WlanEvtThr2"
#define PR_WLANEVTTHR2_S      PR_TSS_S
#define PR_WLANEVTTHR2        PR_TSS

//exec from task manager, Test for vup
#define MN_PS__CWORD52_VUP        "_CWORD52_vup"
#define PR_PS__CWORD52_VUP_S      PR_TSS_S
#define PR_PS__CWORD52_VUP        PR_TSS

#define MN_PS_SYSVUP          "sysvup"
#define PR_PS_SYSVUP_S        PR_TSS_S
#define PR_PS_SYSVUP          PR_TSS

#define MN_SS_ROOTFSVUP       "rootfsvup"
#define PR_SS_ROOTFSVUP_S     PR_TSS_S
#define PR_SS_ROOTFSVUP       PR_TSS

#define MN_SS_VUPPROGUI       "vupprogressui"
#define PR_SS_VUPPROGUI_S     PR_TSS_S
#define PR_SS_VUPPROGUI       PR_TSS

#define MN_SS_NORVUP          "norvup"
#define PR_SS_NORVUP_S        PR_TSS_S
#define PR_SS_NORVUP          PR_TSS

// OUTER_UPDATE START
#define MN_XMVUPSERVICE      "radio_xm_update"
#define PR_XMVUPSERVICE_S    PR_TSS_S
#define PR_XMVUPSERVICE      PR_TSS
// OUTER_UPDATE END

#define MN_BTPHONESRV         "BT_PhoneSrv"
#define PR_BTPHONESRV_S       PR_TSS_S
#define PR_BTPHONESRV         PR_TSS

#define MN_BTPBKSRV           "BT_PbkSrv"
#define PR_BTPBKSRV_S         PR_TSS_S
#define PR_BTPBKSRV           PR_TSS

#define MN_BTMSGSRV           "BT_MsgSrv"
#define PR_BTMSGSRV_S         PR_TSS_S
#define PR_BTMSGSRV           PR_TSS

// NON-resident, exec from task manager, Repro update
#define MN_PS_SYSUPDATE       "sysupdate"
#define PR_PS_SYSUPDATE_S     PR_TSS_S
#define PR_PS_SYSUPDATE       PR_TSS

#define MN_SS_NANDUPDATE      "nandupdate"
#define PR_SS_NANDUPDATE_S    PR_TSS_S
#define PR_SS_NANDUPDATE      PR_TSS

  #define TN_NANDUPDATE_CLD    "t_nandcld"
  #define PR_NANDUPDATE_CLD_S  PR_TSS_S
  #define PR_NANDUPDATE_CLD    PR_TSS

#define MN_BTPHONESRV         "BT_PhoneSrv"
#define PR_BTPHONESRV_S       PR_TSS_S
#define PR_BTPHONESRV         PR_TSS

#define MN_BTPBKSRV           "BT_PbkSrv"
#define PR_BTPBKSRV_S         PR_TSS_S
#define PR_BTPBKSRV           PR_TSS

#define MN_BTMSGSRV           "BT_MsgSrv"
#define PR_BTMSGSRV_S         PR_TSS_S
#define PR_BTMSGSRV           PR_TSS

//exec from diag
#define MN_DIAGSERVICE        "DiagService"
#define PR_DIAGSERVICE_S      PR_TSS_S
#define PR_DIAGSERVICE        PR_TSS

#define MN_DIAGWORKERTSK      "diagworker_tsk"
#define PR_DIAGWORKERTSK_S    PR_TSS_S
#define PR_DIAGWORKERTSK      PR_TSS

#define MN_DIAGTSK            "diag_tsk"
#define PR_DIAGTSK_S          PR_TSS_S
#define PR_DIAGTSK            PR_TSS

#define MN_DIAGMCTSK          "diagmc_tsk"
#define PR_DIAGMCTSK_S        PR_TSS_S
#define PR_DIAGMCTSK          PR_TSS

#define MN_DIAGUTCOL          "diagutCol_tsk"
#define PR_DIAGUTCOL_S        PR_TSS_S
#define PR_DIAGUTCOL          PR_TSS

#define MN_DIAGUTUPD          "diagutUpd_tsk"
#define PR_DIAGUTUPD_S        PR_TSS_S
#define PR_DIAGUTUPD          PR_TSS

//exec from Connectivity for _CWORD57_
#define MN__CWORD57_UTILSERVICE    "_CWORD57_UtilService"
#define PR__CWORD57_UTILSERVICE_S  PR_TSS_S
#define PR__CWORD57_UTILSERVICE    PR_TSS

  #define TN_CON_IPUT_DETECT    "iputsrv_detect"
  #define PR_CON_IPUT_DETECT_S  PR_TSS_S
  #define PR_CON_IPUT_DETECT    PR_TSS

  #define TN_CON_IPUT_AUTH      "iputsrv_auth"
  #define PR_CON_IPUT_AUTH_S    PR_TSS_S
  #define PR_CON_IPUT_AUTH      PR_TSS

  #define TN_CON_IPUT_SERIAL    "iputsrv_serial"
  #define PR_CON_IPUT_SERIAL_S  PR_TSS_S
  #define PR_CON_IPUT_SERIAL    PR_TSS

  #define TN_CON_IPUT_USB_1    "iputsrv_usb1"
  #define PR_CON_IPUT_USB_1_S  PR_TSS_S
  #define PR_CON_IPUT_USB_1    PR_TSS

  #define TN_CON_IPUT_USB_2    "iputsrv_usb2"
  #define PR_CON_IPUT_USB_2_S  PR_TSS_S
  #define PR_CON_IPUT_USB_2    PR_TSS

  #define TN_CON_IPUT_SPP      "iputsrv_spp"
  #define PR_CON_IPUT_SPP_S    PR_TSS_S
  #define PR_CON_IPUT_SPP      PR_TSS

#define MN__CWORD57_DTSERVICE    "_CWORD57_DTService"
#define PR__CWORD57_DTSERVICE_S  PR_TSS_S
#define PR__CWORD57_DTSERVICE    PR_TSS

  #define TN_CON_IPDT_SERIAL    "ipdtsrv_serial"
  #define PR_CON_IPDT_SERIAL_S  PR_TSS_S
  #define PR_CON_IPDT_SERIAL    PR_TSS

  #define TN_CON_IPDT_USB_1    "ipdtsrv_usb1"
  #define PR_CON_IPDT_USB_1_S  PR_TSS_S
  #define PR_CON_IPDT_USB_1    PR_TSS

  #define TN_CON_IPDT_USB_2    "ipdtsrv_usb2"
  #define PR_CON_IPDT_USB_2_S  PR_TSS_S
  #define PR_CON_IPDT_USB_2    PR_TSS

  #define TN_CON_IPDT_SPP      "ipdtsrv_spp"
  #define PR_CON_IPDT_SPP_S    PR_TSS_S
  #define PR_CON_IPDT_SPP      PR_TSS

#define MN_WEBDAVMGR          "webdavmgr"
#define PR_WEBDAVMGR_S        PR_TSS_S
#define PR_WEBDAVMGR          PR_TSS

#define MN_DISPLAYSERVICE     "DisplayService"
#define PR_DISPLAYSERVICE_S   PR_TSS_S
#define PR_DISPLAYSERVICE     PR_TSS

#define MN_ENFORMSERVICE      "EnformService"
#define PR_ENFORMSERVICE_S    PR_TSS_S
#define PR_ENFORMSERVICE      PR_TSS

#define MN_CONNUTIL           "ConnUtil"
#define PR_CONNUTIL_S         PR_TSS_S
#define PR_CONNUTIL           PR_TSS

#define MN_CONNUTILSLAVE      "ConnUtilSlave"
#define PR_CONNUTILSLAVE_S    PR_TSS_S
#define PR_CONNUTILSLAVE      PR_TSS

#define MN_CONNMGR            "ConnMgr"
#define PR_CONNMGR_S          PR_TSS_S
#define PR_CONNMGR            PR_TSS

#define MN_SERVICEFLAGMGR     "ServiceFlagMgr"
#define PR_SERVICEFLAGMGR_S   PR_TSS_S
#define PR_SERVICEFLAGMGR     PR_TSS

//exec from VR
#define MN_VRMANAGER    "vrmanager"
#define PR_VRMANAGER_S  PR_TSS_S
#define PR_VRMANAGER    PR_TSS

  #define TN_VR_WORKER    "VrWorkerThread"
  #define PR_VR_WORKER_S  PR_TSS_S
  #define PR_VR_WORKER    PR_TSS

  #define TN_VBT_PROPDISPATCH    "PropDispatchThread"
  #define PR_VBT_PROPDISPATCH_S  PR_TSS_S
  #define PR_VBT_PROPDISPATCH    PR_TSS

  #define TN_VBT_PROPRESPONSE    "PropResponseThread"
  #define PR_VBT_PROPRESPONSE_S  PR_TSS_S
  #define PR_VBT_PROPRESPONSE    PR_TSS

  #define TN_VBT_PROPAUDIOPLAY    "PropAudioPlayThread"
  #define PR_VBT_PROPAUDIOPLAY_S  PR_TSS_S
  #define PR_VBT_PROPAUDIOPLAY    PR_TSS

  #define TN_VBT_PROPAUDIORECORD    "PropAudioRecordThread"
  #define PR_VBT_PROPAUDIORECORD_S  PR_TSS_S
  #define PR_VBT_PROPAUDIORECORD    PR_TSS

  #define TN_VBT_MAINTHREADPRIO    "MainThreadPriority"
  #define PR_VBT_MAINTHREADPRIO_S  PR_TSS_S
  #define PR_VBT_MAINTHREADPRIO    PR_TSS

  #define TN_VBT_ASRMANAGERGRAMMAR    "AsrManagerGrammarGenerationThread"
  #define PR_VBT_ASRMANAGERGRAMMAR_S  PR_TSS_S
  #define PR_VBT_ASRMANAGERGRAMMAR    PR_TSS

  #define TN_VBT_ASRVOCONRECO    "AsrVoconRecoProcessThread"
  #define PR_VBT_ASRVOCONRECO_S  PR_TSS_S
  #define PR_VBT_ASRVOCONRECO    PR_TSS

  #define TN_VBT_BROADCASTREAD    "BroadCastReadThread"
  #define PR_VBT_BROADCASTREAD_S  PR_TSS_S
  #define PR_VBT_BROADCASTREAD    PR_TSS

  #define TN_VBT_FILEAGGREGATOR    "FileAggregatorDecompressThread"
  #define PR_VBT_FILEAGGREGATOR_S  PR_TSS_S
  #define PR_VBT_FILEAGGREGATOR    PR_TSS

  #define TN_VBT_HTTPCURLREQUEST    "HttpCurlRequestThread"
  #define PR_VBT_HTTPCURLREQUEST_S  PR_TSS_S
  #define PR_VBT_HTTPCURLREQUEST    PR_TSS

  #define TN_VBT_HTTPDRIVERREQUEST    "HttpDriverRequestThread"
  #define PR_VBT_HTTPDRIVERREQUEST_S  PR_TSS_S
  #define PR_VBT_HTTPDRIVERREQUEST    PR_TSS

  #define TN_VBT_HTTPREQUESTSESSION    "HttpRequestSessionStateThread"
  #define PR_VBT_HTTPREQUESTSESSION_S  PR_TSS_S
  #define PR_VBT_HTTPREQUESTSESSION    PR_TSS

  #define TN_VBT_PLAYMGRSTOPASYNC    "PlayMgrStopAsyncStreamThread"
  #define PR_VBT_PLAYMGRSTOPASYNC_S  PR_TSS_S
  #define PR_VBT_PLAYMGRSTOPASYNC    PR_TSS

  #define TN_VBT_RESOURCEMGRQUEUE    "ResourceMgrQueueHandlerThread"
  #define PR_VBT_RESOURCEMGRQUEUE_S  PR_TSS_S
  #define PR_VBT_RESOURCEMGRQUEUE    PR_TSS

  #define TN_VBT_SMURFDRIVERTIMEOUT    "SmurfDriverTimeoutThread"
  #define PR_VBT_SMURFDRIVERTIMEOUT_S  PR_TSS_S
  #define PR_VBT_SMURFDRIVERTIMEOUT    PR_TSS

  #define TN_NVR_NVRMAIN    "NvrMainThread"
  #define PR_NVR_NVRMAIN_S  PR_TSS_S
  #define PR_NVR_NVRMAIN    PR_TSS

  #define TN_NVR_NVRRECO    "NvrRecoThread"
  #define PR_NVR_NVRRECO_S  PR_TSS_S
  #define PR_NVR_NVRRECO    PR_TSS

  #define TN_NVR_NVRDICT    "NvrDictThread"
  #define PR_NVR_NVRDICT_S  PR_TSS_S
  #define PR_NVR_NVRDICT    PR_TSS

  #define TN_NVR_NVRENC    "NvrEncThread"
  #define PR_NVR_NVRENC_S  PR_TSS_S
  #define PR_NVR_NVRENC    PR_TSS

//exec from VehicleInfo
#define MN_VEHICLEINFOSERVICE        "VehicleInfoSrv"
#define PR_VEHICLEINFOSERVICE_S      PR_TSS_S
#define PR_VEHICLEINFOSERVICE        PR_TSS

//exec from _CWORD58_
#define MN__CWORD58_SERVICE        "_CWORD58_Service"
#define PR__CWORD58_SERVICE_S      PR_TSS_S
#define PR__CWORD58_SERVICE        PR_TSS

#define MN__CWORD8_SRV     "_CWORD8_Srv"
#define PR__CWORD8_SRV_S   PR_TSS_S
#define PR__CWORD8_SRV     PR_TSS

#define MN_SPCSERVICE         "SPCService"
#define PR_SPCSERVICE_S       PR_TSS_S
#define PR_SPCSERVICE         PR_TSS

#define MN_LOCALSERVERPROXY    "LSP"
#define PR_LOCALSERVERPROXY_S  PR_TSS_S
#define PR_LOCALSERVERPROXY    PR_TSS

#define MN_EOMSERVICE          "eOMService"
#define PR_EOMSERVICE_S        PR_TSS_S
#define PR_EOMSERVICE          PR_TSS

//exec from _CWORD89_
#define MN__CWORD89_SERVICE         "_CWORD89_Service"
#define PR__CWORD89_SERVICE_S       PR_TSS_S
#define PR__CWORD89_SERVICE         PR_TSS

//exec from NetworkManager
#define MN_NETWORKMANAGER       "NetworkManager"
#define PR_NETWORKMANAGER_S     PR_TSS_S
#define PR_NETWORKMANAGER       PR_TSS

  #define TN_NWM_TH_CMDRCV      "NWM_Th_CmdRcv"
  #define PR_NWM_TH_CMDRCV_S    PR_TSS_S
  #define PR_NWM_TH_CMDRCV      PR_TSS

  #define TN_NWM_TH_PROCMGR     "NWM_Th_ProcMgr"
  #define PR_NWM_TH_PROCMGR_S   PR_TSS_S
  #define PR_NWM_TH_PROCMGR     PR_TSS

  #define TN_NWM_TH_CMDPROC     "NWM_Th_CmdProc"
  #define PR_NWM_TH_CMDPROC_S   PR_TSS_S
  #define PR_NWM_TH_CMDPROC     PR_TSS

  #define TN_NWM_TH_DNSMGR      "NWM_Th_DnsMgr"
  #define PR_NWM_TH_DNSMGR_S    PR_TSS_S
  #define PR_NWM_TH_DNSMGR      PR_TSS

  #define TN_NWM_TH_DHCPD      "NWM_Th_Dhcpd"
  #define PR_NWM_TH_DHCPD_S    PR_TSS_S
  #define PR_NWM_TH_DHCPD      PR_TSS

// DCM Service
#define MN_DCMSERVICE         "DCMService"
#define PR_DCMSERVICE_S       PR_TSS_S
#define PR_DCMSERVICE         PR_TSS

  #define TN_DCM_TH_CMDRCV      "DCM_Th_CmdRcv"
  #define PR_DCM_TH_CMDRCV_S    PR_TSS_S
  #define PR_DCM_TH_CMDRCV      PR_TSS

  #define TN_DCM_TH_MSGRCV      "DCM_Th_MsgRcv"
  #define PR_DCM_TH_MSGRCV_S    PR_TSS_S
  #define PR_DCM_TH_MSGRCV      PR_TSS

  #define TN_DCM_TH_TIMER       "DCM_Th_Timer"
  #define PR_DCM_TH_TIMER_S     PR_TSS_S
  #define PR_DCM_TH_TIMER       PR_TSS

// HELP Service
#define MN_HELPSERVICE        "HELPService"
#define PR_HELPSERVICE_S      PR_TSS_S
#define PR_HELPSERVICE        PR_TSS

//exec from RemoteService
#define MN_REMOTESERVICE        "RemoteService"
#define PR_REMOTESERVICE_S      PR_TSS_S
#define PR_REMOTESERVICE        PR_TSS

  #define TN_RS_TH_CANCTRL      "RS_Th_CANCtrl"
  #define PR_RS_TH_CANCTRL_S    PR_TSS_S
  #define PR_RS_TH_CANCTRL      PR_TSS

  #define TN_RS_TH_DISPCTRL     "RS_Th_DispCtrl"
  #define PR_RS_TH_DISPCTRL_S   PR_TSS_S
  #define PR_RS_TH_DISPCTRL     PR_TSS

  #define TN_RS_TH_PARTSCTRL    "RS_Th_PartsCtrl"
  #define PR_RS_TH_PARTSCTRL_S  PR_TSS_S
  #define PR_RS_TH_PARTSCTRL    PR_TSS

  #define TN_RS_TH_HTTPPROC     "RS_Th_HttpProc"
  #define PR_RS_TH_HTTPPROC_S   PR_TSS_S
  #define PR_RS_TH_HTTPPROC     PR_TSS

//exec from VR
#define MN_CONTENTSMGR    "contentsmgr"
#define PR_CONTENTSMGR_S  PR_TSS_S
#define PR_CONTENTSMGR    PR_TSS

  #define TN_CDB_CONTENDB    "contendbThread"
  #define PR_CDB_CONTENDB_S  PR_TSS_S
  #define PR_CDB_CONTENDB    PR_TSS

/* COMARB Service */
#define MN_NW_COMARB          "ComArbService"
#define PR_NW_COMARB_S        PR_TSS_S
#define PR_NW_COMARB          PR_TSS

/* ASND_FRthread */
#define MN_ASND_FRTH         "ASND_FRthread"
#define PR_ASND_FRTH_S       PR_SND_VCETRFCTRL_S
#define PR_ASND_FRTH         PR_SND_VCETRFCTRL

/* MLINK Service */
#define MN_MLINKSERVICE       "MlinkService"
#define PR_MLINKSERVICE_S     PR_TSS_S
#define PR_MLINKSERVICE       PR_TSS

#define MN__CWORD74_SERVICE "_CWORD74_Service"
#define PR__CWORD74_SERVICE_S PR_TSS_S
#define PR__CWORD74_SERVICE PR_TSS 
#endif //__AGL_THREAD_H__
