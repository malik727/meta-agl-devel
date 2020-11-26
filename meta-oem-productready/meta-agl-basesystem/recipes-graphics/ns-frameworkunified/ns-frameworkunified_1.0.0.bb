SUMMARY = "ns-frameworkunified for AGL software"
DESCRIPTION = "ns-frameworkunified to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

# Common Dependencies
DEPENDS += " \
    os-posixbasedos001legacylibrary \
    ns-loglibrary \
    ns-commonlibrary \
    libxml2 \
    boost \
"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/native/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/native"

inherit agl-basesystem-common

EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="framework_unified"

FILES_${PN} += " \
    ${libdir}/* \
    ${CONFDIR}/ns_logger/* \
    ${LOCALDIR}/nv/BS/ns/framework_unified/* \
    ${CONFDIR}/BS/ns/framework_unified/rodata/* \
"
FILES_${PN}-staticdev += " \
    ${libdir}/*.a \
"
FILES_${PN}-dev += "${includedir}/*"


RDEPENDS_${PN} += " \
    os-posixbasedos001legacylibrary \
    ns-loglibrary \
    ns-commonlibrary \
"

AGL_BRANCH = "sandbox/ruke47/complete_build"
