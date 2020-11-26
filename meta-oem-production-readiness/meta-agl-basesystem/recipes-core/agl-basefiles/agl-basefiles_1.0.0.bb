SUMMARY = "base-files for AGL software"
DESCRIPTION = "install base-files to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

BBCLASSEXTEND = "native nativesdk"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=agl-basefiles;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

PV = "1.0.0+gitr${SRCPV}"

S = "${WORKDIR}/agl-basefiles"

do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_install[depends] += "virtual/kernel:do_shared_workdir"

do_install() {
        install -d ${D}${includedir}/basesystem/agldd
        install -m 644 -D ${S}/include/* ${D}${includedir}/basesystem/
        install -m 644 -D ${S}/agldd/* ${D}${includedir}/basesystem/agldd/

        install -d ${D}${datadir}/basesystem
        install -m 644 -D ${S}/share/* ${D}${datadir}/basesystem/
        install -m 755 -D ${S}/bin/launch_xml2cfg.sh ${D}${datadir}/basesystem/

        # LOCALDIR is defined at conf/include/agl-basesystem-base.inc
        install -d ${D}${LOCALDIR}/nv/BS/ns/npp/rwdata/
        install -m 644 -D ${S}/BS/ns/npp/rwdata/* ${D}${LOCALDIR}/nv/BS/ns/npp/rwdata/

        install -d ${D}${includedir}/linux
        install -D -m 0644 ${TMPDIR}/work-shared/${MACHINE}/kernel-build-artifacts/include/generated/autoconf.h ${D}${includedir}/linux/
}

FILES_${PN} += " \
    ${LOCALDIR}/nv/BS/ns/npp/rwdata/* \
"

FILES_${PN}-dev += " \
    ${datadir}/basesystem/* \
    ${includedir}/basesystem/* \
"
