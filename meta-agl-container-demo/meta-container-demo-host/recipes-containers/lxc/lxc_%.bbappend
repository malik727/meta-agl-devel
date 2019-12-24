FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " \
    file://dnsmasq.agl-demo.conf \
    "

FILES_${PN} += "${systemd_confdir}/lxc/dnsmasq.agl-demo.conf"

do_install_append() {
    #
    # configuration of lxc-net for AGL demo
    #
    sed -e '/LXC_ADDR=/s/"\([^"]*\)"/"192.168.20.1"/' \
        -e '/LXC_NETWORK=/s/"\([^"]*\)"/"192.168.20.0\/24"/' \
        -e '/LXC_DHCP_RANGE=/s/"\([^"]*\)"/"192.168.20.2,192.168.20.254"/' \
        -e '/LXC_DHCP_CONFILE=/s/"\([^"]*\)"/"\/etc\/lxc\/dnsmasq.agl-demo.conf"/' \
        -i ${D}${sysconfdir}/default/lxc-net

    install -Dm 0644 ${WORKDIR}/dnsmasq.agl-demo.conf ${D}${sysconfdir}/lxc/
}