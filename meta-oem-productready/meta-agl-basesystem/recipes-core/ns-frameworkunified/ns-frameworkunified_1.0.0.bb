SUMMARY = "ns-frameworkunified for AGL software"
DESCRIPTION = "ns-frameworkunified to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${MAKE_DIR}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

# Common Dependencies
DEPENDS += " \
    os-posixbasedos001legacylibrary \
    ns-loglibrary \
    ns-commonlibrary \
    libxml2 \
    boost \
"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/native/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/native"

inherit agl-basesystem-common

MAKE_DIR ="framework_unified"

do_compile (){
     cd ${S}/${MAKE_DIR}

    # build libNS_FrameworkUnified.so first
    # then build libNS_XMLConfigParse.so
     oe_runmake -f Makefile.client
     oe_runmake -f Makefile.library
}

do_install (){
    cd ${S}/${MAKE_DIR}
    oe_runmake -f Makefile.client DESTDIR=${D} install
    oe_runmake -f Makefile.library DESTDIR=${D} install
}

FILES_${PN} += "${libdir}/*"

RDEPENDS_${PN} += " \
    os-posixbasedos001legacylibrary \
    ns-loglibrary \
    ns-commonlibrary \
"
