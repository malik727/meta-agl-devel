RRECOMENDS_${PN} += "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'lxc', 'lxc-config dhcp-client', '', d)} \
    "
