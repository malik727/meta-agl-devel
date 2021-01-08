FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"


SRC_URI += "file://0001-Don-t-try-to-include-gl3ext.h.patch \
            file://0002-Add-DRM-lease-support.patch"

PACKAGECONFIG += "drm-lease"
PACKAGECONFIG[drm-lease] = "-Ddrm_lease=enabled,-Ddrm_lease=disabled,drm-lease-manager"
