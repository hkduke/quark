include $(gRootConf)
TestsInc := ./

LDFlags := $(CoreLDFlags) $(RootLDFlags)
CXXFLAGS :=$(CoreCXXFlags) -I$(RootInc) -I$(TestsInc)

tests_utils_src := tests_utils.cc

unit_test_src := $(wildcard tst-*.cc)
unit_test_exe := $(basename $(unit_test_src))

all-tests: $(unit_test_exe)


$(unit_test_exe) : %:%.cc $(tests_utils_src)
	mkdir bin
	@echo $@ $^
	$(CXX) $(CXXFLAGS) $^ -o bin/$@ $(LDFlags)

clean:
	rm -rf bin
