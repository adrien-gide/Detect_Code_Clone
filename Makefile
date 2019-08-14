LIB_DIR = -L ~/lib
INC_DIR = -I ~/include

MY_CXX_FLAGS= -std=c++11 -DNDEBUG -stdlib=libc++ \
		#-Xpreprocessor -fopenmp \
		$(CODE_COVER) \

MY_CXX_OPT_FLAGS= -Wall -Os \
		-g \

MY_CXX=g++
CXX_FLAGS= $(MY_CXX_FLAGS) $(MY_CXX_OPT_FLAGS) $(INC_DIR) $(LIB_DIR)
CCLIB= -lsdsl -ldivsufsort -ldivsufsort64 \
		-lboost_filesystem -lboost_system \
		#-lomp \

#PROGRAM_OPTIONS= -DMEMORY_MAX_GB=64


CST= cst/*.cpp
ST= simple_st/*.cpp
BWT= bwt/*.cpp
TEST = test.cpp cst/Duplifinder.cpp simple_st/SuffixTree.cpp simple_st/Suffix.cpp simple_st/Node.cpp bwt/Duplifinder_v2.cpp bwt/Node.cpp bwt/WaveletTree.cpp

all: cst.exe st.exe bwt2.exe

$(TEST): *.hpp simple_st/*.h
$(CST): cst/*.hpp
$(ST): simple_st/*.h
$(BWT): bwt/*.hpp

test.exe: $(TEST)
	$(MY_CXX) $(CXX_FLAGS) $^ -o $@ $(CCLIB) $(PROGRAM_OPTIONS)

cst.exe: $(CST)
	$(MY_CXX) $(CXX_FLAGS) $^ -o $@ $(CCLIB) $(PROGRAM_OPTIONS)

st.exe: $(ST)
	$(MY_CXX) -o $@ $^ $(CCLIB) $(PROGRAM_OPTIONS) $(CXX_FLAGS)

bwt2.exe: $(BWT)
	$(MY_CXX) -o $@ $^ $(CCLIB) $(PROGRAM_OPTIONS) $(CXX_FLAGS)


clean:
	rm -f *.exe
	rm -f *.sdsl
	rm -rf *.dSYM
