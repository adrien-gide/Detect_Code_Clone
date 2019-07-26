
//
//  main.cpp
//
//
//  Created by Adrien Gide on 2019/06/28.
//
//
#include "Duplifinder.hpp"
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
    Duplifinder d;
    
    d.repeat("yes");
    
//    for(int i=0; i<d.lcp_array.size();i++)
//        cout<<i<< " : " << d.lcp_array[i]<<endl;
    
    return 0;
}
