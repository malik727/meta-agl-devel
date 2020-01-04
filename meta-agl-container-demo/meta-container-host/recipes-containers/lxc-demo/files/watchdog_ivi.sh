#!/bin/sh

watch_file=/var/local/lib/containers/GUEST_IVI/etc/lxc/trigger-reboot-container-ivi

while inotifywait -e OPEN $watch_file; do
	sync
	/usr/bin/lxc-attach -n GUEST_IVI -- halt -f
done
