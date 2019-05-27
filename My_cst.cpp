//
//  My_cst.cpp
//  
//
//  Created by Adrien Gide on 2019/05/21.
//

#include "My_cst.hpp"
#include <sys/stat.h>
#include <iostream>
#include <string>

using namespace sdsl;
using namespace std;

void My_cst::repeat(char* name_file)
{
    name_f = name_file;
    construct(cst, name_file,1);

    typedef cst_bfs_iterator<cst_t> iterator;
    iterator begin = iterator(&cst, cst.root());
    iterator end   = iterator(&cst, cst.root(), true, true);
    
    vector<pair<char,int>> vec(MAX_NODES);
    
    vector<vector<pair<char,int>> > vec2d(MAX_CHILDREN,vec);
    
    pair_array = vec2d;
    
    for(iterator it=begin; it != end; it++)
    {
//        for(int k = 0; k < cst.degree(*it);k++)
//            for(int l = 1; l < cst.degree(*it); l++)
//            {
//                auto child = cst.select_child(*it,k);
//                auto sib = cst.select_child(*it,l);
                for(int c=0;c<128;c++)
                {
//                    A(child,c);
//                    if( map_pos.count(cst.id(child))==1 )
                    A(*it,c);
//                    if( map_pos.count(cst.id(*it))==1 )
//                    {
//                        cout << "id node : " << cst.id(child) << " - pair : ( " << map_pos.at(cst.id(child)).first << ", " << map_pos.at(cst.id(child)).second << ")" << endl;
////                        cout << "id node : " << cst.id(*it) << " - pair : ( " << map_pos.at(cst.id(*it)).first << ", " << map_pos.at(cst.id(*it)).second << ")" << endl;
//                        for(int d=0; d<128; d++)
//
//                            A(sib,d);
//                            if (d!=c && !map_pos.contains(cst.id(child)))
//                            {
//                                cout << "pair 2: ( ( " << position.first << ", " << position.second << ")" << endl;
//                            }
//
//                    }
                }
               
//                for(int i=1; i<=cst.depth(child);i++)
//
//                    for(int j=1; j<=cst.depth(sib);j++)
//
//                        char c = cst.edge(child,i);
//                        cout << c << " - " ;
//                        char d = cst.edge(sib,j);
//                        cout << d << " " ;
//                        if(c!=d)
//                        {
//                            cout << "result: ( (" << i << "," << i+cst.depth(*it)-1 << "), (" << j << "," << j+cst.depth(*it)-1 << ")" << endl;
//
//                        }
//
//
//            }
    }
}

void My_cst::A(node_type v, char c,int id)
{
    if(cst.is_leaf(v))
    {
        if(get_i(c,v))
        {
            
            int place;
            if(cst.id(v)==0)
            {
                place = 0;
            }
            else
            {
                place = cst.id(cst.parent(v));
            }
            vector<pair<char,int>> vect;
            vect.push_back(position);

            
            pair_array.at(place) = vect;
            pair_array.at(cst.id(v)) = vect;

//            vector<vector<pair<char,int>> >::iterator it = pair_array.insert(pair_array.begin()+place+1,vect);
//            vector<vector<pair<char,int>> >::iterator it2 = pair_array.insert(pair_array.begin()+cst.id(v)+1,vect);
            
        }
    }
    else
        for(auto& child : cst.children(v))
        {
            id = cst.id(child);
            A(child, c,id);
        }
 
}

bool My_cst::get_i(char c, node_type v)
{
    ifstream is(name_f);
    string origin( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));
                       
    int length = origin.size();
    int index = length - cst.depth(v) + 1;
                       
    if( c == origin[index - 1] )
    {
        cout << origin[index - 1] <<endl;
        position = make_pair(c,index+1);
        
        for(int i=index; i<length; i++)
            cout << origin[i];
        cout<< " : node "<< cst.id(v)<<endl;
        return true;
    }
    is.close();
    return false;
}

void My_cst::printlist()
{
//    for (map<size_type, list<pair<char,int>>>::iterator it=map_pos.begin(); it!=map_pos.end(); it++)
//    {
//        cout << "\n id node : " << it->first << endl;
//
//        for (pair<char,int> p : it->second)
//            cout << "  pair : (" << p.first << ", " << p.second << ")" << endl;
//    }
    for(int i=0;i<pair_array.size(); i++) {
        for (int j=0;j<pair_array[i].size(); j++)
            cout << "  pair : (" << pair_array[i][j].first << ", " << pair_array[i][j].second << ")" << endl;
        cout << endl;
    }
 
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "usage: " << argv[0] << " file" << endl;
        return 1;
    }
    
    My_cst test;
    
    test.repeat(argv[1]);
    
    test.printlist();
    
    return 0;
}
