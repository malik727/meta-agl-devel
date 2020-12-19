inherit bshalmake

FILES_${PN}-dev_remove = "${FILES_SOLIBSDEV}" 

EXTRA_OEMAKE = "'DESTDIR=${D}'"

DEPENDS_append = " agl-basefiles"


