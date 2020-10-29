DESCRIPTION = "AGL Core Package Groups"
LICENSE = "CLOSED"
PR = "r1"


DEPENDS += " \
	   agl-basefiles \
	   agl-systemd \
           "

#
# packages which content depend on MACHINE_FEATURES need to be MACHINE_ARCH
#
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

PACKAGES = "\
	packagegroup-agl-basesystem-core \
	"

RDEPENDS_packagegroup-agl-basesystem-core = "\
	agl-basefiles \
	sudo \
	agl-systemd \
	"

RDEPENDS_packagegroup-agl-basesystem-core-dbg = "\
	sysklogd \
	strace \
	uftrace \
	sysstat \
	valgrind \
	"
