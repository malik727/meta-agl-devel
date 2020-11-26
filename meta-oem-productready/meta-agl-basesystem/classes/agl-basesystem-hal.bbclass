FILES_SOLIBSDEV = ""

FILES_${PN}-staticdev = ""

EXTRA_OEMAKE = "'CXX=${CXX}' 'CC=${CC}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'DESTDIR=${D}' 'SDKTARGETSYSROOT=${STAGING_DIR_HOST}'"

DEPENDS_append = " agl-basefiles" 

do_install (){
    cd ${S}/hal_api
    install -d ${D}${INCLUDEDIR}
    install -D -m 644 *.h ${D}${INCLUDEDIR}
    install -d ${D}/usr/lib/basesystem/

    cd ${S}
    oe_runmake install
}

