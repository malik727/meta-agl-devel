DESCRIPTION = "AGL Container Demo Host image"

require agl-container-demo-host.inc

LICENSE = "MIT"

IMAGE_FEATURES_append = " \
    "

# add packages for container demo host here
IMAGE_INSTALL_append = " \
    packagegroup-agl-container-demo-host \
    "
