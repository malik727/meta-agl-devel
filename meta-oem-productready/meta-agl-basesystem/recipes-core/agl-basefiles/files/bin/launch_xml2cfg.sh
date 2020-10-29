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

#Since xpath is slow, use sed as much as possible.

infile=$1
main_file=system_launcher_main.xml
body_file=system_launcher_body.xml


#check xmllint is exist 
if ! which xmllint > /dev/null ; then
  echo "It need xmllint. Please install it."
  exit 1;
fi 

#check xpath is exist 
if ! which xpath > /dev/null ; then
  echo "It need xpath Please install it."
  exit 1;
fi 

#arg check
if ! [[ "$infile" =~ .+\.xml ]] ;then
  echo "$infile is not *.xml"
  exit 1
elif ! [ -e $infile ];then
  echo "$infile not found"
  exit 1
fi

cp -f `dirname $0`/$main_file `dirname $1`
cp -f $infile $body_file

#check xml vaild 
if ! xmllint --noout --valid $main_file ;then
  echo "XML is Invalid. "
  exit 1;
fi

#Format into xpath and read into memory
xmem=`xpath -q -e /system_launcher $main_file`

echo "#  This file is created from $infile."
echo "#  created date : `LANG=en date`"
echo "[ModulesLaunchConfig]"

#GROUP LOOP
group_num=`echo $xmem | xpath -e /system_launcher/group 2>&1 | grep Found | cut -d ' ' -f2`

l_idx=1
cur_group=1
until [ $cur_group -gt $group_num ];  
do
  #LAUNCH LOOP
  group_text=`echo $xmem | xpath -q -e /system_launcher/group[$cur_group]`  #ALL XML text for group
  group_attr=`echo $group_text | sed 's/\(<group[^>]\+>\)\(.*\)/\1/g'`

  g_name=`echo $group_attr | sed 's/\(.* name="\)\([^"]*\)\(.*\)/\2/g'`
  g_wait_time=`echo $group_attr | sed 's/\(.* wait_time="\)\([^"]*\)\(.*\)/\2/g'`
  g_trigger=`echo $group_attr | sed 's/\(.* trigger="\)\([^"]*\)\(.*\)/\2/g'`

#  echo $g_name $g_wait_time $g_trigger
  l_launch_num=`echo $xmem | xpath -e /system_launcher/group[$cur_group]/launch  2>&1 | grep Found | cut -d ' ' -f2`
  
  cur_launch=1; 
  until [ $cur_launch -gt $l_launch_num ];  do
    launch_text=`echo $xmem | xpath -q -e /system_launcher/group[$cur_group]/launch[$cur_launch]`  
    
    l_attr="Launch${l_idx}=$g_name|$cur_group|$g_wait_time|$g_trigger"
    l_attr+="|"`echo $launch_text | sed 's/\(.* name="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* path="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* priority="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* critical="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* retry_cnt="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* arguments="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* logging_mask="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* restart="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* is_start_required="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* shutdown_critical="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* shutdown_wait_time="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* fast_shutdown_wait_time="\)\([^"]*\)\(.*\)/\2/g'`
    l_attr+="|"`echo $launch_text | sed 's/\(.* user_name="\)\([^"]*\)\(.*\)/\2/g'`
    if echo "$launch_text" | grep -sq 'is_agl_unit=' ; then
      l_attr+="|"`echo $launch_text | sed 's/\(.* is_agl_unit="\)\([^"]*\)\(.*\)/\2/g'`
    else
      l_attr+="|"
    fi
    if echo "$launch_text" | grep -sq 'disable_agl_resethistory=' ; then
      l_attr+="|"`echo $launch_text | sed 's/\(.* disable_agl_resethistory="\)\([^"]*\)\(.*\)/\2/g'`
    else
      l_attr+="|"
    fi
    if echo "$launch_text" | grep -sq 'disable_nonagl_resethistory=' ; then
      l_attr+="|"`echo $launch_text | sed 's/\(.* disable_nonagl_resethistory="\)\([^"]*\)\(.*\)/\2/g'`
    else
      l_attr+="|"
    fi
    if echo "$launch_text" | grep -sq 'env_cond=' ; then
      l_attr+="|"`echo $launch_text | sed 's/\(.* env_cond="\)\([^"]*\)\(.*\)/\2/g'`
    else
      l_attr+="|"
    fi
    
    if echo "$launch_text" | grep -sq 'cpu_assign=' ; then
      l_attr+="|"`echo $launch_text | sed 's/\(.* cpu_assign="\)\([^"]*\)\(.*\)/\2/g'`
    else
      l_attr+="|0x0"
    fi

    echo $l_attr

    cur_launch=$(($cur_launch+1))
    l_idx=$(($l_idx+1))
  done

  cur_group=$(($cur_group+1))
done


rm $body_file
rm $main_file


