
//
//  main.cpp
//
//
//  Created by Adrien Gide on 2019/06/28.
//
//
#include "Duplifinder_v2.hpp"
#include "WaveletTree.hpp"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
//
//    WaveletTree *wt = new WaveletTree("mnuuuuullummmd$m");
//
//
//    cout << "      completion "<<  endl;
//
//    for (WaveletTree::map_node::iterator it = wt->tree.begin(); it != wt->tree.end(); it++)
//    {
//
//        if(!it->second->bit_vector.empty())
//        {
//            int size = it->second->bit_vector.size();
//            for (int o=0; o<size; o++)
//                cout << it->second->bit_vector[o];
//    //        cout << "oy" << endl;
//    //        for(int o : it->second->getBit())
//    //            cout << o;
//            cout << endl;
//        }
//        else
//            cout << it->second->final_string<<endl;;
//    }
//
//    return 0;
    
    clock_t time = clock();

    Duplifinder_v2 d;
     set<string> setfiles;

    const char* types[] = {".cpp",".h",".hpp"};

    set<string> s_typ;
    int size =  sizeof(types) / sizeof(types[0]);
    for(int t = 0; t <size; t++)
        s_typ.insert(types[t]);
    system::error_code ec;

    filesystem::path f("../gcc");

    if (filesystem::is_directory(f))
        for (filesystem::recursive_directory_iterator it{f, ec}, end; it != end; it.increment(ec))
            if (!filesystem::is_directory(it->path()) )
                if (s_typ.find(filesystem::extension(it->path())) != s_typ.end() )
                    setfiles.insert(it->path().string());

    cout << "Time get files: " << ( clock())/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;

    ofstream merge(TMP_FILE3, ios_base::binary);
    //    clock_t time =clock();

//    double lg = 0;
    int id = 0;
    for (string f : setfiles)
    {
        ifstream tmp(f, ios_base::binary);
        if (tmp.good())
        {
            merge << tmp.rdbuf() << "\n$id$:" << id++ << endl;
//            lg += tmp.tellg();
//            lg_map.insert(make_pair(f,lg));
//            if (lg_max <= tmp.tellg())
//                lg_max = tmp.tellg();
        }
        tmp.close();
    }
    cout << "Time concat : " <<  clock()/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
    merge.close();

//    d.repeat(TMP_FILE3,500);
    d.repeat("Test Files/Test3.txt");

//    for(int i=0; i<d.lcp_array.size();i++)
//        cout<<i<< " : " << d.lcp_array[i]<<endl;
    cout << "Time complete : " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;

    return 0;
}

//int main(int argc, char* argv[])
//{
//
//    Duplifinder_v2 test;
//    clock_t time;
//    time = clock();
//    //    ".py",".pl",".cs",".css",".html",".c",".cc",".h",".hpp"
//
//    const char* types[] = {".cpp",".h",".hpp"};
//
//    set<string> s_typ;
//    int size =  sizeof(types) / sizeof(types[0]);
//    for(int t = 0; t <size; t++)
//        s_typ.insert(types[t]);
//
//    if(argc < 3)
//    {
//        cout << " usage: " << argv[0] << " identifier file(s) lower_bound(min depth: default 2) upper_bound(max depth: default 500)" << endl;
//        return 1;
//    }
//
//    if (strcmp(argv[1],"-s")==0)
//    {
//        if (argc == 3)
//            test.repeat(argv[2]);
//        else if (argc == 5)
//            test.repeat(argv[2],atoi(argv[3]),atoi(argv[4]));
//        else
//            cout << " usage: " << argv[0] << " identifier file lower_bound(min depth: default 2) upper_bound(max depth: default 500)" << endl;
//    }
//
//    else if (strcmp(argv[1],"-c")==0)
//    {
//        if(argc < 4 || atoi(argv[2]) < 2)
//        {
//            cout << " usage: " << argv[0] << " identifier number_of_files file(s) lower_bound(min depth: default 2) upper_bound(max depth: default 500)" << endl;
//            return 1;
//        }
//
//        set<string> setfiles;
//        for (int i = 3; i < 3+atoi(argv[2]);i++)
//        {
//            ifstream f(argv[i]);
//            if (!f)
//            {
//                cout << " the file can't open !" << endl;
//                return 1;
//            }
//            setfiles.insert(argv[i]);
//        }
//
//        if (argc==atoi(argv[2])+3)
//            test.compare(setfiles,2);
//        else if (argc==atoi(argv[2])+5)
//            test.compare(setfiles,atoi(argv[argc-2]),atoi(argv[argc-1]));
//        else
//            cout << " usage: " << argv[0] << " identifier file(s) lower_bound(min depth: default 2) upper_bound(max depth: default 500)" << endl;
//    }
//    else if (strcmp(argv[1],"-r")==0)
//    {
//        set<string> setfiles;
//        if (argc < 3)
//        {
//            cout << "Usage: exe identifier path lower_bound(min depth: default 2) upper_bound(max depth: default 500)" << endl;
//            return 1;
//        }
//        system::error_code ec;
//
//        filesystem::path f(argv[2]);
//
//        if (filesystem::is_directory(f))
//            for (filesystem::recursive_directory_iterator it{f, ec}, end; it != end; it.increment(ec))
//                if (!filesystem::is_directory(it->path()) )
//                    if (s_typ.find(filesystem::extension(it->path())) != s_typ.end() )
//                        setfiles.insert(it->path().string());
//
//        cout << "Time get files: " << ( clock())/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
//
//        cout<<setfiles.size()<<endl;
//
//        if (argc==3)
//            test.compare(setfiles,2);
//        else if (argc==5)
//            test.compare(setfiles,atoi(argv[argc-2]),atoi(argv[argc-1]));
//        else
//            cout << " usage: " << argv[0] << " identifier file(s) lower_bound(min depth: default 2) upper_bound(max depth: default 500)" << endl;
//    }
//    else
//    {
//        cout << "Identifer is missing or is invalid."<<endl;
//        cout<< "    -r : repository\n   -c: comparison between files\n    -s: single file"<<endl;
//        return 0;
//    }
//
//    cout << "Time finish: " << ( clock() )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
//
//    return 0;
//}
//
//
