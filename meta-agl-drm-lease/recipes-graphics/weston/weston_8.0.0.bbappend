FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://0001-backend-drm-Add-method-to-bypass-libudev-enumeration.patch \
            file://0002-libweston-Add-DRM-lease-launcher-backend.patch \
            file://0003-Add-DRM-lease-option.patch \
            "

PACKAGECONFIG[drm-lease] = "-Ddrm-lease=true,-Ddrm-lease=false,drm-lease-manager"
PACKAGECONFIG_append = " drm-lease"
