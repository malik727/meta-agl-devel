SUMMARY = "agl-service-agl-service-ss-resourcemanager for AGL software"
DESCRIPTION = "agl-service-agl-service-ss-resourcemanager to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

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

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;branch=${BASESYSTEM_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/git/service/system/resource_manager"

inherit agl-basesystem-common

BSMAKE_FILE = "Makefile.server"
EXTRA_OEMAKE += "'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols' "
EXTRA_OEMAKE += "'OECORE_NATIVE_SYSROOT=${STAGING_DIR_NATIVE}'"
EXTRA_OEMAKE += "'RPATHLINK=${STAGING_DIR_HOST}/usr/lib:${STAGING_DIR_HOST}/lib:${STAGING_DIR_HOST}/usr/lib/basesystem'"

TARGET_CFLAGS_append = " -I${STAGING_KERNEL_BUILDDIR}/include "
do_compile[depends] += "virtual/kernel:do_shared_workdir"

do_compile_prepend() {
    oe_runmake -f Makefile.client
}

RDEPENDS_${PN} += " \
    ss-interfaceunified \
    ss-resourcemanager \
    ns-commonlibrary \
    ns-frameworkunified \
    os-rpclibrary \
    os-eventlibrary \
    libsoctemperature-hal \
"

CAPABILITY = "cap_setuid+ep:/usr/bin/resm"
