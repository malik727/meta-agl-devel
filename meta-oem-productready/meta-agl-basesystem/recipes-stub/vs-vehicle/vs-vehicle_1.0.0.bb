SUMMARY = "vs-vehicle for AGL software"
DESCRIPTION = "vs-vehicle to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += "${libdir}/*"
FILES_${PN}-staticdev += "${libdir}/*/*.a"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=stub;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/stub"

DEPENDS += " ps-communication"

inherit agl-basesystem-common

MAKE_DIR ="vehicle"

EXTRA_MAKEFILE = " -f Makefile"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"

AGL_BRANCH = "sandbox/ruke47/complete_build"