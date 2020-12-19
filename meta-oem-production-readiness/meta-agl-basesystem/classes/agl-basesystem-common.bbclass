inherit bsmake

DEPENDS_append = " agl-basefiles"

EXTRA_OEMAKE = "'DESTDIR=${D}'"

RDEPENDS_${PN} += " agl-basefiles "
