# Detect Code Clone
The term code clone refer to the duplicated code in a source code file. Its detection can lead to debug, to refactoring. It can be also used in order to avoid plagiarism or copyright violation.

## Requirements

If you just want to use the program, there is no nothing required.

If you want to modify the code, you will need : 
* a C++11 ready compiler, such as g++ 4.9 or higher, or clang 3.2 or higher.
* the [SDSL Library][sdsl].

## Installation / Downloads

Just cloning the repo will do the work : 
```sh
git clone https://github.com/adrien-gide/Detect_Code_Clone.git
```
## Test

After cloning the repo, you may want to test the program. You can create an executable who will run a few examples, according to the files in [Test files](Test files/).
To create and run all the tests : 
```sh
cd Detect_Code_Clone
make test.exe
./test.exe
```
The framework used for the [Unit tests]( is [Catch2][catch]. It's simply a [header][header] and the usage in this project is very basic but you can see how it works on [the git][catch].

## Getting started

[sdsl] https://github.com/simongog/sdsl-lite "Git SDSL"
[catch] https://github.com/catchorg/Catch2 "Git Catch"
[header] https://github.com/adrien-gide/Detect_Code_Clone/blob/master/catch.hpp "Catch file"
[test] https://github.com/adrien-gide/Detect_Code_Clone/blob/master/test.cpp "Test file"
