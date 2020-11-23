SUMMARY = "agl-service-ss-loggerservice for AGL software"
DESCRIPTION = "agl-service-ss-loggerservice to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common

CAPABILITY = "cap_dac_override+ep:/usr/bin//SS_LoggerService"

FILES_${PN}-staticdev += "${libdir}/*/*.a"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/system;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/system"

DEPENDS += " libtar \
    ss-config \
    ss-interfaceunified \
    ss-romaccesslibrary \
    ss-resourcemanager \
    ns-commonlibrary \
    ns-frameworkunified \
    ns-backupmanager \
    os-vehicleparameterlibrary \
    os-posixbasedos001legacylibrary \
    logrotate \
    ns-memorygpioaccesslibrary \
    vs-clock \
    vs-diagrecord \
"
RDEPENDS_${PN} += " \
    ss-config \
    ss-interfaceunified \
    ss-romaccesslibrary \
    ss-resourcemanager \
    ns-commonlibrary \
    ns-frameworkunified \
    ns-backupmanager \
    os-vehicleparameterlibrary \
    os-posixbasedos001legacylibrary \
    ns-memorygpioaccesslibrary \
    vs-clock \
    vs-diagrecord \
"
EXTRA_MAKEFILE = " -f Makefile.server"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="logger_service"
