hostname_append = "-ic"

do_install_append() {
    # disable mount entry /run
    sed -i -e '0,/\/run/{/\/run/s/^/#/}' ${D}${sysconfdir}/fstab
}
