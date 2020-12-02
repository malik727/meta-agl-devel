SUMMARY = "agl-service-ss-systemmanager for AGL software"
DESCRIPTION = "agl-service-ss-systemmanager to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " \
    agl-service-ss-resourcemanager \
    agl-service-ss-loggerservice \
    agl-service-ps-communication \
    ss-config \
    ss-interfaceunified \
    ns-commonlibrary \
    ns-frameworkunified \
    os-vehicleparameterlibrary \
    os-posixbasedos001legacylibrary \
    os-rpclibrary \
    os-eventlibrary \
    libpower-hal \
    vs-clock \
    vs-diagcode \
    libxml2-native \
    libxml-libxml-perl-native \
"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/system;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/system/system_manager"

inherit agl-basesystem-common

BSMAKE_FILE = "Makefile.server"

FILES_${PN} += " \
    /usr/share/* \
"

RDEPENDS_${PN} += " \
    agl-service-ss-resourcemanager \
    agl-service-ss-loggerservice \
    agl-service-ps-communication \
    ss-config \
    ss-interfaceunified \
    ns-commonlibrary \
    ns-frameworkunified \
    os-vehicleparameterlibrary \
    os-posixbasedos001legacylibrary \
    os-rpclibrary \
    os-eventlibrary \
    libpower-hal \
    vs-clock \
    vs-diagcode \
"

CAPABILITY = "cap_sys_nice,cap_setuid,cap_setgid,cap_sys_resource+ep:/usr/bin/basesystem/SS_SystemManager"
AGL_BRANCH="sandbox/Riku.Nomoto/WIP_20201201"
