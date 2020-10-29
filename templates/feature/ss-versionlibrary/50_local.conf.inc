DISTRO_FEATURES_append = " systemd ${DISTRO_FEATURES_LIBC}"
TOOLCHAIN_HOST_TASK_append += " nativesdk-os-rpclibrary-tool nativesdk-perl-module-app-cpan nativesdk-perl-module-json-pp" 

# add the static lib to SDK toolchain
SDKIMAGE_FEATURES_append += " staticdev-pkgs dev-pkgs tools-debug tools-profile headerfiles-pkgs nativesdk-os-rpclibrary"
SDKIMAGE_FEATURES_remove += " dbg-pkgs"
EXTRA_IMAGE_FEATURES_append += " staticdev-pkgs dev-pkgs dbg-pkgs tools-profile"

IMAGE_INSTALL_append += " ss-versionlibrary"
