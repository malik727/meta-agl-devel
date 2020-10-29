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

#
# rpc rule makefile
#

#rpc_apidef directory path must be added
RPC_APIDEF := $(OECORE_NATIVE_SYSROOT)/usr/bin/rpc_apidef

RPC_API_RULES := $(RPC_API:%=.%.api.rule)
rpc_api := $(shell echo $(RPC_API) | tr A-Z a-z)
CLEAN_API_SRCS := $(rpc_api:%=%_api.h) $(rpc_api:%=%_api_stub.c) $(rpc_api:%=%_srvr.h) $(rpc_api:%=%_srvr_stub.c)
RPC_API_DEPS := $(rpc_api:%=%_api_stub.d) $(rpc_api:%=%_srvr_stub.d)

.%.api.rule:
	@echo 'rpc_name:=$(shell echo $* | tr A-Z a-z)' > $@
	@echo '$$(rpc_name)_api.h $$(rpc_name)_api_stub.c $$(rpc_name)_srvr.h $$(rpc_name)_srvr_stub.c: $*.api $$(RPC_APIDEF)' >> $@
	@echo '	$$(RPC_APIDEF) $$(CPPFLAGS) $$(RPC_APIDEF_FLAGS) $$<' >> $@
	@echo >> $@
	@echo '$*.api:' >> $@
	@echo >> $@

ifeq ($(strip $(filter clean%,$(MAKECMDGOALS))),)
ifneq ($(RPC_API_RULES),)
-include $(RPC_API_RULES) $(RPC_API_DEPS)
endif
endif

