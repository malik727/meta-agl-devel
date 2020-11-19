SUMMARY = "ss-taskmanager for AGL software"
DESCRIPTION = "ss-taskmanager to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += " \
    ${LIBDIR}/* \
    ${CONFDIR}/files/BS/ss/task_manager/rodata/* \
"
FILES_${PN}-dev += "${INCLUDEDIR}/*"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=systemservice/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

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

inherit agl-basesystem-common

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
EXTRA_OEMAKE += "${EXTRA_MAKEFILE} 'CXX=${CXX} -Wl,--warn-unresolved-symbols' 'CC=${CC} -Wl,--warn-unresolved-symbols'"
MAKE_DIR ="task_manager"

