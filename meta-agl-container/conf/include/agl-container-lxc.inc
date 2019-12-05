# for host
# install lxc and lxc-networking
IMAGE_INSTALL_append = "${@bb.utils.contains('DISTRO_FEATURES', 'agl-container-host', ' lxc lxc-networking', '', d)}"

# for guest
# install dhcp-client
IMAGE_INSTALL_append = "${@bb.utils.contains('DISTRO_FEATURES', 'agl-container-guest', ' lxc-config dhcp-client', '', d)}"
