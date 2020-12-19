SUMMARY = "Systemd related file for launching sample application"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"

DEPENDS += " agl-basefiles"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;branch=${BASESYSTEM_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/git/agl-systemd"

inherit systemd

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}${systemd_unitdir}/system
	install -m 644 ${S}/agl-trigger.service ${D}/${systemd_unitdir}/system
	install -m 644 ${S}/launch_sm.service ${D}/${systemd_unitdir}/system

	install -d ${D}/etc/systemd/system
	install -m 644 ${S}/systemd-udev-trigger.service ${D}/etc/systemd/system
	install -d ${D}/etc/systemd/system/tmp.mount.d
	install -m 644 ${S}/options.conf ${D}/etc/systemd/system/tmp.mount.d

	install -d ${D}${sysconfdir}/basesystem
	install -m 644 ${S}/env.txt ${D}${sysconfdir}/basesystem

	install -d ${D}${LOCALDIR}/tool_9E_SI
	install -m 755 ${S}/tool_9E_SI/*.sh ${D}${LOCALDIR}/tool_9E_SI

	install -d ${D}${CONFDIR}/target
	install -m 644 ${S}/usr/target/*.lst ${D}${CONFDIR}/target

        install -d ${D}/lib/udev/rules.d
	install -m 644 ${S}/99-agl.rules ${D}/lib/udev/rules.d

	install -d -m 777 ${D}${LOCALDIR}/nv/export
	install -d -m 777 ${D}${LOCALDIR}/nv/backup
	install -d -m 777 ${D}${LOCALDIR}/nv/log/frameworkunifiedlog
	install -d -m 777 ${D}${LOCALDIR}/ramd/bkup
}

RDEPENDS_${PN} += "bash"

SYSTEMD_SERVICE_${PN} = " \
    launch_sm.service \
    agl-trigger.service \
"
