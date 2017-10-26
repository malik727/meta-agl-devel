SUMMARY     = "Sound Manager binding"
ESCRIPTION = "Sound Manager is the binding library to communicate \
	with Genivi Audio Manager. Genivi Audio Manager is the policy manager \
	"
HOMEPAGE    = "https://wiki.automotivelinux.org/soundmanager"
S = "${WORKDIR}/git"
SECTION = "multimedia"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=ae6497158920d9524cf208c09cc4c984"
DEPENDS = "dbus glib-2.0 af-binder json-c"
RDEPENDS_${PN} = "audiomanager audiomanager-plugins"

#SRC_URI = "git://gerrit.automotivelinux.org/gerrit/apps/agl-service-soundmanager-2017;protocol=https;branch=master"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/apps/agl-service-soundmanager-2017;protocol=https;branch=sandbox/knimitz/hmi-framework"
SRCREV = "d8a125b3348826b5d993568c631c096102d9e1ac"

inherit cmake aglwgt
