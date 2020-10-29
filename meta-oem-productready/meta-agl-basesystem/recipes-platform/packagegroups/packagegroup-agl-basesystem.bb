DESCRIPTION = "BaseSystem Package Groups"
LICENSE = "CLOSED"
PR = "r1"

DEPENDS = " "

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

PACKAGES = "\
        packagegroup-agl-basesystem \
        "
ALLOW_EMPTY_${PN} = "1"

RDEPENDS_${PN} += "\
    packagegroup-agl-image-minimal \
    "

RDEPENDS_${PN}  += "\
        packagegroup-agl-basesystem-core \
        packagegroup-agl-basesystem-graphics \
        packagegroup-agl-basesystem-service \
        packagegroup-agl-basesystem-hal \
	"


