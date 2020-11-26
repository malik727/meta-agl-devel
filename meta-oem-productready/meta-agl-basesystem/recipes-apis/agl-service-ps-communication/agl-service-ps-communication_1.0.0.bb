SUMMARY = "agl-service-ps-communication for AGL software"
DESCRIPTION = "agl-service-ps-communication to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

CAPABILITY = "cap_dac_override+ep:/usr/bin/communication"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/peripheral;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/peripheral"

DEPENDS += " \
    ns-frameworkunified \
    ps-communication \
    os-posixbasedos001legacylibrary \
    ss-interfaceunified \
    ss-romaccesslibrary \
    libcan-hal \
"

inherit agl-basesystem-common

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
