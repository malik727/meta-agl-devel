RDEPENDS_${PN} += " agl-basefiles "

DEPENDS_append = " agl-basefiles"

EXTRA_OEMAKE = "'CXX=${CXX} ${CODINGRULES_CPP_21MM}' 'CC=${CC} ${CODINGRULES_C_21MM}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'DESTDIR=${D}' 'SDKTARGETSYSROOT=${STAGING_DIR_HOST}'"

# not set do_install
do_install (){
    oe_runmake DESTDIR=${D} install
}
