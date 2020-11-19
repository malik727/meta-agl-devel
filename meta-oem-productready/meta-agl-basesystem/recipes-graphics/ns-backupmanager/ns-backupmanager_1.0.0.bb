SUMMARY = "ns-backupmanager for AGL software"
DESCRIPTION = "ns-backupmanager to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += " \
    ${LIBDIR}/* \
    ${CONFDIR}/files/BS/ns/backup_manager/rodata/* \
"
FILES_${PN}-dev += "${INCLUDEDIR}/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=nsframework/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " \
    libxml2-native \
    ns-frameworkunified \
    libnv-hal \
"

inherit agl-basesystem-common

RDEPENDS_${PN} += " \
    ns-frameworkunified \
    libnv-hal \
"
EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="backup_manager"

