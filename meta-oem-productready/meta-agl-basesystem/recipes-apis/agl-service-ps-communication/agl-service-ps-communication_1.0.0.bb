SUMMARY = "agl-service-ps-communication for AGL software"
DESCRIPTION = "agl-service-ps-communication to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common

CAPABILITY = "cap_dac_override+ep:/usr/agl/bin/communication"

FILES_${PN} += " /usr/agl/bin/* "

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/toyota.git;protocol=https;branch=sandbox/ToshikazuOhiwa/ps-communication"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " \
    ns-frameworkunified \
    ps-communication \
    os-posixbasedos001legacylibrary \
    ss-interfaceunified \
    ss-romaccesslibrary \
    libcan-hal \
"
RDEPENDS_${PN} += " \
    ns-frameworkunified \
    ps-communication \
    os-posixbasedos001legacylibrary \
    ss-interfaceunified \
    ss-romaccesslibrary \
    libcan-hal \
"

EXTRA_MAKEFILE = " -f Makefile.server"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="communication"


