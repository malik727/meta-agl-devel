SUMMARY = "libvehicle_hal for AGL software"
DESCRIPTION = "install libvehicle_hal to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=hal/vehicle_hal;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/vehicle_hal"

DEPENDS += " ns-frameworkunified"

inherit agl-basesystem-hal

HAL_NAME = "vehicle_hal"
FILES_${PN} += "${libdir}/lib${HAL_NAME}.so"
