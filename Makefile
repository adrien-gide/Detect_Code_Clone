LIB_DIR = -L ~/lib
INC_DIR = -I ~/include

MY_CXX_FLAGS= -std=c++11 -DNDEBUG -stdlib=libc++ \
		#-Xpreprocessor -fopenmp \
		$(CODE_COVER) \

MY_CXX_OPT_FLAGS= -Wall -Os
MY_CXX=g++
CXX_FLAGS= $(MY_CXX_FLAGS) $(MY_CXX_OPT_FLAGS) $(INC_DIR) $(LIB_DIR)
CCLIB= -lsdsl -ldivsufsort -ldivsufsort64 \
		-lboost_filesystem -lboost_system \
		#-lomp \

#PROGRAM_OPTIONS= -DMEMORY_MAX_GB=64


TEST= test.cpp Duplifinder.cpp
MAIN= main.cpp Duplifinder.cpp

all: repeat.exe

$(TEST): Duplifinder.hpp catch.hpp
$(MAIN): Duplifinder.hpp

test.exe: $(TEST)
	$(MY_CXX) $(CXX_FLAGS) $^ -o $@ $(CCLIB) $(PROGRAM_OPTIONS)

repeat.exe: $(MAIN)
	$(MY_CXX) $(CXX_FLAGS) $^ -o $@ $(CCLIB) $(PROGRAM_OPTIONS)


clean:
	rm -f *.exe
