//
//  main.cpp
//  
//
//  Created by Adrien Gide on 2019/06/03.
//
//
#include "Duplifinder.hpp"
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;

void process_mem_usage(double& vm_usage, double& resident_set)
{
    vm_usage     = 0.0;
    resident_set = 0.0;
    
    // the two fields we want
    unsigned long vsize;
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
        >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
        >> ignore >> ignore >> vsize >> rss;
    }
    
    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}

int main(int argc, char* argv[])
{
  
    Duplifinder test;
    clock_t time;
    time = clock();
//    ".py",".pl",".cs",".css",".html",".c",".cc",".h",".hpp"
    
    const char* types[] = {".cpp",".h",".hpp"};
    
    set<string> s_typ;
    int size =  sizeof(types) / sizeof(types[0]);
    for(int t = 0; t <size; t++)
        s_typ.insert(types[t]);
    
//    if(argc < 3)
//    {
//        cout << " usage: " << argv[0] << " number of files file(s) int(min depth: default 2)" << endl;
//        return 1;
//    }
//
//    if (atoi(argv[1]) == 1)
//    {
//        if (argc== atoi(argv[1])+1)
//            test.repeat(argv[1]);
//        else
//            test.repeat(argv[1],atoi(argv[2]));
//    }
//    else
//    {
        set<string> setfiles;
//        for (int i = 2; i < 2+atoi(argv[1]);i++)
//        {
//            ifstream f(argv[i]);
//            if (!f)
//            {
//                cout << " usage: " << argv[0] << " number of files file(s) int(min depth: default 2)" << endl;
//                return 1;
//            }
//            files.insert(argv[i]);
//        }
//
//        if (argc==atoi(argv[1])+2)
//            test.compare(files,2);
//        else
//            test.compare(files,atoi(argv[argc-1]));
//    }
    
    if (argc < 2)
    {
        cout << "Usage: exe path\n";
        return 1;
    }
    
    system::error_code ec;
    
    filesystem::path f(argv[1]);
    
    if (filesystem::is_directory(f))
        for (filesystem::recursive_directory_iterator it{f, ec}, end; it != end; it.increment(ec))
            if (!filesystem::is_directory(it->path()) )
                if (s_typ.find(filesystem::extension(it->path())) != s_typ.end() )
                    setfiles.insert(it->path().string());

    cout << "Time get files: " << ( clock())/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
    
    cout<<setfiles.size()<<endl;

    test.compare(setfiles,500);
//    test.printlist();
    
    double vm, rss;
    process_mem_usage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;
//
//    struct statfs stats;
//    if (0 == statfs("/", &stats))
//    {
//        myFreeSwap = (uint64_t)stats.f_bsize * stats.f_bfree;
//    }
//
    
    cout << "Time finish: " << ( clock() )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;

    return 0;
}


