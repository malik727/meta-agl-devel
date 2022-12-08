SUMMARY = "Offline open source speech recognition API based on Kaldi and Vosk GRPC server"
HOMEPAGE = ""
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "git://github.com/amanarora9848/voicerecognizer-gst-grpc;protocol=https;branch=flutter-grpc \
           "

PV = "0.1+git${SRCPV}"
SRCREV = "31b6c714db3be23165c5302507872e582e189bdb"

S = "${WORKDIR}/git"

inherit setuptools3

DEPENDS += " \
    ${PYTHON_PN}-protobuf \
    ${PYTHON_PN}-grpcio \
"

RDEPENDS:${PN} += " \
    ${PYTHON_PN}-protobuf \
    ${PYTHON_PN}-grpcio \
    python3-vosk-api \
"

do_compile() {

}

do_install() {
    install -d ${D}/usr/local/speechservice/
    cp ${S}/*.py ${D}/usr/local/speechservice/
}

FILES:${PN} += "/usr/local/speechservice"
