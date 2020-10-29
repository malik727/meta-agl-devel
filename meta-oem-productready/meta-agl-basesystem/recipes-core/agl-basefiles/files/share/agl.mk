#
# @copyright Copyright (c) 2016-2019 TOYOTA MOTOR CORPORATION.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#################################################################################
#
# MAKE VARIABLES
#
# (mandatory)
#   MAKETOP        : pprosrc/root directory
#
# (optional)
#   COMPONENT_NAME : component name
#   INST_HEADERS   : headers to install
#   INST_LIBS      : libraries to install
#   INST_SHLIBS    : shared libraries to install
#   NOINST_LIBS    : libraries for local use
#   INST_PROGS     : programs to install
#   INST_CONFBIN   : conf_bin to install
#   RPC_API        : RPC API definitions (without suffix)
#   IPC_API        : IPC API definitions (without suffix)
#   xxx_SRCS       : source files of program xxx (*.{c,S,cc})
#   libxxx_SRCS    : source files of library libxxx (*.{c,S,cc})
#   xxx_PCOS       : pre-compiled object files of program xxx (*.{o,os,a})
#   libxxx_PCOS    : pre-compiled object files of library libxxx (*.{o,os,a})
#   SUBDIRS        : sub directories
#   CLEAN_FILES    : extra files to clean
#   CLEAN_DIRS     : extra directoies to clean
#   UNINST_FILES   : extra files to uninstall
#   CPPFLAGS       : preprocess options (-I, -D, ...)
#   CFLAGS         : C source compile options
#   CXXFLAGS       : C++ source compile options
#   ASFLAGS        : assembler source assemble options
#   LDFLAGS        : link options (-L, ...)
#   LDLIBS         : libraries to link (-lxxx)
#   ALL            : targets to make
#                    (default: install-header install-lib install-prog install-data)
#   xxx_SONAME     : dummy library SONAME
#
# MAKE TARGETS
#
#   all, test                   : for target in $(ALL); do $(MAKE) $$target; done
#   install-prog		: install program
#   install-lib			: install-shlib and intall-arlib
#   install-shlib		: install shared libraries
#   install-arlib		: install static libraries
#   install-test-mock-lib	: install mock libraries
#   install-test-mock-shlib	: install shared mock libraries
#   install-test-mock-arlib	: install static mock libraries
#   clean, clean-test           : clean temporary files
#   clean-all, clean-all-test   : clean temporary files and installed files
#   clean-self, clean-self-test : non-recursive clean
#################################################################################


ifneq ($(ADD_EXT),)
  AEXT=.$(ADD_EXT)
endif


ifneq ($(strip $(filter $(MAKECMDGOALS),\
	lint \
	)),)
endif

ifneq ($(strip $(filter $(MAKECMDGOALS),\
	)),)
endif


#################################################################################
SYSROOT ?= $(SDKTARGETSYSROOT)
DESTDIR ?= $(SDKTARGETSYSROOT)

WARN_FLAGS ?= -Wall
DEBUG_FLAGS ?= -g

AUTO_INCLUDE := -include $(SYSROOT)/usr/agl/include/agl_types_obsoluted.h
AGLCFLAGS := $(CFLAGS) $(COMPONENT_CFLAGS)
AGLCXXFLAGS := $(CXXFLAGS) $(COMPONENT_CXXFLAGS)
AGLCPPFLAGS := $(CPPFLAGS) $(COMPONENT_CPPFLAGS)
AGLASFLAGS :=  $(ASFLAGS)
AGLLDFLAGS := $(LDFLAGS) $(COMPONENT_LDFLAGS)
AGLLDLIBS := $(LDLIBS) $(COMPONENT_LDLIBS)
AGLARFLAGS := $(ARFLAGS)
AGLPICFLAGS := -fPIC

AGLCFLAGS += $(WARN_FLAGS) $(DEBUG_FLAGS) $(AUTO_INCLUDE)
AGLCXXFLAGS += $(WARN_FLAGS) $(DEBUG_FLAGS) $(AUTO_INCLUDE)
AGLASFLAGS += $(WARN_FLAGS) $(ARCH_FLAGS)


ifdef LINK_CXX
LINK := $(CXX)
else
LINK := $(CC)
endif

ifdef LINK_SHLIB_CXX
LINK_SHLIB := $(CXX)
else
LINK_SHLIB := $(CC)
endif

ifdef DUMMY_SHLIB
AGLLDFLAGS += -L.
endif

