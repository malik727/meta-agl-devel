RDEPENDS_${PN} += "\
    wayland-ivi-extension \
    "

RDEPENDS_${PN} += "\
    ${@bb.utils.contains("DISTRO_FEATURES", "weston-remoting", \
    "gstreamer1.0-plugins-base-meta gstreamer1.0-plugins-good-meta", "",d)} \
    "
