project_name := quark
this := $(shell pwd)

lGccDir := $(this)/deps/gcc-5.3

#
# global environment
#
#CC  := $(lGccDir)/bin/gcc
#CXX := $(lGccDir)/bin/g++
CC  := clang
CXX := clang++


CorePath := $(this)/src
CoreLibName := lib$(project_name)
CoreCXXFlags := -std=c++11
CoreLDFlags :=

RootInc := $(this)/include
RootLDFLAGS := -lpthread
