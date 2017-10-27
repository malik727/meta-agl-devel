SUMMARY     = "Window Manager client library for application"
S = "${WORKDIR}/git"
SECTION = "graphics"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"
#LIC_FILES_CHKSUM = "file://LICENSE;md5=ae6497158920d9524cf208c09cc4c984"
DEPENDS = "af-binder json-c"
RDEPENDS_${PN} = "agl-service-windowmanager-2017"

#SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/libwindowmanager.git;protocol=https;branch=master"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/libwindowmanager.git;protocol=https;branch=sandbox/yuta-d/hmi-framework"
SRCREV = "70d843bfc9ecbd644481becdd93114d092cbbdd7"

inherit cmake
