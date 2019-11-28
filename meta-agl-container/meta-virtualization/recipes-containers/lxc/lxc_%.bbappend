SRC_URI_append = " \
    file://lxc.conf \
"

do_install_append() {
     install -m 644 ${WORKDIR}/lxc.conf ${D}${sysconfdir}/lxc/
}

FILES_${PN} += " \
    ${sysconfdir}/lxc/lxc.conf \
    "
