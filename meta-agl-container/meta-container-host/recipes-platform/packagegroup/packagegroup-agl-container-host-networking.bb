DESCRIPTION = "The packages for networking required by AGL Container Host"
LICENSE = "MIT"

inherit packagegroup

PACKAGES = "\
    packagegroup-agl-container-host-networking \
    "

ALLOW_EMPTY_${PN} = "1"

RDEPENDS_${PN} += "\
    connman \
    connman-client \
    connman-tools \
    iproute2 \
    dhcp-client \
    "