SUMMARY = "Systemd related file for launching sample application"
LICENSE     = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=agl-systemd/;branch=${AGL_BRANCH}"
SRCREV := "${AGL_DEFAULT_REVISION}"

PV = "1.0.0+gitr${SRCPV}"
S = "${WORKDIR}/agl-systemd"

inherit systemd

SYSTEMD_SERVICE_${PN} = " \
    setup_refhw.service \
    launch_sm.service \
    agl-trigger.service \
"

DEPENDS += " \
    agl-basefiles \
"

RDEPENDS_${PN} += " \
    bash \
"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}${systemd_unitdir}/system
	install -m 644 ${S}/setup_refhw.service ${D}/${systemd_unitdir}/system
	install -m 644 ${S}/agl-trigger.service ${D}/${systemd_unitdir}/system
	install -m 644 ${S}/launch_sm.service ${D}/${systemd_unitdir}/system

	install -d ${D}/etc/systemd/system
	install -m 644 ${S}/systemd-udev-trigger.service ${D}/etc/systemd/system
	install -d ${D}/etc/systemd/system/tmp.mount.d
	install -m 644 ${S}/options.conf ${D}/etc/systemd/system/tmp.mount.d

	install -d ${D}${LOCALDIR}/tool_9E_SI
	install -m 755 ${S}/tool_9E_SI/*.sh ${D}${LOCALDIR}/tool_9E_SI
	install -m 644 ${S}/env.txt ${D}${LOCALDIR}/tool_9E_SI
	
	install -d ${D}${CONFDIR}/target 
	install -m 644 ${S}/usr/target/*.lst ${D}${CONFDIR}/target

        install -d ${D}/lib/udev/rules.d
	install -m 644 ${S}/99-agl.rules ${D}/lib/udev/rules.d

	install -d -m 777 ${D}${LOCALDIR}/nv/export
	install -d -m 777 ${D}${LOCALDIR}/nv/backup
	install -d -m 777 ${D}${LOCALDIR}/nv/log/frameworkunifiedlog
	install -d -m 777 ${D}${LOCALDIR}/ramd/bkup
}

AGL_BRANCH = "sandbox/Riku.Nomoto/WIP_fixpath"
