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
