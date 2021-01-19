# AGL specific package configuration
#
# Add systemd configuration

SHAREDIR = "${datadir}/basesystem"
INCLUDEDIR = "${includedir}/basesystem"
CONFDIR = "${sysconfdir}/basesystem"
LOCALDIR = "/var/local/lib/basesystem"

BASESYSTEM_REVISION = "71afcd09b0f210e7da5ae6adc1b914fa02d412ff"
BASESYSTEM_BRANCH = "master"

# for agl-basefiles recipe
IMAGE_INSTALL_append += "\
    packagegroup-agl-basesystem \
"
