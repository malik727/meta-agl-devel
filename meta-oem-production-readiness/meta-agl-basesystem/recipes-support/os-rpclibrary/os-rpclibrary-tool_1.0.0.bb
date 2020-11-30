SUMMARY = "librpc tools for AGL software"
DESCRIPTION = "install librpc tool"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " agl-basefiles-native bison-native "

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/other;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/other/rpc_library"

EXTRA_OEMAKE = "'CXX=${CXX}' 'CC=${CC}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'LDFLAGS=${LDFLAGS} ${LDLIBS}' 'CFLAGS=${CFLAGS}' 'SDKTARGETSYSROOT=${STAGING_DIR_NATIVE}' -j 1"

BSMAKE_FILE = "./tool/Makefile"

do_install () {
	install -D -m 755 tool/rpc_apidef ${D}${base_prefix}/usr/bin/rpc_apidef
}

FILES_${PN} += "${base_prefix}/usr/bin/rpc_apidef"

BBCLASSEXTEND = "native nativesdk"
