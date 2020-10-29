SUMMARY = "agl-service-ss-systemmanager for AGL software"
DESCRIPTION = "agl-service-ss-systemmanager to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common agl-basesystem-capability

CAPABILITY = "cap_sys_nice,cap_setuid,cap_setgid,cap_sys_resource+ep:/usr/agl/bin/SS_SystemManager"

FILES_${PN} += " /usr/agl/bin/* "

FILES_${PN} += "/usr/agl/conf/BS/ss/system_manager/rwdata/sm_launch.cfg"
FILES_${PN} += "/usr/agl/share/BS/ss/system_manager/rodata/version.txt"
FILES_${PN} += "/usr/agl/share/BS/ss/system_manager/rodata/PhaseInfo.txt"

FILES_${PN} += "/nv/BS/ss/system_manager/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/toyota.git;protocol=https;branch=sandbox/ToshikazuOhiwa/ss-systemmanager"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " \
    agl-service-ss-resourcemanager \
    agl-service-ss-loggerservice \
    agl-service-ps-communication \ 
    ss-config  \
    ss-interfaceunified  \
    ns-commonlibrary  \
    ns-frameworkunified  \
    os-vehicleparameterlibrary  \
    os-posixbasedos001legacylibrary  \
    os-rpclibrary  \
    os-eventlibrary \
    libpower-hal \
    vs-clock \
    vs-diagcode \
"
RDEPENDS_${PN} += " \
    agl-service-ss-resourcemanager \
    agl-service-ss-loggerservice \
    agl-service-ps-communication \ 
    ss-config  \
    ss-interfaceunified  \
    ns-commonlibrary  \
    ns-frameworkunified  \
    os-vehicleparameterlibrary  \
    os-posixbasedos001legacylibrary  \
    os-rpclibrary  \
    os-eventlibrary \
    libpower-hal \
    vs-clock \
    vs-diagcode \
"

EXTRA_MAKEFILE = " -f Makefile.server"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="system_manager"