######### add gcov option ############



define LINK_DUMMY
if [ "$1" != "$3" ]; then \
	echo "dummy lib ($1) created" ; \
	$(LINK_SHLIB) -shared $(PIC_FLAGS) -Wl,-soname=$2 -o $1 -xc /dev/null ; \
else \
	echo "error: dummy lib must not have the same name as $3" ; \
	exit 1 ; \
fi ;
endef

define INST_DUMMY
	@$(foreach lib,$(DUMMY_SHLIB),$(if $(lib),$(call LINK_DUMMY,$(lib),$(if $($(lib)_SONAME),$($(lib)_SONAME),$(lib)),$1)))
endef

define CLEAN_DUMMY
	@$(foreach lib,$(DUMMY_SHLIB),$(if $(lib),rm -f $(lib)))
endef

define INSTALL_EXT
@if [ "$(AEXT)" != "" ];then \
  if echo "$(ADD_EXT)" | grep -q '^[A-Za-z]' ;then \
    echo "$< -> $<$(AEXT)" ;\
    mv $< $<$(AEXT) ;\
    install -c -m 0755 $<$(AEXT) $@$(AEXT) ;\
    if [ -f "$*.map" ];then \
      mv $*.map $*.map$(AEXT) ;\
    fi ;\
  else \
    echo "ADD_EXT : ERROR $(ADD_EXT)" ;\
    exit 1 ;\
  fi ;\
fi
endef


define INSTALL_SCRIPT
install -d -m 0755 $(@D)
install -c -m 0755 $< $@
endef

define INSTALL_PIXMAP
install -d -m 0755 $(@D)
install -c -m 0644 $< $@
endef

define INSTALL_UCODE
install -d -m 0755 $(@D)
install -c -m 0644 $< $@
endef

define INSTALL_DATAINITOBJ
if [ -n "$<" ]; then\
 install -d -m 0755 $(@D);\
 install -c -m 0644 $< $@;\
fi;
endef

define INSTALL_OBJ
install -d -m 0755 $(@D)
install -c -m 0644 $< $@
endef

define INSTALL_CONFBIN
if [ -n "$<" ]; then\
 install -d -m 0755 $(@D);\
 install -c -m 0644 $< $@;\
fi;
endef

#################################################################################


## for libc ##
AGLCPPFLAGS += -D_GNU_SOURCE

## for libPosixBased001Legacy 
AGLCPPFLAGS += -DAGL_PosixBasedOS001LEGACY_USED -DAGL_STUB -DLINUX

## for agl header##
AGLCPPFLAGS += -I$(SYSROOT)/usr/agl/include

## for agl library##
AGLLDFLAGS += -L$(SYSROOT)/usr/agl/lib

ifneq ($(INST_SHLIBS),libagl_stub)
AGLLDLIBS += -Wl,-Bdynamic -lpthread
endif


##########################################

COMPONENT_NAME ?= $(error COMPONENT_NAME is not defined)
AGL_TOPDIR ?= $(DESTDIR)/usr/agl
AGL_INCDIR := $(AGL_TOPDIR)/include
AGL_LIBDIR := $(AGL_TOPDIR)/lib
AGL_BINDIR := $(AGL_TOPDIR)/bin
AGL_PIXMAPDIR := $(AGL_TOPDIR)/pixmaps
AGL_UCODEDIR := $(AGL_TOPDIR)/data/ucode

#################################################################################

HEADER_INSTALL_DIR := $(AGL_INCDIR)/$(COMPONENT_NAME)
LIB_INSTALL_DIR := $(AGL_LIBDIR)
PROG_INSTALL_DIR := $(AGL_BINDIR)
PIXMAP_INSTALL_DIR := $(AGL_PIXMAPDIR)/$(COMPONENT_NAME)
UCODE_INSTALL_DIR := $(AGL_UCODEDIR)
DATAINITOBJ_INSTALL_DIR := $(AGL_DATAINITOBJDIR)
CONFBIN_INSTALL_DIR := $(AGL_CONFBINDIR)

#################################################################################

DEL_OBJS = $(filter %.o,$($(1)_SRCS:%.c=%.o) $($(1)_SRCS:%.cc=%.o) \
 $($(1)_SRCS:%.cpp=%.o) \
 $($(1)_SRCS:%.S=%.o))
