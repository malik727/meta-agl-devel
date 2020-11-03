SUMMARY = "agl-service-agl-service-ss-resourcemanager for AGL software"
DESCRIPTION = "agl-service-agl-service-ss-resourcemanager to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common

CAPABILITY = "cap_setuid+ep:/usr/agl/bin/resm"

FILES_${PN} += " /usr/agl/bin/* "
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/toyota.git;protocol=https;branch=sandbox/ToshikazuOhiwa/ss-resourcemanager"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " \
    os-rpclibrary-tool-native \
    ss-interfaceunified \
    ss-resourcemanager \
    ns-commonlibrary \
    ns-frameworkunified \
    os-rpclibrary \
    os-eventlibrary \
    libsoctemperature-hal \
"
RDEPENDS_${PN} += " \
    ss-interfaceunified \
    ss-resourcemanager \
    ns-commonlibrary \
    ns-frameworkunified \
    os-rpclibrary \
    os-eventlibrary \
    libsoctemperature-hal \
"
EXTRA_MAKEFILE=" -f Makefile.server"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE} -j 1 'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols' "
MAKE_DIR ="resource_manager"

do_compile_prepend() {
    cd ${S}/${MAKE_DIR}
    oe_runmake -f Makefile.client
}

