include $(gRootConf)
TestsInc := ./

LDFlags := $(CoreLDFlags) $(RootLDFlags) $(USECoreLibLDFlags)
CXXFLAGS :=$(CoreCXXFlags) -I$(RootInc) -I$(TestsInc) $(DebugFlag)

tests_utils_src := tests_utils.cc

unit_test_src := $(wildcard tst-*.cc)
unit_test_exe := $(basename $(unit_test_src))

all-tests: $(unit_test_exe)


$(unit_test_exe) : %:%.cc $(tests_utils_src)
	@echo $@ $^
	$(CXX) $(CXXFLAGS) $^ -o bin/$@ $(LDFlags)

clean:
	if [ -d bin ]; then \
		rm -rf bin;\
	fi
	mkdir bin
