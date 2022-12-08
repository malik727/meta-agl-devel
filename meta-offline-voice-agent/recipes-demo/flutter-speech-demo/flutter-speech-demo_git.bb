SUMMARY = "Flutter Speech Recog"
DESCRIPTION = "A Flutter based Speech Recog Application for automotive grade Linux."

HOMEPAGE = "https://gerrit.automotivelinux.org/gerrit/apps/flutter-dashboard"

BUGTRACKER = "https://github.com/hritik-chouhan/dashboard_for_recipe/issues"

SECTION = "graphics"

#LICENSE = "Apache-2.0"
#LIC_FILES_CHKSUM = "file://License.md;md5=f712ede8d4f845976061925d1416fc40"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"


SRC_URI = "git://github.com/amanarora9848/voicerecognizer-gst-grpc;protocol=https;branch=flutter-grpc \
           "
PV = "0.1+git${SRCPV}"
SRCREV = "31b6c714db3be23165c5302507872e582e189bdb"
S = "${WORKDIR}/git/app"


inherit agl-app flutter-app

# flutter-app
#############
PUBSPEC_APPNAME = "speech_app"
FLUTTER_APPLICATION_INSTALL_PREFIX = "/flutter"
FLUTTER_BUILD_ARGS = "bundle -v"

# agl-app
#########
AGL_APP_TEMPLATE = "agl-app-flutter"
AGL_APP_ID = "speech_app"
AGL_APP_NAME = "Speech"

