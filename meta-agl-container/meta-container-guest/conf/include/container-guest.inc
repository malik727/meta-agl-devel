OVERRIDES .= ":agl-container-guest"
DISTRO_FEATURES_append = " agl-container-guest"

# tar.xz is convinient to write rootfs to specific partition of sdcard
AGL_DEFAULT_IMAGE_FSTYPES_rcar-gen3 ="tar.xz"
