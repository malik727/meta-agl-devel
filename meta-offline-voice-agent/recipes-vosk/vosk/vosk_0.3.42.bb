SUMMARY = "Offline open source speech recognition API based on Kaldi and Vosk"
HOMEPAGE = "https://github.com/alphacep/vosk-api"
AUTHOR = "aman.arora9848@gmail.com"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../COPYING;md5=d09bbd7a3746b6052fbd78b26a87396b"

SRC_URI = "git://github.com/alphacep/vosk-api;protocol=https;branch=master \
           file://0001-Build-fixes-for-shared-library-under-bitbake.patch \
           "

PV = "0.3.42+git${SRCPV}"
SRCREV = "b1b216d4c87d708935f1601287fe502aa11ee4a9"

S = "${WORKDIR}/git/src"


DEPENDS += " vosk-kaldi vosk-openfst openblas"

RDEPENDS_${PN} += " \
"

CFLAGS:append = " -I${STAGING_INCDIR}/kaldi -g "
LDFLAGS:remove = "-Wl,--as-needed"

do_configure(){
:
}

do_compile(){
make KALDI_ROOT=${STAGING_INCDIR}/kaldi/ OPENFST_ROOT=${STAGING_INCDIR} OPENBLAS_ROOT=${STAGING_INCDIR} USE_SHARED=1 EXTRA_CFLAGS="${CFLAGS}" EXTRA_LDFLAGS="${LDFLAGS}" ${PARALLEL_MAKE}

}

do_install(){

    install -d ${D}${libdir}
    install -m 0644 libvosk.so.0.3.42 ${D}${libdir}
    cd ${D}${libdir}
    ln -sf libvosk.so.0.3.42 libvosk.so
    cd ${S}

    install -d ${D}${includedir}/vosk
    for i in *.h ; do
	install -m 0644 $i ${D}${includedir}/vosk/
    done
}

#ERROR_QA:remove = "already-stripped"
ERROR_QA:remove = "dev-deps"
