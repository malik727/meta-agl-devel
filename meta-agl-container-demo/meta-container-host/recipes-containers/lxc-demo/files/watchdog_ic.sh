#!/bin/sh

watch_file=/var/local/lib/containers/GUEST_IVI/etc/lxc/trigger-reboot-container-ic

while inotifywait -e OPEN $watch_file; do
	sync
	/usr/bin/lxc-attach -n GUEST_IC -- halt -f
	# hack
	/usr/bin/lxc-attach -n GUEST_IVI -- /usr/bin/restore-tbt.sh
	sleep 1
	/usr/bin/lxc-attach -n GUEST_IVI -- /usr/bin/restore-tbt.sh
	sleep 1
	/usr/bin/lxc-attach -n GUEST_IVI -- /usr/bin/restore-tbt.sh
done
