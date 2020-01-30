SUMMARY     = "Launcher of LXC system container of AGL Instrument Cluster Container Demo"
DESCRIPTION = "The 'runlxc' is a manager of LXC container which manages lifecycle of LXC container integrated with AGL Instrument Cluster Container Demo"
LICENSE     = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "wayland wayland-ivi-extension lxc"

inherit cmake systemd

SRC_URI = "git://github.com/cf47mn/lxc-launcher.git;protocol=https;branch=${AGL_BRANCH} \
           file://lxc-launcher.service \
           file://runlxc.conf \
          "
SRCREV  = "${AGL_APP_REVISION}"

PV = "1.0+git${SRCPV}"
S  = "${WORKDIR}/git"

SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE_${PN} = "lxc-launcher.service"
SYSTEMD_AUTO_ENABLE_${PN} = "enable"

do_install_append() {
      install -d ${D}${sysconfdir}/lxc
      install -m 644 -p -D ${WORKDIR}/runlxc.conf ${D}${sysconfdir}/lxc/runlxc.conf

      if ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'true', 'false', d)}; then
              install -d ${D}${systemd_system_unitdir}
              install -m 644 -p -D ${WORKDIR}/lxc-launcher.service ${D}${systemd_system_unitdir}/lxc-launcher.service
       fi
}