SUMMARY     = "HomeScreen client library for application"
SECTION = "HMI"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=ae6497158920d9524cf208c09cc4c984"
DEPENDS = "af-binder json-c"
RDEPENDS_${PN} = "agl-service-homescreen-2017"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/libhomescreen.git;protocol=https;branch=master"
# This revision will be changed if the https://gerrit.automotivelinux.org/gerrit/#/c/11443/ go throgh
SRCREV = "1210883bae3580bd60107d3a746b6b557d002d33"
S = "${WORKDIR}/git"

inherit cmake
