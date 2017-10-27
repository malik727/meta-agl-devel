SUMMARY     = "Sound Manager client library for application"
HOMEPAGE    = "https://wiki.automotivelinux.org/soundmanager"
S = "${WORKDIR}/git"
SECTION = "multimedia"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=ae6497158920d9524cf208c09cc4c984"
DEPENDS = "af-binder json-c"
RDEPENDS_${PN} = "agl-service-soundmanager-2017"

#SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/libsoundmanager.git;protocol=https;branch=master"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/libsoundmanager.git;protocol=https;branch=sandbox/knimitz/hmi-framework"
SRCREV = "2fee4a6fd0612d1336e5be87f4e9369f27ebb52d"

inherit cmake
