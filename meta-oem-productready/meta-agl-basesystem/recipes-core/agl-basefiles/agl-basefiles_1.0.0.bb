SUMMARY = "base-files for AGL software"
DESCRIPTION = "install base-files to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

BBCLASSEXTEND = "native nativesdk"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=agl-basefiles;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

S = "${WORKDIR}/agl-basefiles"

do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_package_qa[noexec] = "1"

do_install() {
        install -d ${D}${includedir}/agl-bs/agldd
        install -m 644 -D ${S}/include/* ${D}${includedir}/agl-bs/
        install -m 644 -D ${S}/agldd/* ${D}${includedir}/agl-bs/agldd/

        install -d ${D}${datadir}/agl-bs
        install -m 644 -D ${S}/share/* ${D}${datadir}/agl-bs/
        install -m 755 -D ${S}/bin/launch_xml2cfg.sh ${D}${datadir}/agl-bs/

        # NVPATH is defined at conf/include/agl-basesystem-base.inc
        install -d ${D}${NVPATH}/ns/npp/rwdata/
        install -m 644 -D ${S}/BS/ns/npp/rwdata/* ${D}${NVPATH}/ns/npp/rwdata/
}

FILES_${PN} += " \
    ${NVPATH}/ns/npp/rwdata/* \
"

FILES_${PN}-dev += " \
    ${datadir}/agl-bs/* \
    ${includedir}/agl-bs/* \
"
