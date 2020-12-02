SUMMARY = "vs-positioning for AGL software"
DESCRIPTION = "vs-positioning to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " \
    ns-frameworkunified \
    os-vehicleparameterlibrary \
    vs-positioningbaselibrary \
    libpositioning-hal \
"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/vehicle;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/vehicle/positioning"

inherit agl-basesystem-common

BSMAKE_FILE = "Makefile.client"
EXTRA_OEMAKE += " 'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols'"

FILES_${PN} += " \
    ${libdir}/* \
"
FILES_${PN}-staticdev = " \
    ${libdir}/*/*.a \
"

RDEPENDS_${PN} += " \
    ns-frameworkunified \
    os-vehicleparameterlibrary \
    vs-positioningbaselibrary \
    libpositioning-hal \
"

AGL_BRANCH="sandbox/Riku.Nomoto/WIP_20201201"
