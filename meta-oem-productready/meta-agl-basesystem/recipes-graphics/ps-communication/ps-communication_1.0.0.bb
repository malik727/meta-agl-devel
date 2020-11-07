SUMMARY = "ps-communication for AGL software"
DESCRIPTION = "ps-communication to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common
FILES_${PN} += " \
    /usr/agl/lib/* \
"
FILES_${PN}-dev += "/usr/agl/include/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=peripheralservice/;branch=master"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " \
    ns-frameworkunified \
    ps-communicationsubcpu \
"
RDEPENDS_${PN} += " \
    ns-frameworkunified \
    ps-communicationsubcpu \
"

EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="communication"

