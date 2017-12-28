SUMMARY     = "A wrapper library of libwindowmanager for Qt Application in AGL"
SECTION     = "graphics"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS = "qtbase libwindowmanager"
RDEPENDS_${PN} = "libwindowmanager"

inherit qmake5

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/qlibwindowmanager.git;protocol=https;branch=${AGL_BRANCH}"
SRCREV = "4f547443ee1b6d6c5653dd3bea8642a55ea08b3e"
S = "${WORKDIR}/git"
