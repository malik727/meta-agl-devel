200~${sysconfdir}SUMMARY = "base-files for AGL software"
DESCRIPTION = "install base-files to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/agl-basefiles/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

BBCLASSEXTEND = "native nativesdk"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=agl-basefiles;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

FILES_${PN} += " \
    /agl-basefiles/bin/* \
    /agl-basefiles/agldd/* \
    /agl-basefiles/include/* \
    /agl-basefiles/BS/ns/npp/rwdata/* \
    /agl-basefiles/share/* \
    ${CONFDIR}/backup_manager/* \
    ${CONFDIR}/systemmanager/* \
    ${NVPATH}/ns/npp/rwdata/* \
"

FILES_${PN}-dev += " \ 
    ${SHAREDIR}/* \
    ${INCLUDEDIR}/* \
    ${INCLUDEDIR}/agl-basefiles/agldd/* \
    ${INCLUDEDIR}/linux/* \
"
S = "${WORKDIR}"

do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_package_qa[noexec] = "1"
do_install[depends] += "virtual/kernel:do_shared_workdir"

do_install() {
        install -C -d ${D}${SHAREDIR}/
        install -C -d ${D}${INCLUDEDIR}/agldd/
        install -C -d ${D}${INCLUDEDIR}/linux/
        install -C -d ${D}${NVPATH}/ns/npp/rwdata/
        install -m 644 ${WORKDIR}/agl-basefiles/agldd/* ${D}${INCLUDEDIR}/agldd/
        install -m 644 ${WORKDIR}/agl-basefiles/share/* ${D}${SHAREDIR}/
        install -m 644 ${WORKDIR}/agl-basefiles/BS/ns/npp/rwdata/* ${D}${NVPATH}/ns/npp/rwdata
        install -m 775 ${WORKDIR}/agl-basefiles/bin/launch_xml2cfg.sh ${D}${SHAREDIR}/
        install -D -m 0644 ${TMPDIR}/work-shared/${MACHINE}/kernel-build-artifacts/include/generated/autoconf.h ${D}${INCLUDEDIR}/linux/
}

sysroot_stage_all_append(){
	sysroot_stage_dir ${D}/usr ${SYSROOT_DESTDIR}${base_prefix}/usr
}

