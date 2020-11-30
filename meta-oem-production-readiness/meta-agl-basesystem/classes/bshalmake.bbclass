#pokyのbase.bbclassではMakefile, makefile, GNUmakefile 以外のMakefileのため定義が必要
# そのため、独自のdo_compileが必要

# pokyのbase_do_installは空なので定義が必要
bshalmake_do_install (){
    oe_runmake install
    
    install -d ${D}${includedir}/basesystem
    install -D -m 644 ${S}/hal_api/*.h ${D}${includedir}/basesystem

}

EXPORT_FUNCTIONS do_install
