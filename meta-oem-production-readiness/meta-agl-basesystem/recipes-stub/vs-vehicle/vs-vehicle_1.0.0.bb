SUMMARY = "vs-vehicle for AGL software"
DESCRIPTION = "vs-vehicle to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " ps-communication"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=stub;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/stub/vehicle"

inherit agl-basesystem-common

BSMAKE_FILE = "Makefile"

FILES_${PN} += "${libdir}/*"
FILES_${PN}-staticdev += "${libdir}/*/*.a"
AGL_BRANCH="sandbox/Riku.Nomoto/WIP_20201201"
