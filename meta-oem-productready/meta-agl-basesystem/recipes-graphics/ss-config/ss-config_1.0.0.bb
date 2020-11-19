SUMMARY = "ss-config for AGL software"
DESCRIPTION = "ss-config to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += " \
    ${LIBDIR}/* \
"
FILES_${PN}-dev += "${INCLUDEDIR}/*"
 
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=systemservice/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " \
    ss-interfaceunified \
    ss-romaccesslibrary \
    ss-versionlibrary \
    ns-frameworkunified \
    ps-communication \
    os-vehicleparameterlibrary \
"

inherit agl-basesystem-common

RDEPENDS_${PN} += " \
    ss-interfaceunified \
    ss-romaccesslibrary \
    ns-frameworkunified \
    ps-communication \
    ss-versionlibrary \
    os-vehicleparameterlibrary \
"
EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="config"

