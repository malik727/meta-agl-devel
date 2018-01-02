FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = " \
    0001-CES2018-Enable-to-execute-chromium-as-WebBrowser.patch \
"

inherit aglwgt

do_install () {
    install -d ${D}/usr/bin/
    install -m 755 ${WORKDIR}/build/runxdg ${D}/usr/bin/
}

do_compile_append() {
 make widget

    rm ${B}/package/video.wgt
    rm ${B}/package/hvac.wgt
    rm ${B}/package/navi.wgt
    rm ${B}/package/simple-egl.wgt

}
