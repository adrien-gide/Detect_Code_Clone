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

    if(argc < 3)
    {
        cout << " usage: " << argv[0] << " number of files file(s) threshold(default 2)" << endl;
        return 1;
    }
    
    if (atoi(argv[1]) == 1)
    {
        if (argc== atoi(argv[1])+1)
            test.repeat(argv[1]);
        else
            test.repeat(argv[1],atoi(argv[2]));
    }
    else
    {
        set<string> files;
        for (int i = 2; i < 2+atoi(argv[1]);i++)
        {
            ifstream f(argv[i]);
            if (!f)
            {
                cout << " usage: " << argv[0] << " number of files file(s) threshold(default 2)" << endl;
                return 1;
            }
            files.insert(argv[i]);
        }
        
        if (argc==atoi(argv[1])+2)
            test.compare(files);
        else
            test.compare(files,atoi(argv[argc-1]));
    }
    
    test.printlist();
    
    
    cout << "Time: " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s) "<< endl;

    return 0;
}
