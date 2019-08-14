/**
 *
 * WaveletTree.cpp
 * Created by Adrien Gide on 2019/08/08.
 */
#include "WaveletTree.hpp"


using namespace std;

WaveletTree::WaveletTree(string s)
{
    occu_type::iterator it;
    
    for(int i = 0; i < s.size(); i++)
    {
        it = occus.find(s[i]);
        
        if (it == occus.end())
        {
            occus.insert(make_pair(s[i],make_pair(0,1)));
        }
        else
            it->second.second++;
    }
    
    fill_occus();
    root = new Node(*this, s, make_pair(1,occus.size()-1));
}

void WaveletTree::fill_occus()
{
    int sum=0;
    int tmp;
    int i=1;
    for(occu_type::iterator o=occus.begin(); o != occus.end(); o++)
    {
        o->second.first = i++;
        tmp = o->second.second;
        o->second.second=sum;
        sum+=tmp;
//        cout << o->first << " ->  (" << o->second.first<< ", "<< o->second.second << ")   " << endl;
    }
    //    int size = occus.size();
    occus.insert(make_pair(127,make_pair(occus.size()+1,sum)));
    

//    for(occu_type::iterator o=occus.begin(); o != occus.end(); o++)
//        cout << o->first << " ->  (" << o->second.first<< ", "<< o->second.second << ")   " << endl;
}


