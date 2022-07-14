SUMMARY = "Offline open source speech recognition API based on Kaldi and Vosk"
HOMEPAGE = "https://github.com/alphacep/vosk-api"
AUTHOR = "aman.arora9848@gmail.com"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../COPYING;md5=d09bbd7a3746b6052fbd78b26a87396b"

SRC_URI = "git://github.com/alphacep/vosk-api;protocol=https;branch=master"

PV = "0.3.42+git${SRCPV}"
SRCREV = "b1b216d4c87d708935f1601287fe502aa11ee4a9"

S = "${WORKDIR}/git/src"


DEPENDS += " \
"

RDEPENDS_${PN} += " \
"