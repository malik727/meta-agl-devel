# AGL specific package configuration
#
# Add systemd configuration

SHAREDIR = "${datadir}/basesystem"
INCLUDEDIR = "${includedir}/basesystem"
CONFDIR = "${sysconfdir}/basesystem"
LOCALDIR = "/var/local/lib/basesystem"

# BASESYSTEM_BRANCH = "${AGL_BRANCH}"
# BASESYSTEM_REVISION = "9e6613f8702df881526023403d33e342e6b428b6"

BASESYSTEM_BRANCH = "sandbox/Riku.Nomoto/test_20201219"
BASESYSTEM_REVISION = "ebd519faa3d6bfd62b4936db67bbcc3bab5e9a43"
