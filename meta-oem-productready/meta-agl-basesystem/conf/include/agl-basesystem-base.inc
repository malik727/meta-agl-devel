# AGL specific package configuration
#
# Add systemd configuration
DISTRO_FEATURES_append = " systemd"
#VIRTUAL-RUNTIME_init_manager = "systemd"

TOOLCHAIN_HOST_TASK_append += " nativesdk-os-rpclibrary-tool nativesdk-perl-module-app-cpan nativesdk-perl-module-json-pp"

# for agl-basefiles recipe
IMAGE_INSTALL_append += "\
    packagegroup-agl-basesystem \
"

