SUMMARY     = "Launcher of LXC system container of AGL CES Container Demo"
DESCRIPTION = "The 'runlxc' is a simple container manager of AGL CES Container Demo"
LICENSE     = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "wayland wayland-ivi-extension lxc"

inherit cmake systemd

SRC_URI = "git://github.com/cf47mn/lxc-launcher.git;protocol=https;branch=dev \
           file://lxc-launcher.service \
           file://runlxc.qemu-ic-example.conf \
           file://runlxc.qemu-ivi-example.conf \
           file://runlxc.rcar3-example.conf \
          "
SRCREV  = "${AGL_APP_REVISION}"

PV = "1.0+git${SRCPV}"
S  = "${WORKDIR}/git"

SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE_${PN} = "lxc-launcher.service"
SYSTEMD_AUTO_ENABLE_${PN} = "enable"
SYSTEMD_AUTO_ENABLE_${PN}_qemuall = "disable"

do_install_append() {
      install -d ${D}${sysconfdir}/lxc
      install -m 644 -p -D ${WORKDIR}/runlxc.qemu-ic-example.conf ${D}${sysconfdir}/lxc/runlxc.qemu-ic-example.conf
      install -m 644 -p -D ${WORKDIR}/runlxc.qemu-ivi-example.conf ${D}${sysconfdir}/lxc/runlxc.qemu-ivi-example.conf
      install -m 644 -p -D ${WORKDIR}/runlxc.rcar3-example.conf ${D}${sysconfdir}/lxc/runlxc.rcar3-example.conf
      ln -sf runlxc.rcar3-example.conf ${D}${sysconfdir}/lxc/runlxc.conf

      if ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'true', 'false', d)}; then
              install -d ${D}${systemd_system_unitdir}
              install -m 644 -p -D ${WORKDIR}/lxc-launcher.service ${D}${systemd_system_unitdir}/lxc-launcher.service
       fi
}