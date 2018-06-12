# Quark Project
#
# root makefile
#


gRootPath := $(shell pwd)
gConfGen  := $(gRootPath)/configs.make
include $(gConfGen)

gRootConf := $(gRootPath)/$(project_name).config



all: help
help:
	@echo "targets:help tests"


env:
	./scripts/make-env.sh $(gRootConf) CC=$(CC) CXX=$(CXX) \
		CorePath=$(CorePath) \
		CoreLibName=$(CoreLibName) \
		CoreLDFlags=$(CoreLDFlags) \
		CoreCXXFlags=$(CoreCXXFlags) \
		RootInc=$(RootInc) \
		RootLDFLAGS=$(RootLDFLAGS)
		
	

.PHONY: tests clean
tests: env
	make all-tests -C $@ gRootConf=$(gRootConf)

clean:
	make -C tests clean
