#!/bin/bash
#
# @copyright Copyright (c) 2019 TOYOTA MOTOR CORPORATION.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

ROMFILESTOP=/
CAP_LST=${ROMFILESTOP}/usr/target/agl_cap.lst
echo `cat ${CAP_LST}`
#-----------------------------------------------------------------------
# Capability

df -T / | grep nfs > /dev/null
IS_EMMC_BOOT=$?

#*********************from init_nfs_cap.sh**************************

echo "init_nfs-cap.sh: Start"

VERBOSE=y
SKIPWARN=n
#-----------------------------------------------------------------------
# Set Capability for NFS or Set DummyLink for ROM
#CAP_LST="/usr/debug/share/target/cap.lst"
CAP_LST="/usr/target/agl_cap.lst"

if [ $IS_EMMC_BOOT -eq 0 ]; then
if [ -f "${CAP_LST}" ];then
    echo "*** set capability for NFS environment ***"
  CAPPATH=/tmp/
  cd /
    for PREAD in `cat ${CAP_LST}`
    do
      IFS_ORG=${IFS} ; IFS='|' ; PARAM=(${PREAD}) ; IFS=${IFS_ORG}
      CAP_NAME=${PARAM[0]} ; FMODE=${PARAM[1]} ; FUID_GID=${PARAM[2]}
      FCAP=${PARAM[3]} ; FKEEPORGPATH=${PARAM[4]}
      if [ ! -f "${CAP_NAME}" -a ! -f "${CAP_NAME}.org" ];then
        if [ "${SKIPWARN}" = "n" ];then
          echo "set capability: ${CAP_NAME}: No such file or directory" 1>&2
        fi
        continue
      fi
      TCAP_NAME="/tmp/${CAP_NAME##*/}"
      # Set Capability for NFS
        if [ ! -L "${CAP_NAME}" ]; then
          cp -a ${CAP_NAME} ${TCAP_NAME}
          if [ "${FKEEPORGPATH}" = "y" ];then
            mv ${CAP_NAME} ${CAP_NAME}.org
            ln -fs ${TCAP_NAME} ${CAP_NAME}
          fi
        else
          cp -a ${CAP_NAME}.org ${TCAP_NAME}
        fi
        if [ -n "${FUID_GID}" ];then
          chown ${FUID_GID} ${TCAP_NAME}
        fi
        if [ -n "${FMODE}" ];then
          chmod ${FMODE} ${TCAP_NAME}
        fi
        if [ -n "${FCAP}" ];then
          setcap ${FCAP} ${TCAP_NAME}
          #if [ "${VERBOSE}" = "y" ];then
          #  getcap ${TCAP_NAME}
          #fi
        fi
    done
  cd - > /dev/null
else
  unset CAPPATH
fi
fi
