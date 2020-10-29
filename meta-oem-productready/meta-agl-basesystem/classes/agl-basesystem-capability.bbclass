pkg_postinst_ontarget_${PN}_append () {
    CAPVARS="${CAPABILITY}"
    IFS=" "
    for cap in ${CAPVARS}; do
        capability=`echo ${cap} | cut -f 1 -d ":"`
        file=`echo ${cap} | cut -f 2 -d ":"`
        setcap ${capability} $D${file}

	df -T / | grep nfs > /dev/null
	IS_EMMC_BOOT=$?
	if [ $IS_EMMC_BOOT -eq 0 ]; then
		TCAP_NAME="/tmp/${file##*/}"
		if [ ! -L ${file} ]; then
		        cp -a ${file} ${TCAP_NAME}
		        mv ${file} ${file}.org
		        ln -fs ${TCAP_NAME} ${file}
		else
		        cp -a ${file}.org ${TCAP_NAME}
		fi
		setcap ${capability} ${TCAP_NAME}
	fi
     done
}
#RDEPENDS_${PN} += "libcap-bin"
PACKAGE_WRITE_DEPS = "libcap-native coreutils-native"
