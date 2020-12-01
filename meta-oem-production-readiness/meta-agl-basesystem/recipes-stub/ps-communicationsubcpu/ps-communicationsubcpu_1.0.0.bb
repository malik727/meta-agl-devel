SUMMARY = "ps-communicationsubcpu for AGL software"
DESCRIPTION = "ps-communicationsubcpu to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " ns-frameworkunified"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=stub;branch=${AGL_BRANCH}"
#SRCREV := "${BASESYSTEM_REVISION}"
SRCREV := "192f2ab881c2ecc586cd0f7551887a7759272a65"

S = "${WORKDIR}/stub/communication_subcpu"

inherit agl-basesystem-common

BSMAKE_FILE = "Makefile"

EXTRA_OEMAKE += "'KERNEL_HEADER_DIR=${STAGING_KERNEL_BUILDDIR}/include'"

FILES_${PN} += "${libdir}/*"
AGL_BRANCH="sandbox/Riku.Nomoto/WIP_20201201"
