# Quark Project
#
# core library
include $(gRootConf)


LDFlags  := $(CoreLDFlags)
CXXFlags := $(CoreCXXFlags) -I$(RootInc)


srcs := $(wildcard *.cc)
tgts := $(patsubst %.cc, %.o, $(srcs))

core-lib-static := lib$(CoreLibName).a

$(core-lib-static): $(tgts)
	@echo "$(InfoPrefix)- packing:$(Suffix)  $@"
	$(AR) cr $@ $^
	$(RANLIB) $@


$(tgts) : %.o:%.cc
	@echo "$(InfoPrefix)- compiling:$(Suffix) $^"
	$(CXX) $(CXXFlags) -c $^ -o $@ $(LDFlags)


.PHONY: clean
clean:
	rm -f *.o *.a
