SUMMARY = "ss-taskmanager for AGL software"
DESCRIPTION = "ss-taskmanager to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-common

FILES_${PN} += " \
    /usr/agl/lib/* \
    /usr/agl/conf/BS/ss/task_manager/rodata/* \
"
FILES_${PN}-dev += "/usr/agl/include/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/toyota.git;protocol=https;branch=sandbox/ToshikazuOhiwa/ss-taskmanager"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

# Common Dependencies
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
RDEPENDS_${PN} += " \
    ss-interfaceunified \
    ns-frameworkunified \
    ns-commonlibrary \
    ss-romaccesslibrary \
    os-rpclibrary \
    ss-resourcemanager \
    os-vehicleparameterlibrary \
"
EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE} -j 1 'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols'"
MAKE_DIR ="task_manager"

