SUMMARY = "vs-positioning for AGL software"
DESCRIPTION = "vs-positioning to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += "${libdir}/*"
FILES_${PN}-staticdev = "${libdir}/*/*.a"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/vehicle/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/vehicle"

DEPENDS += " \
    ns-frameworkunified \
    os-vehicleparameterlibrary \
    vs-positioningbaselibrary \
    libpositioning-hal \
"

inherit agl-basesystem-common

RDEPENDS_${PN} += " \
    ns-frameworkunified \
    os-vehicleparameterlibrary \
    vs-positioningbaselibrary \
    libpositioning-hal \
"
EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE} 'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols'"
MAKE_DIR ="positioning"
