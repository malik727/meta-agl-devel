SUMMARY = "libvideo_in_hal for AGL software"
DESCRIPTION = "install libvideo_in_hal to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=hal/video_in_hal;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/video_in_hal"

DEPENDS += " ns-frameworkunified"

inherit agl-basesystem-hal

HAL_NAME = "video_in_hal"
FILES_${PN} += "${libdir}/lib${HAL_NAME}.so"
