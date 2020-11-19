SUMMARY = "elfio for SystemManager"
DESCRIPTION = "install elfio to build SystemManager"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=4f932e9ddd12264ae5e569aae5f08ed3"

SRC_URI = "https://excellmedia.dl.sourceforge.net/project/elfio/ELFIO-sources/ELFIO-${PV}/${PN}-${PV}.tar.gz"
SRC_URI[md5sum] = "e1ddfc8d316fa6d03a04d8d1d6827663"

FILES_${PN}-dev = "${INCLUDEDIR}/elfio/*"
ALLOW_EMPTY_${PN} = "1"

do_patch[noexec] = "1"
do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}${INCLUDEDIR}/elfio/
	cp ${WORKDIR}/${PN}-${PV}/elfio/* ${D}${INCLUDEDIR}/elfio/
}
