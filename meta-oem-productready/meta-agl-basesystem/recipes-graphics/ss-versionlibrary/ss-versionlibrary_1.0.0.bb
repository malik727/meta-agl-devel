SUMMARY = "ss-versionlibrary for AGL software"
DESCRIPTION = "ss-versionlibrary to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common

FILES_${PN} += " \
    /usr/agl/lib/* \
"
FILES_${PN}-dev += "/usr/agl/include/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=systemservice/;branch=master"
SRCREV := "${BASESYSTEM_SRCREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " \
    ns-frameworkunified \
    ss-interfaceunified \
    ss-romaccesslibrary \
"
RDEPENDS_${PN} += " \
    ns-frameworkunified \
    ss-interfaceunified \
    ss-romaccesslibrary \
"
EXTRA_MAKEFILE = " -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="version_library"

