SUMMARY = "ss-interfaceunified for AGL software"
DESCRIPTION = "ss-interfaceunified to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += " \
    /usr/agl/lib/* \
    /usr/agl/share \
    /usr/agl/conf \
    /usr/agl/share/systemmanager \
    /usr/agl/share/systemmanager/scfg \
    /usr/agl/share/systemmanager/scfg/* \
    /usr/agl/conf/systemmanager \
    /usr/agl/conf/systemmanager/* \
    /usr/agl/conf/BS/ss/system_manager/rwdata/* \
    /usr/agl/conf/BS/ss/power_service/rodata/* \
    /usr/agl/conf/BS/ss/logger_service/rodata/* \
"
FILES_${PN}-dev += "/usr/agl/include/*"
 
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=systemservice/;branch=master"
SRCREV := "${BASESYSTEM_SRCREV}"

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

