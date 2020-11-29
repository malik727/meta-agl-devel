SUMMARY = "agl-service-ns-backupmanager for AGL software"
DESCRIPTION = "agl-service-ns-backupmanager to build AGL software"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2ee41112a44fe7014dce33e26468ba93"
DEPENDS += " \
    libxml2-native \
    ns-frameworkunified \
    libnv-hal \
    ns-backupmanager \
    ss-interfaceunified \
    ss-romaccesslibrary \
    os-vehicleparameterlibrary \
"

PV = "1.0.0+gitr${SRCPV}"
SRC_URI = "git://gerrit.automotivelinux.org/gerrit/staging/basesystem.git;protocol=https;subpath=service/native;branch=${AGL_BRANCH}"
SRCREV := "${BASESYSTEM_REVISION}"

S = "${WORKDIR}/native/backup_manager"

inherit agl-basesystem-common

EXTRA_MAKEFILE = " -f Makefile.server"
EXTRA_OEMAKE += "${EXTRA_MAKEFILE}"

RDEPENDS_${PN} += " \
    ns-frameworkunified \
    libnv-hal \
    ns-backupmanager \
    ss-interfaceunified \
    ss-romaccesslibrary \
    os-vehicleparameterlibrary \
"

CAPABILITY = "cap_dac_override+ep:/usr/bin/NS_BackupMgr"
