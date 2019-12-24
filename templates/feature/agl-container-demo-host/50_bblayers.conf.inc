#
# meta-agl-demo should be included sllin driver, but
# others should NOT be included (by BBMASK).
#
BBLAYERS =+ " \
        ${METADIR}/meta-agl-demo \
        ${METADIR}/meta-agl-devel/meta-agl-container-demo/meta-container-host \
	"

BBMASK += "\
        meta-agl-demo/recipes-connectivity/* \
        meta-agl-demo/recipes-core/* \
        meta-agl-demo/recipes-demo-hmi/* \
        meta-agl-demo/recipes-devtools/* \
        meta-agl-demo/recipes-grahics/* \
        meta-agl-demo/recipes-multimedia/* \
        meta-agl-demo/recipes-navigation/* \
        meta-agl-demo/recipes-platform/* \
        meta-agl-demo/recipes-qt/* \
        meta-agl-demo/recipes-sdl/* \
        meta-agl-demo/recipes-support/* \
        "
