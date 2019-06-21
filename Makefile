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


TEST= test.cpp cst/Duplifinder.cpp simple_st/Node.cpp simple_st/Suffix.cpp simple_st/SuffixTree.cpp
CST= cst/*.cpp
ST= simple_st/*.cpp

all: cst.exe test.exe st.exe

$(TEST): cst/*.hpp catch.hpp simple_st/*.h
$(CST): cst/*.hpp
$(ST): simple_st/*.h

test.exe: $(TEST)
	$(MY_CXX) $(CXX_FLAGS) $^ -o $@ $(CCLIB) $(PROGRAM_OPTIONS)

cst.exe: $(CST)
	$(MY_CXX) $(CXX_FLAGS) $^ -o $@ $(CCLIB) $(PROGRAM_OPTIONS)

st.exe: $(ST)
	$(MY_CXX) -o $@ $^ $(CCLIB) $(PROGRAM_OPTIONS) $(CXX_FLAGS)


clean:
	rm -f *.exe
	rm -f *.sdsl
