FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# configuration of LXC host
SRC_URI_append = " \
    file://lxc.conf \
"

RDEPENDS_${PN}-networking += "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'agl-container-host', 'iproute2', '', d)} \
    "

do_install_append() {
     install -m 644 ${WORKDIR}/lxc.conf ${D}${sysconfdir}/lxc/

     # create dir of lxc.lxcpath
     install -d -m 755 ${D}/var/local/lib/containers
}

FILES_${PN} += " \
    ${sysconfdir}/lxc/lxc.conf \
    /var/local/lib/containers \
    "
