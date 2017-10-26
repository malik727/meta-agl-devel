SUMMARY     = "Window Manager binding and client library for application"
DESCRIPTION = "Window Manager 2017 is the binding library"
HOMEPAGE    = ""
S = "${WORKDIR}/git"
SECTION = "graphics"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"
DEPENDS = "af-binder json-c wayland wayland-ivi-extension wayland-native"
RDEPENDS_${PN} = ""

#SRC_URI = "git://gerrit.automotivelinux.org/gerrit/apps/agl-service-windowmanager-2017;protocol=https;branch=master"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/apps/agl-service-windowmanager-2017;protocol=https;branch=sandbox/yuta-d/hmi-framework"
SRCREV = "77e04dd7cd2e2d43ae20ca5a377b131d1cbf0319"

inherit cmake aglwgt

#If you would like to output log, uncomment out
#EXTRA_OECMAKE = " -DENABLE_DEBUG_OUTPUT=ON "
