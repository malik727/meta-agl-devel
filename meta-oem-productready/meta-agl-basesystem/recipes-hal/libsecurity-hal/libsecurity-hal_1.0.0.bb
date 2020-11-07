SUMMARY = "libsecurity_hal for AGL software"
DESCRIPTION = "install libsecurity_hal to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

inherit agl-basesystem-hal

FILES_${PN}-dev += "/usr/agl/include/system_service/*"

do_package_qa[noexec] = "1"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=security_hal/;branch=master"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS += " ns-frameworkunified"

HAL_NAME = "security_hal"
