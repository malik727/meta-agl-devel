SUMMARY = "A small image just capable of allowing a device to boot."

IMAGE_INSTALL = " \
        packagegroup-core-boot \
        container-host-config \
        lxc \
        pipewire pipewire-alsa alsa-utils \
      "

#        packagegroup-agl-host-boot \
#

IMAGE_LINGUAS = " "

LICENSE = "MIT"

NO_RECOMMENDATIONS = "1"

inherit image

IMAGE_ROOTFS_SIZE ?= "8192"
IMAGE_ROOTFS_EXTRA_SPACE_append = "${@bb.utils.contains("DISTRO_FEATURES", "systemd", " + 4096", "" ,d)}"
