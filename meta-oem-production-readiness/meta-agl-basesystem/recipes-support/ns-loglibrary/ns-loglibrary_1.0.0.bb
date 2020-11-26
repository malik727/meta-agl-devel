SUMMARY = "ns-loglibrary for AGL software"
DESCRIPTION = "ns-loglibrary to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/native/;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/native/log_library"

inherit agl-basesystem-common

EXTRA_MAKEFILE = " -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"

FILES_${PN} += " \
    ${libdir}/* \
"
FILES_${PN}-dev += "${includedir}/*"
