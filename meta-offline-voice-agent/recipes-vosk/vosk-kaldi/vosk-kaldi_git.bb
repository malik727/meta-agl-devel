# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
#
# The following license files were not able to be identified and are
# represented as "Unknown" below, you will need to check them yourself:
#   COPYING
#   src/doc/legal.dox
LICENSE = "Unknown"
LIC_FILES_CHKSUM = "file://../COPYING;md5=a10e448a64dbd3723ff3fb2f397fba2e \
                    file://doc/legal.dox;md5=3cba845003f27e67da70faa5da924c1e"

SRC_URI = "git://github.com/alphacep/kaldi.git;protocol=https;branch=vosk \
           file://0001-Fixes-for-shared-library-compilation.patch \
           "
#           file://0001-Enforce-cross-compilation-under-bitbake.patch \
#           file://0001-Build-fix-for-include-in-makefile.patch \
#
# Modify these as desired
PV = "1.0+git${SRCPV}"
SRCREV = "76cd51d44c0a61e3905c35cadb2ec5f54f3e42d1"

S = "${WORKDIR}/git/src"

# NOTE: unable to map the following CMake package dependencies: CUB LAPACK  BLAS
DEPENDS += "openblas vosk-openfst"
inherit python3native

# Specify any options you want to pass to cmake using EXTRA_OECMAKE:
MYCONF = "--mathlib=OPENBLAS --static --shared --use-cuda=no --fst-root=${STAGING_INCDIR}/../ --fst-version=1.8.0 --openblas-root=${STAGING_INCDIR}/../ "

do_configure(){

  ./configure ${MYCONF}

}

do_compile(){

  make ${PARALLEL_MAKE}

}

do_install(){

  install -d ${D}${libdir}

  for i in lib/*.so ; do
    install -m 0644 ${i} ${D}${libdir}/
  done

  for i in */*.a ; do
    install -m 0644 ${i} ${D}${libdir}/
  done

  for j in base chain decoder feat fstext gmm gst-plugin hmm itf ivector kws lat lm matrix nnet nnet2 nnet3 online online2 rnnlm sgmm2 tfrnnlm transform tree util cudadecoder  cudadecoderbin  cudafeat  cudamatrix ; do
    install -d ${D}${includedir}/kaldi/$j
    for i in $j/*.h ; do 
      install -m 0644 $i ${D}${includedir}/kaldi/$j/
    done
  done

}

ERROR_QA:remove = "rpaths"
ERROR_QA:remove = "dev-elf"

