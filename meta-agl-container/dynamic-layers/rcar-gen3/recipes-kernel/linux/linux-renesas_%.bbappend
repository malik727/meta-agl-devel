# Workaround: Missing cfg/virtio.scc
#
# Remove cfg/virtio.scc from KERNEL_FEATURES added by meta-virtualization
# because rcar-gen3 bsp kernel, linux-renesas doesn't use yocto-kernel-cache
KERNEL_FEATURES_remove = " cfg/virtio.scc"
