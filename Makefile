LIB_DIR = /Users/adriengide/lib
INC_DIR = /Users/adriengide/include
MY_CXX_FLAGS= -std=c++11 -DNDEBUG -stdlib=libc++ $(CODE_COVER)
MY_CXX_OPT_FLAGS= -O3 -ffast-math -funroll-loops -D__extern_always_inline="extern __always_inline"
MY_CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++
CXX_FLAGS=$(MY_CXX_FLAGS) $(MY_CXX_OPT_FLAGS) -I$(INC_DIR) -L$(LIB_DIR)
CCLIB=-lsdsl -ldivsufsort -ldivsufsort64
SOURCES=$(wildcard *.cpp)
EXECS=$(SOURCES:.cpp=.exe)

all: $(EXECS)

build-test: $(EXECS)

My_cst.exe:My_cst.cpp My_cst.hpp
	$(MY_CXX) $(CXX_FLAGS) -o $@ $< $(CCLIB)

clean:
	rm -f $(EXECS)
	rm -rf *.dSYM
