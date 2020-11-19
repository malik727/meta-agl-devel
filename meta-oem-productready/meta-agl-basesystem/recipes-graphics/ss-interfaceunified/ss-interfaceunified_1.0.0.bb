SUMMARY = "ss-interfaceunified for AGL software"
DESCRIPTION = "ss-interfaceunified to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += " \
    ${LIBDIR}/* \
    ${SHAREDIR} \
    ${CONFDIR} \
    ${SHAREDIR}/systemmanager \
    ${SHAREDIR}/systemmanager/scfg \
    ${SHAREDIR}/systemmanager/scfg/* \
    ${CONFDIR}/systemmanager \
    ${CONFDIR}/systemmanager/* \
    ${CONFDIR}/files/BS/ss/system_manager/rwdata/* \
    ${CONFDIR}/files/BS/ss/power_service/rodata/* \
    ${CONFDIR}/files/BS/ss/logger_service/rodata/* \
"
FILES_${PN}-dev += "${INCLUDEDIR}/*"
 
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=systemservice/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " \
    ss-romaccesslibrary \
    ns-commonlibrary \
    ns-frameworkunified \
    elfio \
"

inherit agl-basesystem-common

RDEPENDS_${PN} += " \
    elfio \
    ns-commonlibrary \
    ns-frameworkunified \
    ss-romaccesslibrary \
"

EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="interface_unified"

