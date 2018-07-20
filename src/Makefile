# Quark Project
#
# core library
include $(gRootConf)


LDFlags  := $(CoreLDFlags)

#ifeq ($(HAVESMP),1)
#	CXXFlags := $(CoreCXXFlags) -I$(RootInc) $(DebugFlag) -DHAVESMP
#else
CXXFlags := $(CoreCXXFlags) -I$(RootInc) $(DebugFlag)
#endif

srcs := $(wildcard *.cc)
tgts := $(patsubst %.cc, %.o, $(srcs))

core-lib-static := lib$(CoreLibName).a

$(core-lib-static): $(tgts)
	@echo "$(InfoPrefix)- packing:$(Suffix) $@"
	$(AR) cr $@ $^
	$(RANLIB) $@


$(tgts) : %.o:%.cc
	@echo "$(InfoPrefix)- compiling:$(Suffix) $^"
	$(CXX) $(CXXFlags) -c $^ -o $@ $(LDFlags)


.PHONY: clean
clean:
	rm -f *.o *.a
