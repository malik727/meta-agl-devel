FILESEXTRAPATHS_prepend := "${THISDIR}/${BPN}:"

SRC_URI += "file://core-ivishell.cfg"
SRC_URI += "file://id-agent.cfg"
SRC_URI += "file://ivishell.cfg"

WESTON_FRAGMENTS = "core-ivishell ivishell id-agent ${WESTON_DISPLAYS}"

do_compile_append_rcar-gen3() {
    sed -e "/name=HDMI-A-2/{n; s/^/#/;}" \
        -i ${WORKDIR}/weston.ini.default
}
