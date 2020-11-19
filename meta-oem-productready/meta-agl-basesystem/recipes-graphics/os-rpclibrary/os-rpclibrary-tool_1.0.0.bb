SUMMARY = "librpc tools for AGL software"
DESCRIPTION = "install librpc tool"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=otherservice/;branch=master"
SRCREV := "${BASESYSTEM_SRCREV}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/git"

PV = "1.0.0+gitr${SRCPV}"

INSANE_SKIP_${PN} = "compile-host-path"

S = "${WORKDIR}/git"

EXTRA_OEMAKE = "'CXX=${CXX}' 'CC=${CC}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'LDFLAGS=${LDFLAGS} ${LDLIBS}' 'CFLAGS=${CFLAGS}' 'SDKTARGETSYSROOT=${STAGING_DIR_NATIVE}'"
DEPENDS += " agl-basefiles-native bison-native " 
MAKE_DIR = "rpc_library"
do_compile (){
	cd ${MAKE_DIR}/tool
	oe_runmake
}

do_install (){
	install -D -m 755 rpc_library/tool/rpc_apidef ${D}${base_prefix}/usr/files/bin/rpc_apidef
}
FILES_${PN} += "${base_prefix}/usr/files/bin/rpc_apidef"

#inherit native nativesdk 
BBCLASSEXTEND = "native nativesdk"


