SUMMARY = "os-rpclibrary for AGL software"
DESCRIPTION = "os-rpclibrary to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

FILES_${PN} += "${LIBDIR}/*"
 
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/other;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/other"

#Added here because they are native recipes, although they are AGLs
DEPENDS += " \
    ns-commonlibrary \
    ns-loglibrary \
    bison-native \
"

inherit agl-basesystem-common

RDEPENDS_${PN} += " \
    ns-commonlibrary \
    ns-loglibrary \
"
EXTRA_MAKEFILE=" -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"
MAKE_DIR ="rpc_library"

AGL_BRANCH = "sandbox/ruke47/complete_build"
