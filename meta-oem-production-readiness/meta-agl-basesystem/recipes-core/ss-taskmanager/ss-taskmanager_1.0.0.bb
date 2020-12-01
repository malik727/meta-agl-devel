SUMMARY = "ss-taskmanager for AGL software"
DESCRIPTION = "ss-taskmanager to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " \
    os-rpclibrary-tool-native \
    ss-interfaceunified \
    ss-romaccesslibrary \
    ss-resourcemanager \
    ns-frameworkunified \
    ns-commonlibrary \
    os-rpclibrary \
    os-vehicleparameterlibrary \
    libxml2-native \
"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/system;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/system/task_manager"

inherit agl-basesystem-common

BSMAKE_FILE = "Makefile.client"
EXTRA_OEMAKE += " 'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols'"
EXTRA_OEMAKE += "'OECORE_NATIVE_SYSROOT=${STAGING_DIR_NATIVE}'"

FILES_${PN} += "  /usr/lib/basesystem/*.so"

RDEPENDS_${PN} += " \
    ss-interfaceunified \
    ns-frameworkunified \
    ns-commonlibrary \
    ss-romaccesslibrary \
    os-rpclibrary \
    ss-resourcemanager \
    os-vehicleparameterlibrary \
"
AGL_BRANCH="sandbox/Riku.Nomoto/WIP_20201201"
