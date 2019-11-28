DESCRIPTION = "The minimal set of packages required by AGL Container Host"
LICENSE = "MIT"

inherit packagegroup

PACKAGES = "\
    packagegroup-agl-container-host \
    "

ALLOW_EMPTY_${PN} = "1"

RDEPENDS_${PN} += "\
    packagegroup-agl-core-boot \
    packagegroup-machine-base \
    "

# For AGL appfw
#  appended by meta-agl/meta-app-framework of packagegroup-agl-image-[minimal|boot].bbappend
#
RDEPENDS_${PN} += "\
    packagegroup-agl-app-framework \
    "

# For smack/cynara
#   packagegroup-agl-core-security.bbappend
#
RDEPENDS_${PN} += "\
    packagegroup-agl-core-security \
    "

# For network
#
RDEPENDS_${PN} += "\
    packagegroup-agl-container-host-networking \
    "