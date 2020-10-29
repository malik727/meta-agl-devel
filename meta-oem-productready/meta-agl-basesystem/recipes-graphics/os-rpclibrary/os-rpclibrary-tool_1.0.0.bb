SUMMARY = "librpc tools for AGL software"
DESCRIPTION = "install librpc tool"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/toyota.git;protocol=https;branch=sandbox/ToshikazuOhiwa/os-rpclibrary"
SRCREV = "${AUTOREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"


#inherit native nativesdk 
BBCLASSEXTEND = "native nativesdk"

PV = "1.0.0+gitr${SRCPV}"

INSANE_SKIP_${PN} = "compile-host-path"
INSANE_SKIP_${PN} = "ldflags"

S = "${WORKDIR}/git"

EXTRA_OEMAKE = "'CXX=${CXX}' 'CC=${CC}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'LDFLAGS=${LDFLAGS} ${LDLIBS}' 'CFLAGS=${CFLAGS}' 'SDKTARGETSYSROOT=${STAGING_DIR_NATIVE}'"
EXTRA_OEMAKE += " -j 1"
DEPENDS += " agl-basefiles-native bison-native " 
MAKE_DIR = "rpc_library"
do_compile (){
	cd ${MAKE_DIR}/tool
	oe_runmake
}

do_install (){
	install -D -m 755 rpc_library/tool/rpc_apidef ${D}${base_prefix}/usr/bin/rpc_apidef
}
FILES_${PN} += "${base_prefix}/usr/bin/rpc_apidef"


