//
//  main.cpp
//  
//
//  Created by Adrien Gide on 2019/05/29.
//


#include <stdio.h>
#include "My_cst.hpp"


using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << " usage: " << argv[0] << " file threshold" << endl;
        return 1;
    }
 

    ifstream f(argv[1]);
    if (!f)
    {
        cout << " usage: " << argv[0] << " file threshold" << endl;
        return 1;
    }
    else
    {
        My_cst test;
        
        test.repeat(argv[1],atoi(argv[2]));
        
        test.printlist();
    }
 

    return 0;
}