OBJS = $(DEL_OBJS) $($(1)_PCOS)
DEL_SOBJS = $(filter %.os,$($(1)_SRCS:%.c=%.os) $($(1)_SRCS:%.cc=%.os) \
 $($(1)_SRCS:%.cpp=%.os) \
 $($(1)_SRCS:%.S=%.os))
DEL_GCDA = $(filter %.gcda,$($(1)_SRCS:%.c=%.gcda) $($(1)_SRCS:%.cc=%.gcda) \
 $($(1)_SRCS:%.cpp=%.gcda) \
 $($(1)_SRCS:%.S=%.gcda))
DEL_GCNO = $(filter %.gcno,$($(1)_SRCS:%.c=%.gcno) $($(1)_SRCS:%.cc=%.gcno) \
 $($(1)_SRCS:%.cpp=%.gcno) \
 $($(1)_SRCS:%.S=%.gcno))
DEL_GCOV = $(filter %.gcov,$($(1)_SRCS:%.c=%.gcov) $($(1)_SRCS:%.cc=%.gcov) \
 $($(1)_SRCS:%.cpp=%.gcov) \
 $($(1)_SRCS:%.S=%.gcov))

DEL_INFO = $(filter %.info, \
 $(dirname $($(1)_SRCS:%.c=%.tmp))lcov.info \
 $(dirname $($(1)_SRCS:%.cc=%.tmp))lcov.info \
 $(dirname $($(1)_SRCS:%.cpp=%.tmp))lcov.info \
 $(dirname $($(1)_SRCS:%.S=%.tmp))lcov.info)

SOBJS = $(DEL_SOBJS) $($(1)_PCOS)
DEPS = $(join $(dir $(DEL_OBJS)),$(patsubst %.o,.%.d,$(notdir $(DEL_OBJS))))

INST_TEST_MOCK_LIBS := 
INST_TEST_MOCK_SHLIBS := 
INST_ITV2_TESTPROGS := 
INST_TESTPROGS := 

CLEAN_OBJS := $(foreach lib,$(INST_LIBS) $(INST_SHLIBS) $(INST_TEST_MOCK_LIBS) $(INST_TEST_MOCK_SHLIBS) $(NOINST_LIBS) $(INST_PROGS) $(INST_ITV2_TESTPROGS) $(INST_TESTPROGS),$(call DEL_OBJS,$(lib)))
CLEAN_SOBJS := $(foreach lib,$(INST_SHLIBS) $(INST_TEST_MOCK_SHLIBS),$(call DEL_SOBJS,$(lib)))

CLEAN_GCDA := $(foreach lib,$(INST_LIBS) $(INST_SHLIBS) $(NOINST_LIBS) $(INST_PROGS) $(INST_ITV2_TESTPROGS) $(INST_TESTPROGS),$(call DEL_GCDA,$(lib)))
CLEAN_GCNO := $(foreach lib,$(INST_LIBS) $(INST_SHLIBS) $(NOINST_LIBS) $(INST_PROGS) $(INST_ITV2_TESTPROGS) $(INST_TESTPROGS),$(call DEL_GCNO,$(lib)))
CLEAN_GCOV := $(foreach lib,$(INST_LIBS) $(INST_SHLIBS) $(NOINST_LIBS) $(INST_PROGS) $(INST_ITV2_TESTPROGS) $(INST_TESTPROGS),$(call DEL_GCOV,$(lib)))
CLEAN_CFG  := $(INST_UT_SMCONF:%=%.cfg) $(INST_IT_SMCONF:%=%.cfg)

CLEAN_INFO := $(sort $(foreach lib,$(INST_LIBS) $(INST_SHLIBS) $(INST_TEST_MOCK_LIBS) $(INST_TEST_MOCK_SHLIBS) $(NOINST_LIBS) $(INST_PROGS) $(INST_ITV2_TESTPROGS) $(INST_TESTPROGS),$(call DEL_INFO,$(lib))))

LIB_DEPS := $(foreach lib,$(INST_LIBS) $(INST_SHLIBS) $(INST_TEST_MOCK_LIBS) $(INST_TEST_MOCK_SHLIBS) $(NOINST_LIBS),$(call DEPS,$(lib)))
PROG_DEPS := $(foreach prog,$(INST_PROGS),$(call DEPS,$(prog)))
TESTPROGS_DEPS := 
PROG_RULES := $(foreach prog,$(INST_PROGS),$(if $(prog),.$(prog).out.rule))
TESTPROG_RULES := 

