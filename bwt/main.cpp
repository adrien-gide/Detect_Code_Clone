
//
//  main.cpp
//
//
//  Created by Adrien Gide on 2019/08/08.
//
//
#include "Duplifinder_v2.hpp"
#include "WaveletTree.hpp"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{

    Duplifinder_v2 test;
    clock_t time;
    time = clock();
    //    ".py",".pl",".cs",".css",".html",".c",".cc",".h",".hpp"

    const char* types[] = {".cpp",".h",".hpp"};

    set<string> s_typ;
    int size =  sizeof(types) / sizeof(types[0]);
    for(int t = 0; t <size; t++)
        s_typ.insert(types[t]);

    if(argc < 3)
    {
        cout << " usage: " << argv[0] << " identifier file(s) min_lgth(default 2) min_occ(default 2)" << endl;
        return 1;
    }

    if (strcmp(argv[1],"-s")==0)
    {
        if (argc == 3)
            test.repeat(argv[2]);
        else if (argc == 4)
            test.repeat(argv[2],atoi(argv[3]));
        else if (argc == 5)
            test.repeat(argv[2],atoi(argv[3]),atoi(argv[4]));
        else
            cout << " usage: " << argv[0] << " identifier file min_lgth(default 2) min_occ(default 2)" << endl;
    }

    else if (strcmp(argv[1],"-c")==0)
    {
        if(argc < 4 || atoi(argv[2]) < 2)
        {
            cout << " usage: " << argv[0] << " identifier number_of_files file(s) min_lgth(default 2) min_occ(default 2)" << endl;
            return 1;
        }

        set<string> setfiles;
        for (int i = 3; i < 3+atoi(argv[2]);i++)
        {
            ifstream f(argv[i]);
            if (!f)
            {
                cout << " the file can't open !" << endl;
                return 1;
            }
            setfiles.insert(argv[i]);
        }

        if (argc==atoi(argv[2])+3)
            test.compare(setfiles,2);
        else if (argc==atoi(argv[2])+4)
            test.compare(setfiles,atoi(argv[argc-1]));
        else if (argc==atoi(argv[2])+5)
            test.compare(setfiles,atoi(argv[argc-2]),atoi(argv[argc-1]));
        else
            cout << " usage: " << argv[0] << " identifier file(s) lmin_lgth(default 2) min_occ(default 2)" << endl;
    }
    else if (strcmp(argv[1],"-r")==0)
    {
        set<string> setfiles;
        if (argc < 3)
        {
            cout << "Usage: exe identifier path min_lgth(default 2) min_occ(default 2)" << endl;
            return 1;
        }
        system::error_code ec;

        filesystem::path f(argv[2]);

        if (filesystem::is_directory(f))
            for (filesystem::recursive_directory_iterator it{f, ec}, end; it != end; it.increment(ec))
                if (!filesystem::is_directory(it->path()) )
                    if (s_typ.find(filesystem::extension(it->path())) != s_typ.end() )
                        setfiles.insert(it->path().string());

        cout << "Time get files: " << ( clock())/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;

        cout<<setfiles.size()<<endl;

        if (argc==3)
            test.compare(setfiles,2);
        else if (argc==4)
            test.compare(setfiles,atoi(argv[argc-1]));
        else if (argc==5)
            test.compare(setfiles,atoi(argv[argc-2]),atoi(argv[argc-1]));
        else
            cout << " usage: " << argv[0] << " identifier file(s) min_lgth(default 2) min_occ(default 2)" << endl;
    }
    else
    {
        cout << "Identifer is missing or is invalid."<<endl;
        cout<< "    -r : repository\n   -c: comparison between files\n    -s: single file"<<endl;
        return 0;
    }

    cout << "Time finish: " << ( clock() )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;

    return 0;
}


