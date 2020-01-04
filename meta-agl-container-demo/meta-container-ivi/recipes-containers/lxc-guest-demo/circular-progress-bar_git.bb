SUMMARY          = "Circular progressbar written in QML based on Canvas"
DESCRIPTION      = "Circular progressbar written in QML based on Canvas"
LICENSE          = "LGPL-3.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3000208d539ec061b899bce1d9ce9404"

SRC_URI = "git://github.com/cf47mn/circular-progressbar.git;protocol=https \
           file://qmldir \
          "
SRCREV = "4f7eefcbdacd2ff23448dd8a96ae790ee94b5dd8"

PV = "1.0+git${SRCPV}"
S = "${WORKDIR}/git"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    install -d ${D}${libdir}/qml/AGL/Demo/CircularProgressBar

    install -m 0644 ${WORKDIR}/git/CircularProgressBar.qml ${D}${libdir}/qml/AGL/Demo/CircularProgressBar/CircularProgressBar.qml
    install -m 0644 ${WORKDIR}/qmldir ${D}${libdir}/qml/AGL/Demo/CircularProgressBar/qmldir
}

FILES_${PN} += "${libdir}/qml/AGL/Demo/CircularProgressBar/"
