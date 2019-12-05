SUMMARY = "The container configration of LXC"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit allarch

SRC_URI = "file://01_core.cfg \
           file://02_mount.cfg \
           file://03_net.cfg \
          "

EXTRA_CONFIG  = "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'file://04_systemd.cfg', '', d)}"
EXTRA_CONFIG += "${@bb.utils.contains('DISTRO_FEATURES', 'smack', 'file://05_smack.cfg', '', d)}"

SRC_URI += "${EXTRA_CONFIG}"

SRC_URI += "file://06_misc.cfg"

S = "${WORKDIR}"

PACKAGE_ARCH = "${MACHINE_ARCH}"

do_compile() {
    # Put all of cfg files together.
    rm -f ${WORKDIR}/config
    for F in ${WORKDIR}/*.cfg; do
        cat $F >> ${WORKDIR}/config
        echo >> ${WORKDIR}/config
    done
    sed -i -e 's/[ \t]*$//' ${WORKDIR}/config
}

do_install() {
    install -m 0644 ${WORKDIR}/config ${D}/config
}

FILES_${PN} = "/config"
