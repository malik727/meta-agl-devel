SUMMARY     = "Configuration for guest containers of AGL Demonstrator"
DESCRIPTION = "Configuration for guest containers of AGL Demonstrator"
LICENSE     = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit systemd allarch

SRC_URI = "file://var-local-lib-containers-GUEST_IC.mount \
           file://var-local-lib-containers-GUEST_IVI.mount \
           file://var-local-lib-containers-GUEST_OTHERS.mount \
          "

CONTAINER_GUESTS = "GUEST_IC GUEST_IVI GUEST_OTHERS"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    # Install and enable mount unit for container's root filesystem
    install -d ${D}${systemd_system_unitdir}
    install -d ${D}${sysconfdir}/systemd/system/multi-user.target.wants/

    tmp="${CONTAINER_GUESTS}"
    for guest in $tmp ; do
        # install mount file for container guest
        install -m 0644 ${WORKDIR}/var-local-lib-containers-$guest.mount ${D}${systemd_system_unitdir}
        # enable
        ln -sf ${systemd_system_unitdir}/var-local-lib-containers-$guest.mount ${D}${sysconfdir}/systemd/system/multi-user.target.wants/var-local-lib-containers-$guest.mount
    done
}

FILES_${PN} += "${systemd_system_unitdir}"
