LIB_DIR = /Users/adriengide/lib
INC_DIR = /Users/adriengide/include
MY_CXX_FLAGS= -std=c++11 -DNDEBUG -stdlib=libc++ $(CODE_COVER)
MY_CXX_OPT_FLAGS= -O3
MY_CXX=g++
CXX_FLAGS=$(MY_CXX_FLAGS) $(MY_CXX_OPT_FLAGS) -I$(INC_DIR) -L$(LIB_DIR)
CCLIB=-lsdsl -ldivsufsort -ldivsufsort64
SOURCES=$(wildcard *.cpp)

all: repeat.exe

$(SOURCES): My_cst.hpp

repeat.exe: $(SOURCES)
	$(MY_CXX) $(CXX_FLAGS) $^ -o $@ $(CCLIB)

clean:
	rm -f *.exe
	rm -rf *.dSYM
