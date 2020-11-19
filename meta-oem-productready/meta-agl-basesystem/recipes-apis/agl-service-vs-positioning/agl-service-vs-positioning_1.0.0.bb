SUMMARY = "agl-service-vs-positioning for AGL software"
DESCRIPTION = "agl-service-vs-positioning to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

CAPABILITY = "cap_dac_override+ep:/usr/files/bin/Positioning"

FILES_${PN} += " \
    /usr/files/bin/* \
"
FILES_${PN}-staticdev += " \
    ${LIBDIR}/*.a \
"

FILES_${PN} += "${NVPATH}/files/BS/vs/positioning/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=vehicleservice/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

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

inherit agl-basesystem-common

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


