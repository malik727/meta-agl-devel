#FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

#SRC_URI_remove = "file://kingfisher_output.cfg"
#SRC_URI_append = " file://kingfisher_output_ON.cfg"

#do_configure_append() {
#    rm -f ${WORKDIR}/kingfisher_output.cfg
#}

do_install_append() {
    WESTON_INI_CONFIG=${sysconfdir}/xdg/weston
    sed -e "/name=HDMI-A-2/{n; s/^/#/;}" \
        -i ${D}/${WESTON_INI_CONFIG}/weston.ini
}
