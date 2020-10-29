SUMMARY = "agl-service-ss-loggerservice for AGL software"
DESCRIPTION = "agl-service-ss-loggerservice to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common agl-basesystem-capability

CAPABILITY = "cap_dac_override+ep:/usr/agl/bin/SS_LoggerService"

FILES_${PN} += " \
    /usr/agl/bin/* \
"
FILES_${PN}-staticdev += " /usr/agl/lib/*.a "
FILES_${PN} += "/nv/BS/ss/logger_service/rwdata/frameworkunifiedlog"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/toyota.git;protocol=https;branch=sandbox/ToshikazuOhiwa/ss-loggerservice"
SRCREV = "${AUTOREV}"

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


