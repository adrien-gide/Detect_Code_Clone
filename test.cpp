//
//  test.cpp
//
//
//  Created by Adrien Gide on 2019/05/31.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "cst/Duplifinder.hpp"
#include "simple_st/SuffixTree.h"
#include "bwt/Duplifinder_v2.hpp"

TEST_CASE("CST")
{
    SECTION("1")
    {
        Duplifinder test;
        clock_t time;
        time = clock();
 
        SECTION( "Simple" ) {
            test.repeat("Test files/Test1.txt");
    //        test.printlist();
        }
        SECTION( "Complicated" ) {
            test.repeat("Test files/Test2.txt",3);
    //        test.printlist();
        }
        SECTION( "Lines" ) {
            test.repeat("Test files/Test3.txt",8);
    //        test.printlist();
        }
        SECTION( "Code" ) {
            test.repeat("Test files/Test4.js",200);
    //        test.printlist();
        }

        std::cout << "\nTime: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
        std::cout << "\n------------------------------------------------------------\n"<<std::endl;
    }

    SECTION("MULT")
    {
        Duplifinder test;
        clock_t time;
        time = clock();
        std::set<std::string> files;

        SECTION( "Simple" ) {

            files.insert("Test files/Test5_1.txt");
            files.insert("Test files/Test5_2.txt");
            test.compare(files);
    //        test.printlist();
        }
        SECTION( "Complicated" ) {
            files.insert("Test files/Test6_1.txt");
            files.insert("Test files/Test6_2.txt");
            test.compare(files,3);
    //        test.printlist();
        }
        SECTION( "Lines" ) {
            files.insert("Test files/Test7_1.txt");
            files.insert("Test files/Test7_2.txt");
            test.compare(files,8,10);
    //        test.printlist();
        }
        SECTION( "Code" ) {
            files.insert("Test files/Test8_1.cs");
            files.insert("Test files/Test8_2.cs");
            test.compare(files,20,30);
    //        test.printlist();
        }

        std::cout << "\nTime: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
        std::cout << "\n------------------------------------------------------------\n"<<std::endl;
    }
}

TEST_CASE("ST")
{
    SECTION("1")
    {
        SuffixTree test;
        clock_t time;
        time = clock();

        SECTION( "Simple" ) {
            test.repeat("Test files/Test1.txt");
    //        std::cout<<test.log_tree()<<std::endl;
            //        test.printlist();
        }
        SECTION( "Complicated" ) {
            test.repeat("Test files/Test2.txt",3);
            //        test.printlist();
        }
        SECTION( "Lines" ) {
            test.repeat("Test files/Test3.txt",8);
            //        test.printlist();
        }
        SECTION( "Code" ) {
            test.repeat("Test files/Test4.js",200);
            //        test.printlist();
        }

        std::cout << "\nTime: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
        std::cout << "\n------------------------------------------------------------\n"<<std::endl;
    }

    SECTION("MULT")
    {
        SuffixTree test;
        clock_t time;
        time = clock();
        std::set<std::string> files;

        SECTION( "Simple") {

            files.insert("Test files/Test5_1.txt");
            files.insert("Test files/Test5_2.txt");
            test.compare(files,4);
            //        test.printlist();
        }
        SECTION( "Complicated" ) {
            files.insert("Test files/Test6_1.txt");
            files.insert("Test files/Test6_2.txt");
            test.compare(files,3);
            //        test.printlist();
        }
        SECTION( "Lines" ) {
            files.insert("Test files/Test7_1.txt");
            files.insert("Test files/Test7_2.txt");
            test.compare(files,8,10);
            //        test.printlist();
        }
        SECTION( "Code" ) {
            files.insert("Test files/Test8_1.cs");
            files.insert("Test files/Test8_2.cs");
            test.compare(files,20,30);
            //        test.printlist();
        }

        std::cout << "\nTime: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
        std::cout << "\n------------------------------------------------------------\n"<<std::endl;
    }
}


TEST_CASE("BWT")
{
    SECTION("1")
    {
        Duplifinder_v2 test;
        clock_t time;
        time = clock();

        SECTION( "Simple" ) {
            test.repeat("Test files/Test1.txt");
            //        std::cout<<test.log_tree()<<std::endl;
            //        test.printlist();
        }
        SECTION( "Complicated" ) {
            test.repeat("Test files/Test2.txt",3);
            //        test.printlist();
        }
        SECTION( "Lines" ) {
            test.repeat("Test files/Test3.txt",8);
            //        test.printlist();
        }
        SECTION( "Code" ) {
            test.repeat("Test files/Test4.js",200);
            //        test.printlist();
        }

        std::cout << "\nTime: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
        std::cout << "\n------------------------------------------------------------\n"<<std::endl;
    }

    SECTION("MULT")
    {
        Duplifinder_v2 test;
        clock_t time;
        time = clock();
        std::set<std::string> files;

        SECTION( "Simple") {
            files.insert("Test files/Test5_1.txt");
            files.insert("Test files/Test5_2.txt");
            test.compare(files,4);
            //        test.printlist();
        }
        SECTION( "Complicated" ) {
            files.insert("Test files/Test6_1.txt");
            files.insert("Test files/Test6_2.txt");
            test.compare(files,3);
            //        test.printlist();
        }
        SECTION( "Lines" ) {
            files.insert("Test files/Test7_1.txt");
            files.insert("Test files/Test7_2.txt");
            test.compare(files,6);
            //        test.printlist();
        }
        SECTION( "Code" ) {
            files.insert("Test files/Test8_1.cs");
            files.insert("Test files/Test8_2.cs");
            test.compare(files,20);
            //        test.printlist();
        }

        std::cout << "\nTime: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< std::endl;
        std::cout << "\n------------------------------------------------------------\n"<<std::endl;
    }
}
