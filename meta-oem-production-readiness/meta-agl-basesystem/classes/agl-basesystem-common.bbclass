inherit bsmake

DEPENDS_append = " agl-basefiles"

EXTRA_OEMAKE = "'CXX=${CXX} ${CODINGRULES_CPP_21MM}' 'CC=${CC} ${CODINGRULES_C_21MM}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'DESTDIR=${D}'"

RDEPENDS_${PN} += " agl-basefiles "
