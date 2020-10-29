#
# "kernel module for libev" recipe
#

SUMMARY = "libev kernel module for AGL software"
DESCRIPTION = "libev kernel module build AGL software"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

inherit module

FILES_${PN} = "/lib/modules/${KERNEL_VERSION}/evk_lib.ko"

KERNEL_MODULE_AUTOLOAD += "evk_lib"

SRC_URI += " \
    file://evk_lib.c \
    file://Makefile \
    file://agldd \
"
S = "${WORKDIR}"

do_install (){
	install -d ${D}/lib/modules/${KERNEL_VERSION}/
	install -m 644 evk_lib.ko ${D}/lib/modules/${KERNEL_VERSION}/
}
