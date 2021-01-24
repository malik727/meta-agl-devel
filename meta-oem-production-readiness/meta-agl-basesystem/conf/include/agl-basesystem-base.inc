# AGL specific package configuration
#
# Add systemd configuration

SHAREDIR = "${datadir}/basesystem"
INCLUDEDIR = "${includedir}/basesystem"
CONFDIR = "${sysconfdir}/basesystem"
LOCALDIR = "/var/local/lib/basesystem"

BASESYSTEM_REVISION = "e9c50e0578cd045617f898e01cb51ec05ec7b014"
BASESYSTEM_BRANCH = "sandbox/Shuhei.Aketa/libev"

# for agl-basefiles recipe
IMAGE_INSTALL_append += "\
    packagegroup-agl-basesystem \
"
