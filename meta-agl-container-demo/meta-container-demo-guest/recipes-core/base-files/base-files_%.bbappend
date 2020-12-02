AGL_CONTAINER_HOSTNAME_APPEND ??= "guest"
hostname_append = "${AGL_CONTAINER_HOSTNAME_APPEND}"

do_install_append() {
    # disable mount entry /run
    sed -i -e '0,/\/run/{/\/run/s/^/#/}' ${D}${sysconfdir}/fstab
}
