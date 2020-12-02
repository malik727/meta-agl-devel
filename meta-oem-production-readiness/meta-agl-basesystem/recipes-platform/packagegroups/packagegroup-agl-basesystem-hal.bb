DESCRIPTION = "hal Package Groups"
LICENSE = "Apache-2.0"

inherit packagegroup

PACKAGES = " \
    packagegroup-agl-basesystem-hal \
"

RDEPENDS_${PN} += " \
    libboot-hal \
    libcan-hal \
    libclock-hal \
    libdeck-hal \
    libinput-hal \
    libnv-hal \
    libpositioning-hal \
    libpower-hal \
    libsecurity-hal \
    libsoctemperature-hal \
    libupdate-hal \
    libusb-hal \
    libvehicle-hal \
    libvideo-in-hal \
"
