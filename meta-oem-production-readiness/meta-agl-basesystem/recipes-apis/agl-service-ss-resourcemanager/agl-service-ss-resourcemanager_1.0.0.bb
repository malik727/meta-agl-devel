SUMMARY = "agl-service-agl-service-ss-resourcemanager for AGL software"
DESCRIPTION = "agl-service-agl-service-ss-resourcemanager to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

CAPABILITY = "cap_setuid+ep:/usr/bin/resm"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/system;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/system/resource_manager"

DEPENDS += " \
    os-rpclibrary-tool-native \
    ss-interfaceunified \
    ss-resourcemanager \
    ns-commonlibrary \
    ns-frameworkunified \
    os-rpclibrary \
    os-eventlibrary \
    libsoctemperature-hal \
"
RDEPENDS_${PN} += " \
    ss-interfaceunified \
    ss-resourcemanager \
    ns-commonlibrary \
    ns-frameworkunified \
    os-rpclibrary \
    os-eventlibrary \
    libsoctemperature-hal \
"

inherit agl-basesystem-common

EXTRA_MAKEFILE=" -f Makefile.server"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE} 'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols' "
EXTRA_OEMAKE += "'OECORE_NATIVE_SYSROOT=${STAGING_DIR_NATIVE}'"

do_compile_prepend() {
    oe_runmake -f Makefile.client
}
