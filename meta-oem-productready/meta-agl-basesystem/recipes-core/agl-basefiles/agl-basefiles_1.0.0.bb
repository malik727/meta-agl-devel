SUMMARY = "base-files for AGL software"
DESCRIPTION = "install base-files to build AGL software"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

BBCLASSEXTEND = "native nativesdk"

SRC_URI += " \
    file://LICENSE \
    file://bin \
    file://share \
    file://BS \
    file://include \
    file://agldd \
"

FILES_${PN} += " \
    /bin/* \
    /agldd/* \
    /include/* \
    /BS/ns/npp/rwdata/* \
    /share/* \
    /usr/agl/conf/backup_manager/* \
    /usr/agl/conf/systemmanager/* \
    /nv/BS/ns/npp/rwdata/* \
"
#ALLOW_EMPTY_${PN} = "1"

FILES_${PN}-dev += " \ 
    /usr/agl/share/* \
    /usr/agl/include/* \
    /usr/agl/include/agldd/* \
    /usr/include/linux/* \
"
S = "${WORKDIR}"

#RDEPENDS_${PN} += " libcap-bin sudo"
#RDEPENDS_${PN}-dbg += " sysklogd strace"

do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_package_qa[noexec] = "1"
do_install[depends] += "virtual/kernel:do_shared_workdir"

do_install() {
        install -C -d ${D}/usr/agl/share/
        install -C -d ${D}/usr/agl/include/agldd/
        install -C -d ${D}/usr/include/linux/
        install -C -d ${D}/nv/BS/ns/npp/rwdata/
        install -m 644 ${WORKDIR}/agldd/* ${D}/usr/agl/include/agldd/
        install -m 644 ${WORKDIR}/include/* ${D}/usr/agl/include/
        install -m 644 ${WORKDIR}/share/* ${D}/usr/agl/share/
        install -m 644 ${WORKDIR}/BS/ns/npp/rwdata/* ${D}/nv/BS/ns/npp/rwdata
        install -m 775 ${WORKDIR}/bin/launch_xml2cfg.sh ${D}/usr/agl/share/
        install -D -m 0644 ${TMPDIR}/work-shared/${MACHINE}/kernel-build-artifacts/include/generated/autoconf.h ${D}/usr/include/linux/
}

sysroot_stage_all_append(){
	sysroot_stage_dir ${D}/usr/agl ${SYSROOT_DESTDIR}${base_prefix}/usr/agl
}

