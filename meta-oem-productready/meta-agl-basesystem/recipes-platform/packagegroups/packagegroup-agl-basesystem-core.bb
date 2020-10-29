DESCRIPTION = "AGL Core Package Groups"
LICENSE = "Apache-2.0"

DEPENDS += " \
	   agl-basefiles \
	   agl-systemd \
           "

inherit packagegroup

PACKAGES = "\
	packagegroup-agl-basesystem-core \
	"

RDEPENDS_packagegroup-agl-basesystem-core = "\
	agl-basefiles \
	sudo \
	agl-systemd \
	"
