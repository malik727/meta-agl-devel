# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=95bbe2f9180443b5dcef3fb959804a65"

SRC_URI = "git://github.com/cktan/tomlc99;protocol=https;branch=master"

# Modify these as desired
PV = "1.0+git${SRCPV}"
SRCREV = "034b23ed3e4e5ee5345040eabed470f204d7f668"

S = "${WORKDIR}/git"

TARGET_CC_ARCH += "${LDFLAGS}"

# NOTE: this is a Makefile-only piece of software, so we cannot generate much of the
# recipe automatically - you will need to examine the Makefile yourself and ensure
# that the appropriate arguments are passed in.

do_configure () {
	# Specify any needed configure commands here
	:
}

do_compile () {
	# You will almost certainly need to add additional arguments here
	oe_runmake
}

do_install () {
        oe_runmake install prefix=${D}/${prefix}

        ln -rs ${D}/${prefix}/lib/libtoml.so.0.0 ${D}${prefix}/lib/libtoml.so

        sed 's:^prefix=.*:prefix=${prefix}:' ${S}/libtoml.pc.sample > libtoml.pc
        install -d ${D}${prefix}/lib/pkgconfig
        install libtoml.pc ${D}${prefix}/lib/pkgconfig/
}
