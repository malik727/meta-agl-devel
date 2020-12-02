SUMMARY = "libpositioning_hal for AGL software"
DESCRIPTION = "install libpositioning_hal to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " \
    ns-frameworkunified \
    ns-backupmanager \
    vs-positioningbaselibrary \
"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=hal/positioning_hal;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/positioning_hal"

inherit agl-basesystem-hal

HAL_NAME = "positioning_hal"

FILES_${PN} += " \
    ${libdir}/lib${HAL_NAME}.so \
"
AGL_BRANCH="sandbox/Riku.Nomoto/WIP_20201201"
