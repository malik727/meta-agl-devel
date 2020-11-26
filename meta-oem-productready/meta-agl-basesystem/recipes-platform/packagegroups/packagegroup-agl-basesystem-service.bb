DESCRIPTION = "Native Service Package Groups"
LICENSE = "Apache-2.0"

inherit packagegroup

PACKAGES = "\
        packagegroup-agl-basesystem-service \
        "

RDEPENDS_${PN} += " \
	ns-backupmanager \
	ns-commonlibrary \
	ns-frameworkunified \
	ns-loglibrary \
	os-eventlibrary \
	os-posixbasedos001legacylibrary \
	os-rpclibrary \
	ps-communication \
	ss-romaccesslibrary \
    "
