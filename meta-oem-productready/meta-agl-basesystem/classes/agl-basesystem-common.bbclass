FILES_${PN}-staticdev = ""
 
INHIBIT_SYSROOT_STRIP = "1"
INSANE_SKIP_${PN} = "ldflags"
INSANE_SKIP_${PN}-dev = "dev-elf"
BUILD_OPTIMIZATION = "-Os -pipe"
 
SOLIBS = ".so"
SECTION = "libs"

PACKAGE_DEBUG_SPLIT_STYLE = "debug-without-src"

DEPENDS = " packagegroup-agl-basesystem-core openssl"
RDEPENDS_${PN} += " agl-basefiles "
BBCLASSEXTEND = "nativesdk"

do_compile[depends] += "agl-basefiles:do_populate_sysroot"
do_compile[depends] += "agl-basefiles-native:do_populate_sysroot"
 
EXTRA_OEMAKE = "'CXX=${CXX} ${CODINGRULES_CPP_21MM}' 'CC=${CC} ${CODINGRULES_C_21MM}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'DESTDIR=${D}' 'SDKTARGETSYSROOT=${STAGING_DIR_HOST}' 'OECORE_NATIVE_SYSROOT=${STAGING_DIR_NATIVE}' 'MACHINE=${MACHINE}'"
 
EXTRA_OEMAKE_append_salvator-x += " ARCH=arm64"
EXTRA_OEMAKE_append_m3ulcb += " ARCH=arm64"
EXTRA_OEMAKE_append_qemux86-64 += " ARCH=x86"
EXTRA_OEMAKE_append_qemuarm64 += " ARCH=arm64"

do_compile (){
    cd ${S}/${MAKE_DIR}
    oe_runmake
}
 
do_install (){
    cd ${S}/${MAKE_DIR}
    oe_runmake DESTDIR=${D} install
}


sysroot_stage_all_append(){
    sysroot_stage_dir ${D}/usr/agl ${SYSROOT_DESTDIR}/usr/agl
    sysroot_stage_dir ${D}/usr/agl/conf/systemmanager ${SYSROOT_DESTDIR}/usr/agl/conf/systemmanager
    sysroot_stage_dir ${D}/usr/agl/conf/backup_manager ${SYSROOT_DESTDIR}/usr/agl/conf/backup_manager
    sysroot_stage_dir ${D}/nv/BS/ns/npp/rwdata ${SYSROOT_DESTDIR}/nv/BS/ns/npp/rwdata
    sysroot_stage_dir ${D}/etc/udev/rules.d ${SYSROOT_DESTDIR}/etc/udev/rules.d
    sysroot_stage_dir ${D}/etc ${SYSROOT_DESTDIR}/etc
    sysroot_stage_dir ${D}/etc/ppp ${SYSROOT_DESTDIR}/etc/ppp
}


