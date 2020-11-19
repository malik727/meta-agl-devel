SUMMARY = "os-vehicleparameterlibrary for AGL software"
DESCRIPTION = "os-vehicleparameterlibrary to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += " \
    ${LIBDIR}/* \
"
FILES_${PN}-dev += "${INCLUDEDIR}/*"
 
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=otherservice/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

#Added here because they are native recipes, although they are AGLs
DEPENDS += " \
    ns-backupmanager \
"

inherit agl-basesystem-common

RDEPENDS_${PN} += " \
    ns-backupmanager \
"

EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="vehicle_parameter_library"

