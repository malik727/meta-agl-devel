SUMMARY = "ss-resourcemanager for AGL software"
DESCRIPTION = "ss-resourcemanager to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " \
    os-rpclibrary-tool-native \
    ss-interfaceunified \
    ns-frameworkunified \
    ns-commonlibrary \
    os-rpclibrary \
    os-eventlibrary \
    libsoctemperature-hal \
"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/system;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/system/resource_manager"

inherit agl-basesystem-common

BSMAKE_FILE = "Makefile.client"
EXTRA_OEMAKE += "'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols'"
EXTRA_OEMAKE += "'OECORE_NATIVE_SYSROOT=${STAGING_DIR_NATIVE}'"

TARGET_CFLAGS_append = " -I${STAGING_KERNEL_BUILDDIR}/include "
do_compile[depends] += "virtual/kernel:do_shared_workdir"

FILES_${PN} += "/usr/lib/basesystem/libresm.so"

RDEPENDS_${PN} += " \
    ns-frameworkunified \
    ss-interfaceunified \
    ns-commonlibrary \
    ns-frameworkunified \
    os-rpclibrary \
    os-eventlibrary \
    libsoctemperature-hal \
"
