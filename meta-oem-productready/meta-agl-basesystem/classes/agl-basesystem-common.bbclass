RDEPENDS_${PN} += " agl-basefiles "

DEPENDS_append = " agl-basefiles"

EXTRA_OEMAKE = "'CXX=${CXX} ${CODINGRULES_CPP_21MM}' 'CC=${CC} ${CODINGRULES_C_21MM}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'DESTDIR=${D}' 'SDKTARGETSYSROOT=${STAGING_DIR_HOST}'"

do_compile (){
    cd ${S}/${MAKE_DIR}
    oe_runmake
}

do_install (){
    cd ${S}/${MAKE_DIR}
    oe_runmake DESTDIR=${D} install
}

sysroot_stage_all_append(){
    sysroot_stage_dir ${D}/usr ${SYSROOT_DESTDIR}/usr
    sysroot_stage_dir ${D}${CONFDIR}/systemmanager ${SYSROOT_DESTDIR}${CONFDIR}/systemmanager
    sysroot_stage_dir ${D}${CONFDIR}/backup_manager ${SYSROOT_DESTDIR}${CONFDIR}/backup_manager
    sysroot_stage_dir ${D}${LOCALDIR}/nv/BS/ns/npp/rwdata ${SYSROOT_DESTDIR}${LOCALDIR}/nv/BS/ns/npp/rwdata
}
