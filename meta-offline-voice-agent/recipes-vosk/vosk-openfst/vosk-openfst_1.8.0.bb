LICENSE = "Unknown"
LIC_FILES_CHKSUM = "file://COPYING;md5=973381090441f4eb420224655e05e064"

SRC_URI = "git://github.com/alphacep/openfst.git;protocol=https;branch=master \
           file://0001-build-fixes-for-bitbake.patch \
           "

SRCREV = "7dfd808194105162f20084bb4d8e4ee4b65266d5"
S = "${WORKDIR}/git"

# NOTE: if this software is not capable of being built in a separate build directory
# from the source, you should replace autotools with autotools-brokensep in the
# inherit line
inherit autotools python3native

# Specify any options you want to pass to the configure script using EXTRA_OECONF:
EXTRA_OECONF = "--enable-static --enable-shared --enable-far --enable-ngram-fsts --enable-lookahead-fsts --with-pic --disable-bin"

FILES:${PN} += " /usr/lib/fst   /usr/lib/fst/arc_lookahead-fst.so \
  /usr/lib/fst/ilabel_lookahead-fst.so \
  /usr/lib/fst/ngram-fst.so \
  /usr/lib/fst/olabel_lookahead-fst.so \
"