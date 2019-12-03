FILESEXTRAPATHS_prepend := "${THISDIR}/${BPN}:"

SRC_URI_remove = "file://core.cfg"
SRC_URI += "file://core-ivishell.cfg"

SRC_URI += "file://id-agent.cfg"
SRC_URI += "file://ivishell.cfg"

do_compile_rcar-gen3_append() {
    sed -e "/name=HDMI-A-2/{n; s/^/#/;}" \
        -i ${WORKDIR}/weston.ini
}
