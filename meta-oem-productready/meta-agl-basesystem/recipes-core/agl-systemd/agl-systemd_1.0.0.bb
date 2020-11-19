SUMMARY = "Systemd related file for launching sample application"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/agl-systemd/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"
inherit systemd
S = "${WORKDIR}"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=agl-systemd/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

FILES_${PN} += "\
    ${NVPATH}/tool_9E_SI/* \
    ${NVPATH}/usr/target/* \
    /usr/* \
    ${NVPATH}/* \
    ${NVPATH}/ramd/bkup \
    /etc/systemd/system/tmp.mount.d \
"
SYSTEMD_SERVICE_${PN} = " \
    setup_refhw.service \
    launch_sm.service \
    agl-trigger.service \
"
DEPENDS += " \
    libxml2-native \
    agl-basefiles-native \
"
RDEPENDS_${PN} += " \
    procps \
    agl-basefiles \
    bash \
"
do_compile[depends] += "agl-basefiles:do_populate_sysroot"

do_install() {
	install -d ${D}${systemd_unitdir}/system
	install -m 644 ${WORKDIR}/agl-systemd/setup_refhw.service ${D}/${systemd_unitdir}/system
	install -m 644 ${WORKDIR}/agl-systemd/agl-trigger.service ${D}/${systemd_unitdir}/system
	install -m 644 ${WORKDIR}/agl-systemd/launch_sm.service ${D}/${systemd_unitdir}/system
	install -d ${D}/etc/systemd/system
	install -m 644 ${WORKDIR}/agl-systemd/systemd-udev-trigger.service ${D}/etc/systemd/system
	install -d ${D}${NVPATH}/tool_9E_SI
	install -m 644 ${WORKDIR}/agl-systemd/*.txt ${D}${NVPATH}/tool_9E_SI
	install -m 755 ${WORKDIR}/agl-systemd/tool_9E_SI/*.sh ${D}${NVPATH}/tool_9E_SI
	install -d ${D}${NVPATH}/usr/target 
	install -m 644 ${WORKDIR}/agl-systemd/usr/target/*.lst ${D}${NVPATH}/usr/target
	install -d ${D}/etc/systemd/system
        install -d ${D}/lib/udev/rules.d
	install -m 644 ${WORKDIR}/agl-systemd/99-agl.rules ${D}/lib/udev/rules.d
	install -d -m 777 ${D}${NVPATH}/export
	install -d -m 777 ${D}${NVPATH}/backup
	install -d -m 777 ${D}${NVPATH}/log/frameworkunifiedlog
	install -d -m 777 ${D}${NVPATH}/ramd/bkup
	install -d ${D}/etc/systemd/system/tmp.mount.d
	install -m 644 ${WORKDIR}/agl-systemd/options.conf ${D}/etc/systemd/system/tmp.mount.d
}

sysroot_stage_all_append(){
	sysroot_stage_dir ${D}${NVPATH}/tool_9E_SI ${SYSROOT_DESTDIR}${NVPATH}/tool_9E_SI
	sysroot_stage_dir ${D}${NVPATH}/usr/target ${SYSROOT_DESTDIR}${NVPATH}/usr/target
	sysroot_stage_dir ${D}/usr ${SYSROOT_DESTDIR}/usr
	sysroot_stage_dir ${D}${NVPATH}/ns/npp/rwdata ${SYSROOT_DESTDIR}${NVPATH}/ns/npp/rwdata
	sysroot_stage_dir ${D}/etc/systemd/system/tmp.mount.d ${SYSROOT_DESTDIR}/etc/systemd/system/tmp.mount.d
}
