# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
#
# The following license files were not able to be identified and are
# represented as "Unknown" below, you will need to check them yourself:
#   COPYING
LICENSE = "Unknown"
LIC_FILES_CHKSUM = "file://COPYING;md5=d09bbd7a3746b6052fbd78b26a87396b"

SRC_URI = "git://github.com/alphacep/vosk-server;protocol=https;branch=master"

# Modify these as desired
PV = "1.0+git${SRCPV}"
SRCREV = "70f3d5321a40f2f5dffe9c833bc1fac4b3b451e7"

S = "${WORKDIR}/git"

DEPENDS = "python3-vosk-api openblas vosk boost"

do_configure () {
	# Specify any needed configure commands here
	:
}

do_compile () {
	# websocket-cpp
	cd websocket-cpp
	${CXX} -I${STAGING_INCDIR}/vosk -lvosk ${LDFLAGS} -o vosk-websocket-cpp asr_server.cpp
}

do_install () {
	# websocket-cpp
	install -d ${D}${bindir}
	cp websocket-cpp/vosk-websocket-cpp ${D}${bindir}
}

