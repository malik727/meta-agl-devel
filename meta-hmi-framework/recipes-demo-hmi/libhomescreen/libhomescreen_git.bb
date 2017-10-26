SUMMARY     = "HomeScreen client library for application"
SECTION = "HMI"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=ae6497158920d9524cf208c09cc4c984"
DEPENDS = "af-binder json-c"
RDEPENDS_${PN} = "agl-service-homescreen-2017"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/p/src/libhomescreen.git;protocol=http;branch=sandbox/knimitz/hmi-framework"
SRCREV = "81efec650316d867a42be6a07c8569c3b5fbe7f1"
S = "${WORKDIR}/git"

inherit cmake
