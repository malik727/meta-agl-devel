FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " \
    file://connman.disable_dns_proxy.conf \
    "

FILES_${PN} += "${systemd_unitdir}/system/connman.service.d/disable_dns_proxy.conf"

do_install_append() {
    # add veth to blacklist
    sed -i 's/^\(NetworkInterfaceBlacklist=.*\)/\1,veth/' ${D}${sysconfdir}/connman/main.conf

    # resolve conflict between systemd and dnsmasq
    install -Dm 0644 ${WORKDIR}/connman.disable_dns_proxy.conf ${D}${systemd_unitdir}/system/connman.service.d/disable_dns_proxy.conf
}