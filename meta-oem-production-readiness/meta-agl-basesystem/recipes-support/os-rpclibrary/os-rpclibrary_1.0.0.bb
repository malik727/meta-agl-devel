SUMMARY = "os-rpclibrary for AGL software"
DESCRIPTION = "os-rpclibrary to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " \
    ns-commonlibrary \
    ns-loglibrary \
    bison-native \
"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/other;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

S = "${WORKDIR}/other/rpc_library"

inherit agl-basesystem-common

BSMAKE_FILE = "Makefile.client"

FILES_${PN} += "/usr/lib/basesystem/librpc.so"

RDEPENDS_${PN} += " \
    ns-commonlibrary \
    ns-loglibrary \
"
