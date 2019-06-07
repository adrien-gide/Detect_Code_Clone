LIB_DIR = -L ~/lib
INC_DIR = -I ~/include

MY_CXX_FLAGS= -std=c++11 -DNDEBUG -stdlib=libc++ \
		#-Xpreprocessor -fopenmp \
		$(CODE_COVER) \

MY_CXX_OPT_FLAGS= -Wall -Os
MY_CXX=g++
CXX_FLAGS= $(MY_CXX_FLAGS) $(MY_CXX_OPT_FLAGS) $(INC_DIR) $(LIB_DIR)
CCLIB= -lsdsl -ldivsufsort -ldivsufsort64 \
		#-lomp \

#PROGRAM_OPTIONS= -DMEMORY_MAX_GB=64


SOURCES= test.cpp Duplifinder.cpp

all: repeat.exe

$(SOURCES): Duplifinder.hpp catch.hpp

test.exe: $(SOURCES)
	$(MY_CXX) $(CXX_FLAGS) $^ -o $@ $(CCLIB) $(PROGRAM_OPTIONS)

repeat.exe: main.cpp Duplifinder.cpp
	$(MY_CXX) $(CXX_FLAGS) $^ -o $@ $(CCLIB) $(PROGRAM_OPTIONS)

clean:
	rm -f *.exe
