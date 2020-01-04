SUMMARY          = "AGL DEMO: Reboot container"
DESCRIPTION      = "AGL DEMO: Reboot container"
LICENSE          = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit systemd allarch

SRC_URI = "file://lxc-watchdog-ic.service \
           file://lxc-watchdog-ivi.service \
           file://lxc-watchdog-system.service \
           file://watchdog_ic.sh \
           file://watchdog_ivi.sh \
           file://watchdog_system.sh \
          "

WATCHDOG_TARGETS = "ic ivi system"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    install -d ${D}${systemd_system_unitdir}
    install -d ${D}${bindir}

    tmp="${WATCHDOG_TARGETS}"
    for target in $tmp ; do
        install -m 0644 ${WORKDIR}/lxc-watchdog-$target.service ${D}${systemd_system_unitdir}
        install -m 0755 ${WORKDIR}/watchdog_$target.sh ${D}${bindir}
    done
}

FILES_${PN} += "${systemd_system_unitdir}"
FILES_${PN} += "${bindir}"