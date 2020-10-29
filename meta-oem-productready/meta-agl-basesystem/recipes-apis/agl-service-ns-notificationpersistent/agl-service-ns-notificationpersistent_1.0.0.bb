SUMMARY = "agl-service-ns-notificationpersistent for AGL software"
DESCRIPTION = "agl-service-ns-notificationpersistent to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common

FILES_${PN} += " /usr/agl/bin/* "
FILES_${PN}-dev += "/usr/agl/include/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/toyota.git;protocol=https;branch=sandbox/ToshikazuOhiwa/ns-notificationpersistent"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " \
    libtar \
    ns-frameworkunified \
    os-posixbasedos001legacylibrary \
"
RDEPENDS_${PN} += " \
    ns-frameworkunified \
    os-posixbasedos001legacylibrary \
"

EXTRA_MAKEFILE = " -f Makefile.server"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="notification_persistent_service"


