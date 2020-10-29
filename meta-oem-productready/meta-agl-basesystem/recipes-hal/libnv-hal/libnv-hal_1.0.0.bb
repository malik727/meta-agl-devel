SUMMARY = "libnv_hal for AGL software"
DESCRIPTION = "install libnv_hal to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-hal

FILES_${PN}-dev += "/usr/agl/include/native_service/* "

do_package_qa[noexec] = "1"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/toyota.git;protocol=https;branch=sandbox/ToshikazuOhiwa/nv_hal"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " ns-frameworkunified"

HAL_NAME = "nv_hal"
