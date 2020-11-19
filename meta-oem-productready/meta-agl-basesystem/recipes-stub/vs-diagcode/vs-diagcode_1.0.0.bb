SUMMARY = "vs-diagcode for AGL software"
DESCRIPTION = "vs-diagcode to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += " ${LIBDIR}/* "
FILES_${PN}-dev += "${INCLUDEDIR}/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=stub/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

# Common Dependencies
DEPENDS += " ns-frameworkunified"
 
inherit agl-basesystem-common

# Build directory
MAKE_DIR ="diag_code"

EXTRA_MAKEFILE = " -f Makefile"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"

