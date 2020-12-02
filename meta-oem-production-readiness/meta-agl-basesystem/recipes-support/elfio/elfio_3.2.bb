SUMMARY = "C++ library for reading and generating ELF files"
DESCRIPTION = "ELFIO is a header-only C++ library intended for reading and generating files in the \
               ELF binary format. It is used as a standalone library - it is not dependent on any \
			   other product or project. Adhering to ISO C++, it compiles on a wide variety of \
			   architectures and compilers."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=4f932e9ddd12264ae5e569aae5f08ed3"

SRC_URI = "https://excellmedia.dl.sourceforge.net/project/elfio/ELFIO-sources/ELFIO-${PV}/${BPN}-${PV}.tar.gz"
SRC_URI[md5sum] = "e1ddfc8d316fa6d03a04d8d1d6827663"

do_patch[noexec] = "1"
do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}${includedir}/elfio/
	install -m 644 -D ${S}/elfio/* ${D}${includedir}/elfio/
}

sysroot_stage_all_append() {
	sysroot_stage_dir ${D}${includedir}/elfio ${SYSROOT_DESTDIR}${includedir}/elfio
}

FILES_${PN}-dev = " \
    ${includedir}/elfio/* \
"
