# AGL specific package configuration
#
# Add systemd configuration

SHAREDIR = "${datadir}/basesystem"
INCLUDEDIR = "${includedir}/basesystem"
CONFDIR = "${sysconfdir}/basesystem"
LOCALDIR = "/var/local/lib/basesystem"

BASESYSTEM_REVISION = "bae7619b752e23fe9b945bebcbeff9ede8973e66"
BASESYSTEM_BRANCH = "sandbox/Shuhei.Aketa/fixpositioning"

# for agl-basefiles recipe
IMAGE_INSTALL_append += "\
    packagegroup-agl-basesystem \
"
