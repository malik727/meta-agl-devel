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
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/system;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/system/resource_manager"

inherit agl-basesystem-common

BSMAKE_FILE = "Makefile.server"
EXTRA_OEMAKE += " 'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols'"
EXTRA_OEMAKE += "'OECORE_NATIVE_SYSROOT=${STAGING_DIR_NATIVE}'"
EXTRA_OEMAKE += "'KERNEL_HEADER_DIR=${STAGING_KERNEL_BUILDDIR}/include'"

do_compile_prepend() {
    cd ${S}
    oe_runmake -f Makefile.client
}

FILES_${PN} += " \
    ${libdir}/* \
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

CAPABILITY = "cap_setuid+ep:/usr/bin/resm"