LIB_RULES := $(foreach lib,$(INST_LIBS) $(INST_SHLIBS) $(NOINST_LIBS) $(INST_TEST_MOCK_LIBS),$(if $($(lib)_SRCS),.$(lib).a.rule))
SHLIB_RULES := $(foreach lib,$(INST_SHLIBS) $(INST_TEST_MOCK_SHLIBS),$(if $(lib),.$(lib).so.rule))
ARLIB_RULES := $(foreach lib,$(INST_LIBS) $(NOINST_LIBS),$(if $($(lib)_SRCS),.$(lib).a.rule))

PROG_MAPS := $(foreach prog,$(INST_PROGS),$(if $(prog),$(prog).map))
TESTPROG_MAPS := $(foreach prog,$(INST_ITV2_TESTPROGS) $(INST_TESTPROGS),$(if $(prog),$(prog).map))
LIB_MAPS := $(foreach lib,$(INST_LIBS) $(INST_SHLIBS) $(NOINST_LIBS) $(INST_TEST_MOCK_LIBS) $(INST_TEST_MOCK_SHLIBS),$(if $(lib),$(lib).map))
PROG_LIBDEPS := $(foreach prog,$(INST_PROGS),$(if $(prog),.$(prog).out.libdep))
TESTPROG_LIBDEPS := $(foreach prog,$(INST_ITV2_TESTPROGS) $(INST_TESTPROGS),$(if $(prog),.$(prog).out.libdep))

BUILD_MK_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(BUILD_MK_DIR)/rpc_rule.mk

IPC_API_RULES := $(IPC_API:%=.%.ipc.rule)
ipc_api := $(shell echo $(IPC_API) | tr A-Z a-z)
CLEAN_IPC_API_SRCS := $(ipc_api:%=%_client.h) $(ipc_api:%=%_client.c) $(ipc_api:%=%_server.h) $(ipc_api:%=%_server.c)
IPC_API_DEPS := $(ipc_api:%=%_client.d) $(ipc_api:%=%_server.d)

CLEAN_PROGS := $(foreach prog,$(INST_PROGS),$(if $(prog),$(prog).out))
CLEAN_TESTPROGS := $(foreach prog,$(INST_ITV2_TESTPROGS) $(INST_TESTPROGS),$(if $(prog),$(prog).out))

ifneq ($(AEXT),)
CLEAN_PROGS += $(foreach prog,$(INST_PROGS),$(if $(prog),$(prog).out$(AEXT)))
CLEAN_TESTPROGS += $(foreach prog,$(INST_ITV2_TESTPROGS) $(INST_TESTPROGS),$(if $(prog),$(prog).out$(AEXT)))
endif
CLEAN_LIBS := $(foreach lib,$(INST_LIBS) $(INST_SHLIBS) $(INST_TEST_MOCK_LIBS) $(INST_TEST_MOCK_SHLIBS) $(NOINST_LIBS),$(if $($(lib)_SRCS),$(lib).a))
CLEAN_SHLIBS := $(foreach lib,$(INST_SHLIBS) $(INST_TEST_MOCK_SHLIBS),$(if $(lib),$(lib).so))
ifneq ($(AEXT),)
CLEAN_SHLIBS += $(foreach lib,$(INST_SHLIBS) $(INST_TEST_MOCK_SHLIBS),$(if $(lib),$(lib).so$(AEXT)))
endif
ifneq ($(DUMMY_SHLIB),)
CLEAN_SHLIBS += $(DUMMY_SHLIB)
endif

CLEAN_FILES += $(CLEAN_OBJS) $(CLEAN_SOBJS)
CLEAN_FILES += $(PROG_DEPS) $(LIB_DEPS) $(TESTPROG_DEPS)
CLEAN_FILES += $(PROG_MAPS) $(PROG_LIBDEPS) $(TESTPROG_MAPS) $(TESTPROG_LIBDEPS)
CLEAN_FILES += $(PROG_RULES) $(LIB_RULES) $(SHLIB_RULES) $(AR_RULES) $(TESTPROG_RULES)
CLEAN_FILES += $(CLEAN_PROGS) $(CLEAN_LIBS) $(CLEAN_SHLIBS) $(LIB_MAPS) $(CLEAN_TESTPROGS)
CLEAN_FILES += $(RPC_API_RULES) $(CLEAN_API_SRCS) $(RPC_API_DEPS)
CLEAN_FILES += $(IPC_API_RULES) $(CLEAN_IPC_API_SRCS) $(IPC_API_DEPS)
CLEAN_FILES += $(INST_DATAINITOBJ)
CLEAN_FILES += $(CLEAN_INFO)
CLEAN_FILES += $(CLEAN_GCNO) $(CLEAN_GCDA) $(CLEAN_GCOV)
CLEAN_FILES += $(CLEAN_CFG)
ifneq ($(AEXT),)
CLEAN_FILES += $(foreach lib,$(INST_SHLIBS) $(INST_PROGS),$(if $(lib),$(lib).map$(AEXT)))
endif


