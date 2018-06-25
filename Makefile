# Quark Project
#
# root makefile
#

project_name := quark
gRootPath := $(shell pwd)

lGccDir := $(gRootPath)/deps/gcc-5.3

#
# global environment
#
#CC  := $(lGccDir)/bin/gcc
#CXX := $(lGccDir)/bin/g++
CC  := clang
CXX := clang++
AR  := ar
RANLIB := ranlib

CorePath := $(gRootPath)/src
CoreLibName := $(project_name)
CoreCXXFlags := -std=c++11
CoreLDFlags := -lpthread
RootInc := $(gRootPath)/include


gConfInput-Static := $(gRootPath)/configs.static
gRootConf := $(gRootPath)/$(project_name).config
gTestsPath := $(gRootPath)/tests

all: help
help:
	@echo "targets:"
	@echo "  help  - print this message."
	@echo "  tests - unit tests"
	@echo "  quark - core library"


env:
	./scripts/make-env.sh $(gRootConf) $(gConfInput-Static) \
		gRootPath=$(gRootPath) \
		CC=$(CC) CXX=$(CXX) \
		CorePath=$(CorePath) \
		CoreLibName=$(CoreLibName) \
		CoreLDFlags=$(CoreLDFlags) \
		CoreCXXFlags=$(CoreCXXFlags) \
		RootInc=$(RootInc) \
		AR=$(AR) RANLIB=$(RANLIB) \
		USECoreLibLDFlags="-L$(CorePath),-l$(CoreLibName)"

		
quark: env
	make -C $(CorePath) gRootConf=$(gRootConf)


.PHONY: tests clean
tests: env
	make all-tests -C $(gTestsPath) gRootConf=$(gRootConf)

clean:
	make -C $(CorePath) clean
	make -C $(gTestsPath) clean
