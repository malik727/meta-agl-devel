SUMMARY = "agl-service-ss-systemmanager for AGL software"
DESCRIPTION = "agl-service-ss-systemmanager to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

CAPABILITY = "cap_sys_nice,cap_setuid,cap_setgid,cap_sys_resource+ep:/usr/bin/agl-bs/SS_SystemManager"

FILES_${PN} += "${SHAREDIR}/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/system;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/system"

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
    libxml2-native \
 "

inherit agl-basesystem-common

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
