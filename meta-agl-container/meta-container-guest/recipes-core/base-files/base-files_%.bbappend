hostname_append = "-guest"

do_install_append() {
    # disable mount from /dev/root
    sed -i -e 's/\/dev\/root/#\/dev\/root/' ${D}${sysconfdir}/fstab
}
