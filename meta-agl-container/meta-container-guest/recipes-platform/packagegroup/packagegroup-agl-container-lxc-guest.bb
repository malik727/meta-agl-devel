DESCRIPTION = "The minimal set of packages required by AGL Container Guest"
LICENSE = "MIT"

inherit packagegroup

PACKAGES = "\
    packagegroup-agl-container-lxc-guest \
    "

ALLOW_EMPTY_${PN} = "1"

#
# LXC configuration
#
RDEPENDS_${PN} += "\
    lxc-config \
    "
