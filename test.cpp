//
//  test.cpp
//
//
//  Created by Adrien Gide on 2019/05/31.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "My_cst.hpp"
#include <time.h>

TEST_CASE("One file")
{
    My_cst test;
    clock_t time;
    time = clock();

    SECTION( "Simple" ) {
        test.repeat("Test files/Test1.txt");
        test.printlist();
    }
    SECTION( "Complicated" ) {
        test.repeat("Test files/Test2.txt",3);
        test.printlist();
    }
    SECTION( "Multiple" ) {
        test.repeat("Test files/Test3.txt",8);
        test.printlist();
    }
    SECTION( "Code" ) {
        test.repeat("Test files/Test4.js.txt",274);
        test.printlist();
    }

    std::cout << "\nTime: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
    std::cout << "\n------------------------------------------------------------\n"<<std::endl;

}

TEST_CASE("Multiple files")
{
    My_cst test;
    clock_t time;
    time = clock();
    std::set<std::string> files;
   
    SECTION( "2 files - Simple single strings" ) {

        files.insert("Test files/Test5_1.txt");
        files.insert("Test files/Test5_2.txt");
        test.compare(files);
        test.printlist();
    }
    SECTION( "2 files - Complicated single strings" ) {
        files.insert("Test files/Test6_1.txt");
        files.insert("Test files/Test6_2.txt");
        test.compare(files,3);
        test.printlist();
    }
    SECTION( "2 files - Multiple lines" ) {
        files.insert("Test files/Test7_2.txt");
        files.insert("Test files/Test7_1.txt");
        test.compare(files,10);
        test.printlist();
    }
    SECTION( "2 files - Source code files" ) {
        files.insert("Test files/Test8_1.cs");
        files.insert("Test files/Test8_2.cs");
        test.compare(files,20);
        test.printlist();
    }

    std::cout << "\nTime: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
    std::cout << "\n------------------------------------------------------------\n"<<std::endl;
    
//    std::cout << "\n------------------------------------------------------------\n"<<std::endl;
//
//    SECTION( "3 files (More than 2) - Simple single strings" ) {
//        v.resize( 10 );
//
//        REQUIRE( v.size() == 10 );
//        REQUIRE( v.capacity() >= 10 );
//    }
//    SECTION( "3 files (More than 2) - Complicated single strings" ) {
//        v.resize( 10 );
//
//        REQUIRE( v.size() == 10 );
//        REQUIRE( v.capacity() >= 10 );
//    }
//    SECTION( "3 files (More than 2) - Multiple lines" ) {
//        v.resize( 10 );
//
//        REQUIRE( v.size() == 10 );
//        REQUIRE( v.capacity() >= 10 );
//    }
//    SECTION( "3 files (More than 2) - Source code files" ) {
//        v.resize( 10 );
//
//        REQUIRE( v.size() == 10 );
//        REQUIRE( v.capacity() >= 10 );
//    }
}
