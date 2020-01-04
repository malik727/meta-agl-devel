SUMMARY          = "AGL DEMO: Reboot container"
DESCRIPTION      = "AGL DEMO: Reboot container"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

SRC_URI = "git://github.com/cf47mn/agl-cm-demo.git;protocol=https;branch=${AGL_BRANCH} \
           file://restore-tbt.sh \
          "
SRCREV = "${AGL_APP_REVISION}"

PV = "1.0+git${SRCPV}"
S = "${WORKDIR}/git"

# build-time dependencies
DEPENDS += "qtquickcontrols2 libhomescreen qlibwindowmanager qttools-native qtaglextras"

inherit qmake5 aglwgt

do_install_append() {
    install -d ${D}${sysconfdir}/lxc
    install -d ${D}${bindir}

    touch ${D}${sysconfdir}/lxc/trigger-reboot-container-ic
    touch ${D}${sysconfdir}/lxc/trigger-reboot-container-ivi
    touch ${D}${sysconfdir}/lxc/trigger-reboot-system

    install -m 0755 ${WORKDIR}/restore-tbt.sh ${D}${bindir}
}

FILES_${PN} += "${sysconfdir}/lxc"
FILES_${PN} += "${bindir}"
