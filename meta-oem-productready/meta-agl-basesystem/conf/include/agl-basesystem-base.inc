# AGL specific package configuration
#
# Add systemd configuration
DISTRO_FEATURES_append = " systemd ${DISTRO_FEATURES_LIBC}"
#VIRTUAL-RUNTIME_init_manager = "systemd"

TOOLCHAIN_HOST_TASK_append += " nativesdk-os-rpclibrary-tool nativesdk-perl-module-app-cpan nativesdk-perl-module-json-pp"

# add the static lib to SDK toolchain
SDKIMAGE_FEATURES_append += " staticdev-pkgs dev-pkgs tools-debug tools-profile headerfiles-pkgs nativesdk-os-rpclibrary-tool"
SDKIMAGE_FEATURES_remove += " dbg-pkgs"
EXTRA_IMAGE_FEATURES_append += " staticdev-pkgs dev-pkgs dbg-pkgs tools-profile"

# for agl-basefiles recipe
IMAGE_INSTALL_append += "\
    packagegroup-agl-basesystem \
"

