FILES_${PN} = " \
    /usr/lib/*.so \
    /usr/bin/* \
"
FILES_SOLIBSDEV = ""

FILES_${PN}-dev += " \
    /usr/include/* \
    /usr/agl/include/* \
"
FILES_${PN}-staticdev = ""

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"
INSANE_SKIP_${PN} = "ldflags"
INSANE_SKIP_${PN}-dev = "dev-elf"
TARGET_CC_ARCH += "${LDFLAGS}"
SOLIBS = ".so"
SECTION = "libs"

DEPENDS += " "

EXTRA_OEMAKE = "'CXX=${CXX}' 'CC=${CC}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'DESTDIR=${D}' 'SDKTARGETSYSROOT=${STAGING_DIR_HOST}'"

EXTRA_ARCH ?= " ARCH=arm64"
EXTRA_OEMAKE_append += " ${EXTRA_ARCH}"

do_compile[depends] += "agl-basefiles:do_populate_sysroot"
do_compile (){
    cd ${S}
    oe_runmake
}

do_install (){
    cd ${S}/hal_api
    install -d ${D}/usr/include
    install -D -m 644 *.h ${D}/usr/include
    install -d ${D}/usr/lib/

    cd ${S}
    oe_runmake install
}

sysroot_stage_all_append(){
    sysroot_stage_dir ${D}/usr/agl ${SYSROOT_DESTDIR}/usr/agl
}
