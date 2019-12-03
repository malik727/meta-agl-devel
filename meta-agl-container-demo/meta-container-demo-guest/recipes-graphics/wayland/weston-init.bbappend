#
# 'tty=' option for drm-backend causes error when wayland-backend
# so override instead append
#
WESTONARGS = "--idle-time=0 --backend=wayland-backend.so --display=wayland-host-0 "
WESTONARGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'agl-demo-ivi', '--output-count=2 --width=1080 --height=1920', '', d)}"
WESTONARGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'agl-demo-ic', '--width=1920 --height=1080', '', d)}"