#################################################################################

RPATHLINK := $(SYSROOT)/usr/lib:$(SYSROOT)/lib:$(SYSROOT)/usr/agl/lib

#################################################################################
SUBDIRS := $(filter-out mock,$(SUBDIRS))

.PHONY: all all-subdirs install test $(SUBDIRS:%=all-%) $(SUBDIRS:%=install--%)
.PHONY: install-test $(SUBDIRS:%=install-test-%)
.PHONY: build-lib
.PHONY: build-prog $(SUBDIRS:%=build-prog-%)
.PHONY: build-shlib $(SUBDIRS:%=build-shlib-%)
.PHONY: build-arlib $(SUBDIRS:%=build-arlib-%)
.PHONY: build-cfg
.PHONY: install-header $(SUBDIRS:%=install-header-%)
.PHONY: install-lib
.PHONY: install-shlib $(SUBDIRS:%=install-shlib-%)
.PHONY: install-arlib $(SUBDIRS:%=install-arlib-%)
.PHONY: install-prog $(SUBDIRS:%=install-prog-%)
.PHONY: install-data $(SUBDIRS:%=install-data-%)
.PHONY: install-cfg $(SUBDIRS:%=install-cfg-%)
.PHONY: install-preload 
.PHONY: clean-all
.PHONY: clean-self
.PHONY: clean-sub $(SUBDIRS:%=clean-%)
.PHONY: clean-all-sub $(SUBDIRS:%=clean-all-%)
.PHONY: clean-self-sub
.PHONY: lint lint-exec


REF_ROOT_DIR=/home/ref_root/
TEST_SERVER_DIR=/home/agl_sysroot/
REFHW_SERVER=192.168.1.2

PHONY: all

lint:
	@set -e;\
	$(MAKE) lint-exec


#all: build-lib build-prog build-test-mock-lib build-cfg all-subdirs
all: build-lib build-prog build-cfg all-subdirs

all-subdirs:
	@set -e;\
	for dir in $(SUBDIRS); do (cd $$dir; $(MAKE) all); done


#lint-exec: $(INST_HEADERS) $($(INST_SHLIBS)_SRCS) $($(INST_LIBS)_SRCS) $($(INST_PROGS)_SRCS)
#	-cpplint.py $^ > cpplint_result.txt 2>&1

lint-exec:
	$(eval LINTFILES := $(shell find . -name "*.c*" -o -name "*.h*"))
	-cpplint.py --extensions=hpp,cpp,c,cc,h $(LINTFILES) > cpplint_result.txt 2>&1


#install: install-header install-lib install-prog install-data install-test-mock-header install-test-mock-lib install-test-casename $(SUBDIRS:%=install--%)
install: install-header install-lib install-prog install-data $(SUBDIRS:%=install--%)


build-lib: build-shlib build-arlib

build-shlib: $(INST_SHLIBS:%=%.so)

build-arlib: $(INST_LIBS:%=%.a) $(NOINST_LIBS:%=%.a)

TOPDIR=$(abspath ./)
generate-header-list: install-header-local
	echo $(COMPONENT_NAME) > $(addsuffix .list, $(abspath ./))
	ls -1 $(TOPDIR)/tmp_head/usr/agl/include/$(COMPONENT_NAME)/ >> $(addsuffix .list, $(abspath ./))
	rm -rf ./tmp_head
	

build-prog: $(INST_PROGS:%=%.out)


install-lib: install-arlib install-shlib

install-arlib: build-arlib
ifneq ($(strip $(INST_LIBS)),)
	install -m 0755 -d $(LIB_INSTALL_DIR)
	install -m 0644 $(INST_LIBS).a $(LIB_INSTALL_DIR)
endif

install-shlib: build-shlib
ifneq ($(strip $(INST_SHLIBS)),)
	install -m 0755 -d $(LIB_INSTALL_DIR)
	install -m 0644 $(INST_SHLIBS).so $(LIB_INSTALL_DIR)
endif

