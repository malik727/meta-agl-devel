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

#to expand msg_max
sysctl -w fs.mqueue.msg_max=512

# device detection
echo -n "TARGET_BOARD=" > /tmp/udev_device.env
cat /proc/device-tree/model | cut -d " " -f 2 >> /tmp/udev_device.env
echo >> /tmp/udev_device.env
echo "UID=$INIT_UID" >> /tmp/udev_device.env
echo "GID=$INIT_GID" >> /tmp/udev_device.env
echo "BRAND=$VEHICLEPARAMETERLIBRARY_BRAND" >> /tmp/udev_device.env
echo "AREA=$VEHICLEPARAMETERLIBRARY_AREA" >> /tmp/udev_device.env

# Start: Workaround for release ###############################################
## Sprint 29 To make WebService can update contents.
#chown -R agl:agl /usr/agl/data/electronicom
## For btservice initial data.
#chown -R agl:agl /nv/backup/D_BK_CA_BT_MANAGEMENT 
## Sprint 29 PFDRECThread
mkdir -p /ramd/BS/ns/backup_manager/rwdata
mkdir -p /ramd/BS/ss/logger_service/rwdata/frameworkunifiedlog/diag
restorecon -R /ramd
#chmod 777 /ramd/BS/ss/logger_service/rwdata/frameworkunifiedlog/diag
## Sprint 29 communication
#chmod -R 777 /home/root/.app_can_d
# TODO:for bluetooth_service
#chmod 777 /usr/agl/share

#if `df -T / | grep nfs > /dev/null`; then
#cp /sbin/insmod.kmod /tmp/insmod.kmod
#ln -s -f /tmp/insmod.kmod /sbin/insmod
#setcap cap_sys_module+ep /tmp/insmod.kmod
#fi

## Sprint 32 Positioning
#chmod 777 /dev/ttySC3
#chmod -R 777 /home/root/.app_gps_cmd_d

## Sprint 37 BUG17P-9 clock
ln -f -s /tmp/bs/clock/localtime /etc/localtime

# END: Workaround for release #################################################

# permission setting
# wait for weston is properly launched
#until [ -e /run/user/0/wayland-0 ]
#do
#	usleep 50000
#done
#chmod 777 /run/user/0/wayland-0

mkdir /tmp/shm

chmod 777 /tmp/shm
chmod 666 /dev/mqueue/IccSnd
#chmod 777 /dev/mqueue/*
#chmod 777 /dev/mqueue/NS_NPPService
#chmod 777 /run/user/0

rm -rf /nv/romaccess
rm /dev/shm/lockfile




export PATH=`echo -n ${PATH} | sed 's|/tmp:||'`

