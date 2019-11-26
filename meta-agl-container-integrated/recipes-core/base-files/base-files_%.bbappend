hostname_append_aglcontainerguest = "-guest"

do_install_append_aglcontainerguest() {
    # disable mount /dev/root
    sed -i -e 's/\/dev\/root/#\/dev\/root/' ${D}${sysconfdir}/fstab
}
