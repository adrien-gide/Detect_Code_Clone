//
//  main.cpp
//  
//
//  Created by Adrien Gide on 2019/06/03.
//
//
#include "My_cst.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    My_cst test;
    clock_t time;
    time = clock();

    if(argc < 2)
    {
        cout << " usage: " << argv[0] << " file threshold(default 2)" << endl;
        return 1;
    }
    
    
    ifstream f(argv[1]);
    if (!f)
    {
        cout << " usage: " << argv[0] << " file threshold(default 2)" << endl;
        return 1;
    }
    else
    {
        if (argc==2)
            test.repeat(argv[1]);
        else
            test.repeat(argv[1],atoi(argv[2]));
    }
    
    test.printlist();
    
    
    cout << "Time: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;

    return 0;
}
