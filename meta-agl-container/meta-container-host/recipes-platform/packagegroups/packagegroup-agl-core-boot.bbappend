RRECOMENDS_${PN} += "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'lxc', 'lxc lxc-networking', '', d)} \
    "
