OVERRIDES .= ":agl-container-guest"
DISTRO_FEATURES_append = " agl-container-guest"

# Because AGL UCB on R-Car3 should boot from SD card,
# tar.xz is preferred, wic and ext4 are not suitable to
# write contaner's rootfs.
IMAGE_FSTYPES_rcar-gen3_remove ="ext4 wic.xz wic.bmap wic.vmdk"
IMAGE_FSTYPES_rcar-gen3_append =" tar.xz"
