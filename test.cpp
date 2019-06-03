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

TEST_CASE("Test")
{
    My_cst test;
    clock_t time;
    time = clock();
    
    SECTION( "Simple" ) {
        test.repeat("Test files/Test1",2);
//        REQUIRE(!test.getResults().empty());
        test.printlist();
    }
    SECTION( "Complicated" ) {
        test.repeat("Test files/Test2",3);
//        REQUIRE(test.getResults().empty());
        test.printlist();
    }
    SECTION( "Multiple" ) {
        test.repeat("Test files/Test3",8);
//        REQUIRE(!test.getResults().empty());
        test.printlist();
    }
    SECTION( "Code" ) {
        test.repeat("Test files/Test4.js",274);
//        REQUIRE(!test.getResults().empty());
        test.printlist();
    }
    std::cout << "Time: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
    
    std::cout << "\n------------------------------------------------------------\n"<<std::endl;
//
//    SECTION( "2 files - Simple single strings" ) {
//        v.resize( 10 );
//
//        REQUIRE( v.size() == 10 );
//        REQUIRE( v.capacity() >= 10 );
//    }
//    SECTION( "2 files - Complicated single strings" ) {
//        v.resize( 10 );
//
//        REQUIRE( v.size() == 10 );
//        REQUIRE( v.capacity() >= 10 );
//    }
//    SECTION( "2 files - Multiple lines" ) {
//        v.resize( 10 );
//
//        REQUIRE( v.size() == 10 );
//        REQUIRE( v.capacity() >= 10 );
//    }
//    SECTION( "2 files - Source code files" ) {
//        v.resize( 10 );
//
//        REQUIRE( v.size() == 10 );
//        REQUIRE( v.capacity() >= 10 );
//    }
//
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

