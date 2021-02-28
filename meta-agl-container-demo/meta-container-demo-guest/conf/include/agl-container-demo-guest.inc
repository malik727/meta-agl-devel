require ${@bb.utils.contains('AGL_FEATURES', 'agl-demo-ivi', 'conf/include/agl-demo-ivi.inc', '', d)}
require ${@bb.utils.contains('AGL_FEATURES', 'agl-demo-ic', 'conf/include/agl-demo-ic.inc', '', d)}
