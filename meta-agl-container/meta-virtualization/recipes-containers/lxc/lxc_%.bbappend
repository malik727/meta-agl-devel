SRC_URI_append = " \
    file://0001-lxc-net-add-network.target.patch \
    file://lxc.conf \
"

do_install_append() {
     install -m 644 ${WORKDIR}/lxc.conf ${D}${sysconfdir}/lxc/
}

FILES_${PN} += " \
    ${sysconfdir}/lxc/lxc.conf \
    "
