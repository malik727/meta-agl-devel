# AGL specific package configuration
#
# Add systemd configuration

SHAREDIR = "${datadir}/basesystem"
INCLUDEDIR = "${includedir}/basesystem"
CONFDIR = "${sysconfdir}/basesystem"
LOCALDIR = "/var/local/lib/basesystem"

# BASESYSTEM_BRANCH = "${AGL_BRANCH}"
# BASESYSTEM_REVISION = "9e6613f8702df881526023403d33e342e6b428b6"

BASESYSTEM_BRANCH = "sandbox/Riku.Nomoto/test_20201220"
BASESYSTEM_REVISION = "fa48c740028faab4ba12e4ad19f5837bda9ec28c"
