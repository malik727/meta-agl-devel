DESCRIPTION = "hal Package Groups"
LICENSE = "CLOSED"
PR = "r1"

DEPENDS_qemux86-64 = "agl-basefiles"
DEPENDS_qemuarm64 = "agl-basefiles"

#
# packages which content depend on MACHINE_FEATURES need to be MACHINE_ARCH
#
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

PACKAGES = "\
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

