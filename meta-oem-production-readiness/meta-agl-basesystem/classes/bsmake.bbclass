#pokyのbase.bbclassではMakefile, makefile, GNUmakefile 以外のMakefileのため定義が必要
# そのため、独自のdo_compileが必要
bsmake_do_compile (){
    oe_runmake -f ${BSMAKE_FILE}
}

# pokyのbase_do_installは空なので定義が必要
bsmake_do_install (){
    oe_runmake  -f ${BSMAKE_FILE} DESTDIR=${D} install
}

EXPORT_FUNCTIONS do_compile do_install
