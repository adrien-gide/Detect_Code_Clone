# Duplifinder
The term code clone refer to the duplicated code in a source code file. Its detection can lead to debug, to refactoring. It can be also used in order to avoid plagiarism or copyright violation.

## Context
This project was a part of an intership I've made during Summer 2019, in AIST Kansai. The purpose of this subject was to create a tool in order to detect the duplicated code in a source code. The first step was to detect the exact matching pairs. The structure I'm using is a suffix tree, a compressed suffix tree. The first algorithm I have implemented is drawn from [a lecture note][drop] (p. 18-20) who introduce and explain the role of suffix trees in matching pairs detection. The second one is drawn from the [same algorithm][drop] but with a different data structure. Finally, the last one is using [another solution][beller] because the first two weren't lived up to our expectations.

## Requirements

If you want to use the program or modify the code, you may need : 
* a C++11 ready compiler, such as g++ 4.9 or higher, or clang 3.2 or higher.
* the [SDSL Library][sdsl].

It's used for only one of the implemented methods.

## Installation / Downloads

Just cloning the repo will do the work : 
```sh
git clone https://github.com/adrien-gide/Duplifinder.git
```
## Test

After cloning the repo, you may want to test the program. You can create an executable who will run a few examples, according to the files in [Test files](Test%20files/).
To create and run all the tests : 
```sh
cd Duplifinder
make test.exe
./test.exe
```
The framework used for the [Unit tests][test] is [Catch2][catch]. It's simply a [header][header] and the usage in this project is very basic but you can see how it works on [the git][catch].

You can call specific sections 

## Getting started

### Use of the program

First, you need to create the executables with :
```sh
cd Duplifinder
make
```
It will create the 3 main program : `cst.exe` , `st.exe` and `bwt.exe`. Both of them implement the same algorithm, but the first is using compressed suffix tree and the other normal suffix tree. The implementation of compressed suffix tree is the one from the [SDSL-lite library][sdsl] and the simple suffix tree implementation is the one from [adamserafini's github][adam].

You can create a specific executable with this line (for example `st.exe`: 
```
make st.exe
```

In order to use the programs, you need to be aware of the different identifier available. You need to use one of them in order to specify the kind of operation you want to do.
* Specifiers :
    + -s : For a single file
    + -m : For multiple files indicated in commend line
    + -r : For a repository


Hence, you have multiple uses of the executables : 
* Detecting the repeat in only one file 
```sh
.exe -s file_name (lower_bound) (upper_bound)
```
* Compare files in order to detect the similarities :
    + nb_files: Number of files you want to compare
    + file_name1, file_name2, ... : Name of the file(s). Number corresponding to the value before.

```sh
.exe -m nb_files file_name1 file_name2 ... (lower_bound) (upper_bound)
```
* Traverse a directory in order to compare the source code (you specify the types in the main) :
```sh
.exe -r directory_name (lower_bound) (upper_bound)
```

* (optionnal) lower_bound: Minimum length for the repeats. default value = 2
* (optionnal) upper_bound: Maximum length for the repeats. default value = 500
Be careful, if you decide to use "lower_bound" or "upper_bound", you need to use the other one.

The attributes "lower_bound" and "upper_bound" are only working for  `cst.exe`  and `st.exe`. For `bwt.exe`, it will be "min_lgth" and "min_occ". If you use "min_occ", you have to also use "min_lgth" but the opposite is false.

However, the rest remain the same. For example :
```sh
.exe -m nb_files file_name1 file_name2 ... (min_lgth) (min_occ)
```
* (optionnal) min_lgth: Minimum length for the repeats. default value = 2
* (optionnal) min_occ: Minimum occurences for the repeats. default value = 2
 
### Modifying the code

There are only 3 different parts :
* st : Implementation using [normal suffix tree][adam]. Time efficient, will run in a few minutes for big directories. Memory-expensive.  
Modified files from [original git][adam] :  
    + SuffixTree.cpp
    + SuffixTree.h
    + Suffix.cpp
    + Suffix.h
    + Node.cpp
    + Node.h
    + main.cpp

* cst : implementation using [compressed suffix tree][sdsl]. Slower than the second one, especially for big directories (can take hours and hours in some cases). Less memory-expensive. Can be prefered for small files.  
Source files : 
    + Duplifinder.cpp
    + Duplifinder.hpp
    + main.cpp

The class `Duplifinder` inherit the sdsl-lite class `cst_sada`. It allows us to use the methods and the types provided by this class. 

* bwt : implementation using wavelet tree and Burrow's and Wheeler's Transform (BWT). An implementation of wavelet tree was provided by [SDSL-lite library][sdsl] but wasn't doing what we need to do, so there our own implementation (not complete for a wavelet tree but functionnal). The solution is not finished and has bugs. Because of that, it's the slowest solution, but not the most memory-expensive.  
Source files : 
    + Duplifinder_v2.cpp
    + Duplifinder_v2.hpp
    + Node.cpp
    + Node.hpp
    + WaveletTree.cpp
    + WaveletTree.hpp
    + main.cpp


## Remaining tasks

This project is not done and has some things who need to be finished :
    
    + Documentation
    + Debugging of the third solution
    + Output of the third solution (Duplicates localisation, )
    + 

The function are documented in a Doxygen generated [doc][doc] (not updated).


[drop]: https://www.dropbox.com/s/mjvccs6hq69cage/05-SuffixTrees.pdf?dl=0 "Lecture note"
[sdsl]: https://github.com/simongog/sdsl-lite "Git SDSL"
[catch]: https://github.com/catchorg/Catch2 "Git Catch"
[header]: https://github.com/adrien-gide/Duplifinder/blob/master/catch.hpp "Catch file"
[test]: https://github.com/adrien-gide/Duplifinder/blob/master/test.cpp "Test file"
[doc]: https://adrien-gide.github.io/Duplifinder/ "doxygen"
[adam]: https://github.com/adamserafini/suffix-tree "Git suffix tree"
[beller]: https://link.springer.com/content/pdf/10.1007%2F978-3-642-34109-0_11.pdf "second algorithm"
