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

desired_rt_runtime_us=$1
mygroup=${2:-$(awk -F: '$2 == "cpu,cpuacct" {print $3}' /proc/self/cgroup)}

[[ $desired_rt_runtime_us -gt 0 ]] || exit
[[ $mygroup ]] || exit
[[ $mygroup = / ]] && exit

echo "${0##*/}: setting cpu.rt_runtime_us for $mygroup" >&2

cgpath=
IFS=/ read -ra cgroups <<< "${mygroup:1}"
for cg in "${cgroups[@]}"; do
  cgpath="${cgpath}/${cg}"
  echo "${0##*/}: $desired_rt_runtime_us -> /sys/fs/cgroup/cpu,cpuacct${cgpath}" >&2
  echo "$desired_rt_runtime_us" > /sys/fs/cgroup/cpu,cpuacct${cgpath}/cpu.rt_runtime_us
done
