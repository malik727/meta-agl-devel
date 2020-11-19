SUMMARY = "ns-frameworkunified for AGL software"
DESCRIPTION = "ns-frameworkunified to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

# Common Dependencies
DEPENDS += " \
    os-posixbasedos001legacylibrary \
    ns-loglibrary \
    ns-commonlibrary \
    libxml2 \
    boost \
"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=nsframework/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

inherit agl-basesystem-common

EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="framework_unified"

FILES_${PN} += " \
    ${LIBDIR}/* \
    ${CONFDIR}/ns_logger/* \
    ${NVPATH}/files/BS/ns/framework_unified/* \
    ${CONFDIR}/files/BS/ns/framework_unified/rodata/* \
"
FILES_${PN}-staticdev += " \
    ${LIBDIR}/*.a \
"
FILES_${PN}-dev += "${INCLUDEDIR}/*"


RDEPENDS_${PN} += " \
    os-posixbasedos001legacylibrary \
    ns-loglibrary \
    ns-commonlibrary \
"
