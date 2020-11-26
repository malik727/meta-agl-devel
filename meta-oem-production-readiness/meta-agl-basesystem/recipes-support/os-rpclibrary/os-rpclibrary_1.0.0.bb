SUMMARY = "os-rpclibrary for AGL software"
DESCRIPTION = "os-rpclibrary to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " \
    ns-commonlibrary \
    ns-loglibrary \
    bison-native \
"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/other;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

S = "${WORKDIR}/other"

inherit agl-basesystem-common

EXTRA_MAKEFILE = " -f Makefile.client"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"

MAKE_DIR ="rpc_library"

do_compile () {
    cd ${S}/${MAKE_DIR}
    oe_runmake
}

do_install (){
    cd ${S}/${MAKE_DIR}
    oe_runmake DESTDIR=${D} install
}

FILES_${PN} += "/usr/lib/basesystem/librpc.so"

RDEPENDS_${PN} += " \
    ns-commonlibrary \
    ns-loglibrary \
"
