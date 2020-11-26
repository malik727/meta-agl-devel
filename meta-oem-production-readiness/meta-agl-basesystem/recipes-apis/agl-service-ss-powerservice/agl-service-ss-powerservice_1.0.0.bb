SUMMARY = "agl-service-ss-powerservice for AGL software"
DESCRIPTION = "agl-service-ss-powerserice to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/system;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/system"

DEPENDS += " \
    ss-interfaceunified \
    ss-romaccesslibrary \
    ns-frameworkunified \
    os-posixbasedos001legacylibrary \
"

inherit agl-basesystem-common

RDEPENDS_${PN} += " \
    ss-interfaceunified \
    ss-romaccesslibrary \
    ns-frameworkunified \
    os-posixbasedos001legacylibrary \
"

EXTRA_MAKEFILE=" -f Makefile.server"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="power_service"
