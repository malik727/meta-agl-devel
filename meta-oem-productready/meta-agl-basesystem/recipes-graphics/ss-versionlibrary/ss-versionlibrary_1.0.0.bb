SUMMARY = "ss-versionlibrary for AGL software"
DESCRIPTION = "ss-versionlibrary to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common

FILES_${PN} += "${libdir}/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/system;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/system"

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
