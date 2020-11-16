FILES_SOLIBSDEV = ""

FILES_${PN}-dev += " \
    /usr/include/* \
    /usr/agl/include/* \
"
FILES_${PN}-staticdev = ""

SOLIBS = ".so"
SECTION = "libs"

DEPENDS += " "

EXTRA_OEMAKE = "'CXX=${CXX}' 'CC=${CC}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'DESTDIR=${D}' 'SDKTARGETSYSROOT=${STAGING_DIR_HOST}'"

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

