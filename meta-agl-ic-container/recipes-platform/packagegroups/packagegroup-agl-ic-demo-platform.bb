SUMMARY = "The software for DEMO platform of AGL IVI profile"
DESCRIPTION = "A set of packages belong to AGL Demo Platform"

LICENSE = "MIT"

inherit packagegroup

PROVIDES = "${PACKAGES}"
PACKAGES = "\
    packagegroup-agl-ic-demo-platform \
    "

TTF_FONTS = " \
    ttf-bitstream-vera \
    ttf-dejavu-sans \
    ttf-dejavu-sans-mono \
    ttf-dejavu-serif \
    ttf-noto-emoji-color \
    source-han-sans-cn-fonts \
    source-han-sans-jp-fonts \
    source-han-sans-tw-fonts \
    source-han-sans-kr-fonts \
    "

AGL_APPS = " \
    "

RDEPENDS:${PN} += " \
    udisks2 \
    linux-firmware-ath9k \
    linux-firmware-ralink \
    can-utils \
    cannelloni \
    iproute2 \
    ${TTF_FONTS} \
    weston-ini-conf-no-activate \
    ${@bb.utils.contains('DISTRO_FEATURES', 'agl-devel', 'unzip' , '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'webruntime', 'virtual/webruntime', '', d)} \
    ${AGL_APPS} \
    "
