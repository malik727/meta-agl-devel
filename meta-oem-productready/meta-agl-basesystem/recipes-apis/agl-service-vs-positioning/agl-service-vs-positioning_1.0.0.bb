SUMMARY = "agl-service-vs-positioning for AGL software"
DESCRIPTION = "agl-service-vs-positioning to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common agl-basesystem-capability

CAPABILITY = "cap_dac_override+ep:/usr/agl/bin/Positioning"

FILES_${PN} += " \
    /usr/agl/bin/* \
"
FILES_${PN}-staticdev += " \
    /usr/agl/lib/*.a \
"

FILES_${PN} += "/nv/BS/vs/positioning/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/toyota.git;protocol=https;branch=sandbox/ToshikazuOhiwa/vs-positioning"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

# Common Dependencies
DEPENDS += " \
    ss-config \
    ss-interfaceunified \
    ss-versionlibrary \
    ns-frameworkunified \
    ns-commonlibrary \
    ns-backupmanager \
    os-vehicleparameterlibrary \
    os-eventlibrary \
    ps-communication \
    libpositioning-hal \
    vs-positioningbaselibrary \
    vs-positioning \
    ps-communicationusb \
    vs-clock \
    vs-vehicle \
"
RDEPENDS_${PN} += " \
    ss-config \
    ss-interfaceunified \
    ss-versionlibrary \
    ns-frameworkunified \
    ns-commonlibrary \
    ns-backupmanager \
    os-vehicleparameterlibrary \
    os-eventlibrary \
    ps-communication \
    libpositioning-hal \
    vs-positioningbaselibrary \
    vs-positioning \
    vs-clock \
    vs-vehicle \
"
EXTRA_MAKEFILE=" -f Makefile.server"
EXTRA_OEMAKE += " ${EXTRA_MAKEFILE} -j 1 'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols' "
MAKE_DIR ="positioning"


