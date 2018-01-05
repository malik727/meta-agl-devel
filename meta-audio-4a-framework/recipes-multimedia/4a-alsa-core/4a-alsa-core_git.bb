SUMMARY     = "4A - Low Level Alsa Binding"
DESCRIPTION = "Low Level Alsa Binding for 4A (AGL Advanced Audio Agent)"
HOMEPAGE    = "https://git.automotivelinux.org/src/4a-alsa-core/"
SECTION     = "apps"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "gitsm://gerrit.automotivelinux.org/gerrit/src/4a-alsa-core;protocol=https;branch=${AGL_BRANCH}"
SRCREV = "fe50b1e24283d14f9d516c1885819b2f520e3647"

PV = "0.1+git${SRCPV}"
S  = "${WORKDIR}/git"

inherit afb-system-cmake

FILES_${PN}-dev += "${INSTALL_PREFIX}/4a-alsa-core/htdocs"

FILES_${PN} += "${INSTALL_PREFIX}/4a-alsa-core"
FILES_${PN} += "${INSTALL_PREFIX}/lib"