install-prog: build-prog
ifneq ($(strip $(INST_PROGS)),)
	install -m 0755 -d $(PROG_INSTALL_DIR)
	$(foreach prog, $(INST_PROGS), install -m 0755 $(prog).out $(PROG_INSTALL_DIR)/$(prog);)
endif


install-header-r: install-header $(SUBDIRS:%=install-header-r-%)


install-header-local:
	$(MAKE) DESTDIR=`pwd`/tmp_head install-header-r


install-header: $(INST_HEADERS:%=install-%)


$(INST_HEADERS:%=install-%): install-%: %
ifneq ($(strip $(INST_HEADERS)),)
	install -m 0755 -d $(HEADER_INSTALL_DIR)
	install -m 0644 $< $(HEADER_INSTALL_DIR)
endif


HOST_LAUNCH_XML2CFG = $(SYSROOT)/usr/agl/share/launch_xml2cfg.sh
CONF_H = $(SYSROOT)/usr/agl/include/sm_launch_conf.h

%.cfg: %.xml
	set -e; \
	cpp -P -include $(CONF_H) $< > $<.tmp ; \
	cd $(dir $<.tmp); \
	$(HOST_LAUNCH_XML2CFG) $(notdir $<.tmp) > $@ ; \
	rm -f $<.tmp ;


install-data: $(INST_PIXMAPS:%=$(PIXMAP_INSTALL_DIR)/%) $(INST_UCODE:%=$(UCODE_INSTALL_DIR)/%) $(INST_DATAINITOBJ:%=$(DATAINITOBJ_INSTALL_DIR)/%) $(OBJ_COPY_LIST:%=$(OBJ_COPY_INSTALL_DIR)/%) $(INST_CONFBIN:%=$(CONFBIN_INSTALL_DIR)/%)


clean: $(SUBDIRS:%=clean--%)
	rm -f $(CLEAN_FILES)
	rm -rf $(CLEAN_DIRS)

clean-all: $(SUBDIRS:%=clean-all--%)
	rm -f $(CLEAN_FILES) $(UNINST_FILES)
	rm -rf $(CLEAN_DIRS)

clean-self: clean

#################################################################################

%.o: %.c
	$(CC) -MD -MT $(@:%.o=%.os) -MT $@ -MF $(@D)/.$(@F:%.o=%.d) -MP $(AGLCPPFLAGS) $(AGLCFLAGS) -c -o $@ $<
ifeq ($(SAFLAG),on)
	$(SATOOL) $(AGLCPPFLAGS) $(AGLCFLAGS) -c $<
endif

%.o: %.cc
	$(CXX) -MD -MT $(@:%.o=%.os) -MT $@ -MF $(@D)/.$(@F:%.o=%.d) -MP $(AGLCPPFLAGS) $(AGLCXXFLAGS) -c -o $@ $<
ifeq ($(SAFLAG),on)
	$(SATOOL) $(AGLCPPFLAGS) $(AGLCXXFLAGS) -c $<
endif

%.o: %.cpp
	$(CXX) -MD -MT $(@:%.o=%.os) -MT $@ -MF $(@D)/.$(@F:%.o=%.d) -MP $(AGLCPPFLAGS) $(AGLCXXFLAGS) -c -o $@ $<
ifeq ($(SAFLAG),on)
	$(SATOOL) $(AGLCPPFLAGS) $(AGLCXXFLAGS) -c $<
endif

%.o: %.S
	$(CC) -MD -MT $(@:%.o=%.os) -MT $@ -MF $(@D)/.$(@F:%.o=%.d) -MP $(AGLCPPFLAGS) $(AGLASFLAGS) -c -o $@ $<

%.os: %.c
	$(CC) -MD -MT $(@:%.os=%.o) -MT $@ -MF $(@D)/.$(@F:%.os=%.d) -MP $(AGLPICFLAGS) $(AGLCPPFLAGS) $(AGLCFLAGS) -c -o $@ $<
ifeq ($(SAFLAG),on)
	$(SATOOL) $(AGLPICFLAGS) $(AGLCPPFLAGS) $(AGLCFLAGS) -c $<
endif

%.os: %.cc
	$(CXX) -MD -MT $(@:%.os=%.o) -MT $@ -MF $(@D)/.$(@F:%.os=%.d) -MP $(AGLPICFLAGS) $(AGLCPPFLAGS) $(AGLCXXFLAGS) -c -o $@ $<
