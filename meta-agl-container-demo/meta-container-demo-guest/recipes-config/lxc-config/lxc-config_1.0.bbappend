FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

AGL_CONTAINER_MAC_ADDR ??= "00:16:3e:cf:07:ff"

SRC_URI_append = " \
    file://100_compositor.cfg \
    "

SRC_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'agl-demo-ivi', 'file://101_snd.cfg', '', d)}"
SRC_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'agl-demo-ivi', 'file://102_usb.cfg', '', d)}"
SRC_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'agl-demo-ivi', 'file://103_urandom.cfg', '', d)}"

do_install_append() {
    # override network interface configuration
    sed -i -e "/lxc.net.0.type/s/=\(.*\)/ = veth\n\
lxc.net.0.name = eth0\n\
lxc.net.0.link = lxcbr0\n\
lxc.net.0.flags = up\n\
lxc.net.0.veth.mode = bridge\n\
lxc.net.0.hwaddr = ${AGL_CONTAINER_MAC_ADDR}/" \
              ${D}/config
}