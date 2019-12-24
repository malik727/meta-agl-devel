#
# 'tty=' option for drm-backend causes error when wayland-backend
# so override instead append
#
WESTONARGS = "--idle-time=0 --backend=wayland-backend.so --display=wayland-host-0 --width=1920 --height=1080"

do_install_append() {
    sed -e "s/TTY.*/#&/g" \
        -e "s/StandardInput=.*/#&/g" \
        -e "s/UtmpIdentifier=.*/#&/g" \
        -i ${D}${systemd_system_unitdir}/weston.service
}
