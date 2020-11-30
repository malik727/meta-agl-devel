inherit bshalmake

FILES_${PN}-dev_remove = "${FILES_SOLIBSDEV}" 
FILES_${PN}-staticdev = ""

EXTRA_OEMAKE = "'CXX=${CXX}' 'CC=${CC}' 'RANLIB=${RANLIB}' 'AR=${AR}' 'DESTDIR=${D}' 'SDKTARGETSYSROOT=${STAGING_DIR_HOST}'"

DEPENDS_append = " agl-basefiles"


