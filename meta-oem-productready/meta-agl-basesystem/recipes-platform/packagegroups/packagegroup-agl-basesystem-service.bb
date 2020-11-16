DESCRIPTION = "Native Service Package Groups"
LICENSE = "Apache-2.0"

DEPENDS_qemux86-64 = "agl-basefiles"
DEPENDS_qemuarm64 = "agl-basefiles"

inherit packagegroup

PACKAGES = "\
        packagegroup-agl-basesystem-service \
        "
RDEPENDS_${PN} += " \
	agl-service-ns-backupmanager \
	agl-service-ns-notificationpersistent \
	agl-service-ps-communication \
	agl-service-ss-loggerservice \
	agl-service-ss-powerservice \
	agl-service-ss-resourcemanager \
	agl-service-ss-taskmanager \
	agl-service-vs-positioning \
	agl-service-ss-systemmanager \
	"

