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
        test.repeat("Test files/Test1");
        test.printlist();
    }
    SECTION( "Complicated" ) {
        test.repeat("Test files/Test2",3);
        test.printlist();
    }
    SECTION( "Multiple" ) {
        test.repeat("Test files/Test3",8);
        test.printlist();
    }
    SECTION( "Code" ) {
        test.repeat("Test files/Test4.js",274);
        test.printlist();
    }
  
    std::cout << "\nTime: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
    std::cout << "\n------------------------------------------------------------\n"<<std::endl;
    
}

TEST_CASE("Multiple files")
{
    My_cst test;
    My_cst test2;
    clock_t time;
    time = clock();

   
    SECTION( "2 files - Simple single strings" ) {
        #pragma omp parallel num_threads(2)
        #pragma omp sections
        {
            test.repeat("Test files/Test5.1");
        #pragma omp section
            test2.repeat("Test files/Test5.2");
        }
        test.printlist();
        test2.printlist();
    }
    SECTION( "2 files - Complicated single strings" ) {
        #pragma omp parallel num_threads(2)
        #pragma omp sections
        {
            test.repeat("Test files/Test6.1",3);
        #pragma omp section
            test2.repeat("Test files/Test6.2",3);
        }
        test.printlist();
        test2.printlist();
    }
    SECTION( "2 files - Multiple lines" ) {
        #pragma omp parallel num_threads(2)
        #pragma omp sections
        {
            test.repeat("Test files/Test7.1",8);
        #pragma omp section
            test2.repeat("Test files/Test7.2",8);
        }
        test.printlist();
        test2.printlist();
    }
    SECTION( "2 files - Source code files" ) {
        #pragma omp parallel num_threads(2)
        #pragma omp sections
        {
            test.repeat("Test files/Test8_1.cs",10);
        #pragma omp section
            test2.repeat("Test files/Test8_2.cs",10);
        }
        test.printlist();
        test2.printlist();

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
