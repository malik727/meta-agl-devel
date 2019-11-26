# tar.gz is preferred, wic and ext4 are not suitable to setup guest rootfs to host
IMAGE_FSTYPES_remove ="ext4 wic.xz wic.bmap wic.vmdk"
IMAGE_FSTYPES_append =" tar.gz"