ifeq ($(SAFLAG),on)
	$(SATOOL) $(AGLPICFLAGS) $(AGLCPPFLAGS) $(AGLCXXFLAGS) -c $<
endif

%.os: %.cpp
	$(CXX) -MD -MT $(@:%.os=%.o) -MT $@ -MF $(@D)/.$(@F:%.os=%.d) -MP $(AGLPICFLAGS) $(AGLCPPFLAGS) $(AGLCXXFLAGS) -c -o $@ $<
ifeq ($(SAFLAG),on)
	$(SATOOL) $(AGLPICFLAGS) $(AGLCPPFLAGS) $(AGLCXXFLAGS) -c $<
endif

%.os: %.S
	$(CC) -MD -MT $(@:%.os=%.o) -MT $@ -MF $(@D)/.$(@F:%.os=%.d) -MP $(AGLPICFLAGS) $(AGLCPPFLAGS) $(AGLASFLAGS) -c -o $@ $<

.%.out.rule:
	@echo '$*.out: $$(call OBJS,$*)' > $@
	@echo '	@rm -f $$(@:%=.%.libdep)' >> $@
	@echo '	$$(LINK) $$(AGLLDFLAGS) -Wl,-rpath=$$(RPATH) -Wl,-rpath-link=$$(RPATHLINK),-Map=$$(@:%.out=%.map) $$(call OBJS,$*) $($(*F)_LDLIBS) $$(AGLLDLIBS) -o $$@' >> $@
	@echo '	@awk '\''$$$$1=="LOAD" && $$$$2~/\.a$$$$/{print("$$@:", $$$$2);print($$$$2 ":")}'\'' $$(@:%.out=%.map) > $$(@:%=.%.libdep)' >> $@

.%.a.rule:
	@echo '$*.a: $$(call OBJS,$*)' > $@
	@echo '	$$(AR) $$(AGLARFLAGS) $$@ $$?' >> $@

.%.so.rule:
	@echo '$*.so: $$(call SOBJS,$*)' > $@
	@echo '	$$(call INST_DUMMY,$*.so)' >> $@
	@test -f $*.ver && echo '	$$(LINK_SHLIB) -shared $$(AGLLDFLAGS) $($(*F)_LDFLAGS) $$(AGLLDLIBS) -Wl,-rpath=$$(RPATH) -Wl,-soname=$*.so,-Map=$$(@:%.so=%.map),--version-script,$*.ver $$^ -o $$@' >> $@ || echo '	$$(LINK_SHLIB) -shared $$(AGLLDFLAGS) $($(*F)_LDFLAGS) $$(AGLLDLIBS) -Wl,-rpath=$$(RPATH) -Wl,-soname=$*.so,-Map=$$(@:%.so=%.map) $$^ -o $$@' >> $@
	@echo '	$$(call CLEAN_DUMMY)' >> $@

.%.ipc.rule:
	@echo 'ipc_name:=$(shell echo $* | tr A-Z a-z)' > $@
	@echo '$$(ipc_name)_client.h $$(ipc_name)_client.c $$(ipc_name)_server.h $$(ipc_name)_server.c: $*.api $$(IPC_MKSTUB)' >> $@
	@echo '	$$(IPC_MKSTUB) $$(AGLCPPFLAGS) $$(IPC_MKSTUB_FLAGS) $$<' >> $@
	@echo >> $@
	@echo '$*.api:' >> $@
	@echo >> $@

################################################################################

#
# If you write a pattern of smbols that the library may export,
# it checks for unmatched symbols at installation time.
#
# (example)
#   libfoo_SYMBOL_PATTERN = ^(foo|FOO)_
#   libbar_SYMBOL_PATTERN = ^(bar|Bar)
#

$(LIB_INSTALL_DIR)/%.so: %.so
	$(INSTALL_SHLIB)
	$(INSTALL_EXT)
	@test -z '$($*_SYMBOL_PATTERN)' || $(NM) -f posix -o $< \
	  | awk 'NF>=3 && $$3~/[ABCDGRST]/ && $$2!~/^(_DYNAMIC|_GLOBAL_OFFSET_TABLE_|_edata|_end|__)/ && $$2!~/$($*_SYMBOL_PATTERN)/ \
	    {print $$1, "WARNING: A symbol ", $$2, " that does not match the registered pattern $($*_SYMBOL_PATTERN) is included." > "/dev/stderr"}'

