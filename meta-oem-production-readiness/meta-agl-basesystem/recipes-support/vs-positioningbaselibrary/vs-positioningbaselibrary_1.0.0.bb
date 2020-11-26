SUMMARY = "vs-positioningbaselibrary for AGL software"
DESCRIPTION = "vs-positioningbaselibrary to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += "${libdir}/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/vehicle;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/vehicle"

DEPENDS += " \
    ns-frameworkunified \
    os-eventlibrary \
    os-vehicleparameterlibrary \
"

inherit agl-basesystem-common

RDEPENDS_${PN} += " \
    ns-frameworkunified \
    os-eventlibrary \
    os-vehicleparameterlibrary \
"

EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="positioning_base_library"
