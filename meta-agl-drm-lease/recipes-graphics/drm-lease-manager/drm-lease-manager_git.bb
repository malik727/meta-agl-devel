LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/src/drm-lease-manager;branch=sandbox/dhobsong/v0.1.0-rc \
           file://drm-lease-manager.service \
           "

PV = "0.1+git${SRCPV}"
SRCREV = "3e954b59d1f0a538d42e2dec7c84bab9103a821e"

S = "${WORKDIR}/git"

inherit meson
inherit systemd

DEPENDS = "libdrm"

do_install_append() {
    install -d ${D}/${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/drm-lease-manager.service ${D}/${systemd_unitdir}/system
    rm -rf ${D}/${localstatedir}
}

SYSTEMD_SERVICE_${PN} = "drm-lease-manager.service"

