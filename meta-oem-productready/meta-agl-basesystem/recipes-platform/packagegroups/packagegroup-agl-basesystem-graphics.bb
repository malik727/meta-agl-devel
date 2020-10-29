DESCRIPTION = "Native Service Package Groups"
LICENSE = "Apache-2.0"

DEPENDS_qemux86-64 = "agl-basefiles"
DEPENDS_qemuarm64 = "agl-basefiles"

inherit packagegroup

PACKAGES = "\
        packagegroup-agl-basesystem-graphics \
        "
RDEPENDS_${PN} += " \
	ns-commonlibrary \
	ns-loglibrary \
	ns-frameworkunified \
	ns-backupmanager \
	os-eventlibrary \
	os-posixbasedos001legacylibrary \
	os-vehicleparameterlibrary \
	os-rpclibrary \
	ps-communication \
	ss-versionlibrary \
	ss-romaccesslibrary \
	ss-config \
	ss-interfaceunified \
	ss-resourcemanager \
	ss-taskmanager \
	vs-positioning \
	vs-positioningbaselibrary \
"

