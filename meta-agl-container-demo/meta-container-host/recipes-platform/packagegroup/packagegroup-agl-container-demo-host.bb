SUMMARY = "The software for demo platform of AGL container"
DESCRIPTION = "A set of packages belong to AGL Contaner Demo Host"

LICENSE = "MIT"

PACKAGES = "\
    packagegroup-agl-container-demo-host \
    "

ALLOW_EMPTY_${PN} = "1"

RDEPENDS_${PN} += "\
    packagegroup-agl-container-host \
    "

#
# Added recipes of weston (wayland-compositor)
#
# Because of libdrm issue, container demo has nested weston compositor.
# Host: weston(drm-backend), Guest: weston(wayland-backend)
#
# Ref. packagegroup-agl-graphical-weston
#
RDEPENDS_${PN} += "\
    weston \
    wayland-ivi-extension \
    weston-init \
    weston-ini-conf \
    "

RDEPENDS_${PN} += "\
    guests-filesystem \
    "

# Add most and sllin driver
RDEPENDS_${PN} += "\
    unicens-config \
    most \
    sllin \
    "

# Radio?
RDEPENDS_${PN} += "\
    linux-firmware-ralink \
    "

# Pipewire
RDEPENDS_${PN} += "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'pipewire', 'pipewire', '', d)} \
    "
