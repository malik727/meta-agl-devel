SUMMARY = "ps-communicationsubcpu for AGL software"
DESCRIPTION = "ps-communicationsubcpu to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += "${libdir}/*"
 
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=stub;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/stub"

DEPENDS += " ns-frameworkunified"
 
inherit agl-basesystem-common

MAKE_DIR ="communication_subcpu"

EXTRA_MAKEFILE = " -f Makefile"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"

