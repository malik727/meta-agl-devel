FILES_SOLIBSDEV = ""
FILES_${PN}-staticdev = ""

EXTRA_OEMAKE = "'CXX=${CXX}' 'CC=${CC}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'DESTDIR=${D}' 'SDKTARGETSYSROOT=${STAGING_DIR_HOST}'"

DEPENDS_append = " agl-basefiles" 

do_install (){
    install -d ${D}${includedir}/basesystem
    install -D -m 644 ${S}/hal_api/*.h ${D}${includedir}/basesystem
    install -d ${D}${libdir}/

    cd ${S}
    oe_runmake install
}

