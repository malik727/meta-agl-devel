#
# "kernel module for libev" recipe
#
SUMMARY = "libev kernel module for AGL software"
DESCRIPTION = "libev kernel module build AGL software"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://LICENSE.GPL-2.0-only;md5=4ee23c52855c222cba72583d301d2338"

DEPENDS += " \
    agl-basefiles \
"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=module/kernel-module-evklib;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/kernel-module-evklib"

inherit module

EXTRA_OEMAKE += "COMMON_HEADER_DIR=${STAGING_INCDIR}/basesystem"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.
RPROVIDES_${PN} += " \
    kernel-module-evk_lib \
"

KERNEL_MODULE_AUTOLOAD += "evk_lib"
