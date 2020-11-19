SUMMARY = "agl-service-ss-loggerservice for AGL software"
DESCRIPTION = "agl-service-ss-loggerservice to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common

CAPABILITY = "cap_dac_override+ep:/usr/files/bin/SS_LoggerService"

FILES_${PN} += " \
    /usr/files/bin/* \
"
FILES_${PN}-staticdev += " ${LIBDIR}/*.a "
FILES_${PN} += "${NVPATH}/files/BS/ss/logger_service/rwdata/frameworkunifiedlog"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=systemservice/;branch=master"
SRCREV := "${BASESYSTEM_SRCREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

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


