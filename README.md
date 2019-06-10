# Duplifinder
The term code clone refer to the duplicated code in a source code file. Its detection can lead to debug, to refactoring. It can be also used in order to avoid plagiarism or copyright violation.

## Context
This project was a part of an intership I've made during Summer 2019, in AIST Kansai. The purpose of this subject was to create a tool in order to detect the duplicated code in a source code. The first step was to detect the exact matching pairs. The structure I'm using is a suffix tree, a compressed suffix tree. The algorithm I have implemented is drawn from [a lecture note][drop] (p. 18-20) who introduce and explain the role of suffix trees in matching pairs detection.

## Requirements

If you want to use the program or modify the code, you will need : 
* a C++11 ready compiler, such as g++ 4.9 or higher, or clang 3.2 or higher.
* the [SDSL Library][sdsl].

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

## Getting started

### Use of the program

First, you need to create the executable with :
```sh
cd Duplifinder
make
```
The program will be used with 2 mandatory arguments, and one optionnal. There is also 2 different uses of the program :

+ Detecting the repeat in only one file 
```sh
./repeat.exe 1 file_name (threshold)
```
+ Compare files in order to detect the similarities
```sh
./repeat.exe nb_files file_name1 file_name2 ... (threshold)
```
* nb_files: Number of files you want to compare
* file_name1, 2, ... : Name of the file(s). Number corresponding to the value before.
* (optionnal) threshold: Minimum length for the repeats. default value = 2

### Modifying the code

There are only 3 different files : 
+ Duplifinder.cpp
+ Duplifinder.hpp
+ main.cpp

The class `Duplifinder` inherit the sdsl-lite class `cst_sct3`. It allows us to use the methods and the types provided by this class. 
The function are documented in a Doxygen generated [doc][doc].






[drop]: https://www.dropbox.com/s/mjvccs6hq69cage/05-SuffixTrees.pdf?dl=0 "Lecture note"
[sdsl]: https://github.com/simongog/sdsl-lite "Git SDSL"
[catch]: https://github.com/catchorg/Catch2 "Git Catch"
[header]: https://github.com/adrien-gide/Detect_Code_Clone/blob/master/catch.hpp "Catch file"
[test]: https://github.com/adrien-gide/Detect_Code_Clone/blob/master/test.cpp "Test file"
[doc]: https://adrien-gide.github.io/Detect_Code_Clone/
