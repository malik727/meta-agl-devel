AGL_CONTAINER_MAC_ADDR ??= "00:16:3e:cf:07:ff"

do_install_append() {
    # override network interface configuration
    sed -i -e "/lxc.net.0.type/s/=\(.*\)/ = veth\n\
lxc.net.0.name = eth0\n\
lxc.net.0.link = lxcbr0\n\
lxc.net.0.flags = up\n\
lxc.net.0.veth.mode = bridge\n\
lxc.net.0.hwaddr = ${AGL_CONTAINER_MAC_ADDR}/" \
              ${D}/config
}