$(LIB_INSTALL_DIR)/%.a: %.a
	$(INSTALL_LIB)
	@test -z '$($*_SYMBOL_PATTERN)' || $(NM) -f posix -o $< \
	  | awk 'NF>=3 && $$3~/[ABCDGRST]/ && $$2!~/$($*_SYMBOL_PATTERN)/ \
	    {print $$1, "WARNING: A symbol ", $$2, " that does not match the registered pattern $($*_SYMBOL_PATTERN) is included." > "/dev/stderr"}'
#################################################################################

ifneq ($(strip $(SUBDIRS)),)
$(SUBDIRS:%=all-%):
	@set -e; \
	dir=`pwd`; \
	subdir=$(@:all-%=%); \
	echo "leve:$(MAKELEVEL) dir:`basename $$dir` SUBDIR:$$subdir ==START==" ; \
	$(MAKE) -C $(@:all-%=%) all; \
	echo "leve:$(MAKELEVEL) dir:`basename $$dir` SUBDIR:$$subdir ==END==";

$(SUBDIRS:%=install--%):
	@set -e; \
	dir=`pwd`; \
	subdir=$(@:install--%=%); \
	echo "leve:$(MAKELEVEL) dir:`basename $$dir` SUBDIR:$$subdir ==START==" ; \
	$(MAKE) -C $(@:install--%=%) install; \
	echo "leve:$(MAKELEVEL) dir:`basename $$dir` SUBDIR:$$subdir ==END==";

$(SUBDIRS:%=install-header-r-%):
	@set -e; \
	dir=`pwd`; \
	subdir=$(@:install-header-r-%=%); \
	echo "leve:$(MAKELEVEL) dir:`basename $$dir` SUBDIR:$$subdir ==START==" ; \
	$(MAKE) -C $(@:install-header-r-%=%) install-header-r; \
	echo "leve:$(MAKELEVEL) dir:`basename $$dir` SUBDIR:$$subdir ==END==";


$(SUBDIRS:%=clean--%):
	@$(MAKE) -C $(@:clean--%=%) clean

$(SUBDIRS:%=clean-all--%):
	@echo "$@ ==Start=="
	@$(MAKE) -C $(@:clean-all--%=%) clean-all
	@echo "$@ ==End=="

endif


#################################################################################

ifeq ($(MAKECMDGOALS),all)
-include $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif

ifeq ($(MAKECMDGOALS),)
-include $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif

ifeq ($(MAKECMDGOALS),install)
-include $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif
ifeq ($(MAKECMDGOALS),install-test)
-include $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif
ifeq ($(MAKECMDGOALS),install-test-exec)
-include $(PROG_RULES) $(TESTPROG_RULES) $(PROG_DEPS) $(TESTPROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif

ifeq ($(MAKECMDGOALS),test)
-include $(TESTPROG_RULES) $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif

ifeq ($(MAKECMDGOALS),run-ct-local)
-include $(TESTPROG_RULES) $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif

ifeq ($(MAKECMDGOALS),run-itv2-local)
-include $(TESTPROG_RULES) $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES)
endif

ifeq ($(MAKECMDGOALS),run-ut-local)
-include $(TESTPROG_RULES) $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif

ifeq ($(MAKECMDGOALS),run-it-local)
-include $(TESTPROG_RULES) $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif



ifeq ($(MAKECMDGOALS),test-exec)
-include $(TESTPROG_RULES) $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS) $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS) $(ARLIB_RULES) 
endif


ifeq ($(MAKECMDGOALS),build-prog)
-include $(PROG_RULES) $(PROG_DEPS) $(PROG_LIBDEPS)
endif

ifeq ($(MAKECMDGOALS),build-testdriver)
-include $(PROG_RULES) $(TESTPROG_RULES) $(TESTPROG_DEPS) $(TESTPROG_LIBDEPS)
endif

ifeq ($(MAKECMDGOALS),build-lib)
-include $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS)
endif

ifeq ($(MAKECMDGOALS),build-arlib)
-include $(SHLIB_RULES) $(LIB_RULES) $(LIB_DEPS)
endif

ifeq ($(MAKECMDGOALS),build-shlib)
-include $(SHLIB_RULES) $(LIB_DEPS)
endif

ifeq ($(MAKECMDGOALS),build-arlib)
-include $(ARLIB_RULES) $(LIB_DEPS)
endif

ifeq ($(strip $(filter clean%,$(MAKECMDGOALS))),)
ifneq ($(IPC_API_RULES),)
-include $(IPC_API_RULES) $(IPC_API_DEPS)
endif
endif

