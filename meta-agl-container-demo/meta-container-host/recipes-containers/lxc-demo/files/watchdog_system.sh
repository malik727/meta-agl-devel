#!/bin/sh

watch_file=/var/local/lib/containers/GUEST_IVI/etc/lxc/trigger-reboot-system

while inotifywait -e OPEN $watch_file; do
	sync
	reboot -f
done
