SUMMARY = "libusb_hal for AGL software"
DESCRIPTION = "install libusb_hal to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=hal/usb_hal;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/usb_hal"

DEPENDS += " ns-frameworkunified"

inherit agl-basesystem-hal

HAL_NAME = "usb_hal"
FILES_${PN} += "${libdir}/lib${HAL_NAME}.so"

AGL_BRANCH = "sandbox/Riku.Nomoto/WIP_fixpath"
