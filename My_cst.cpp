//
//  My_cst.cpp
//  
//
//  Created by Adrien Gide on 2019/05/21.
//

#include "My_cst.hpp"
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>

using namespace sdsl;


void My_cst::repeat(char* name_file)
{
    name_f = name_file;
    construct(cst, name_file,1);
    
    auto root = cst.root();
    
//    typedef const_bottom_up_iterator iterator;
//    iterator begin = cst.begin_bottom_up();
//    iterator end   = cst.end_bottom_up();

    typedef cst_bfs_iterator<cst_t> iterator;
    iterator begin = iterator(&cst, cst.root());
    iterator end   = iterator(&cst, cst.root(), true, true);
    
    for(iterator it=begin; it != end; it++)
    {
        for(int k = 0; k < cst.degree(*it);k++)
        {
            for(int l = 1; l < cst.degree(*it); l++)
            {
                
                auto child = cst.select_child(*it,k);
                auto sib = cst.select_child(*it,l);
                for(int c=0;c<128;c++)
                {
                    A(child,c);
                    if( map_pos.count(cst.id(child))==1 )
                    {
                        std::cout << "pair : ( " << map_pos[cst.id(child)].first << ", " << map_pos[cst.id(child)].second << ")" << std::endl;
//                        for(int d=0; d<128; d++)
//                        {
//                            A(sib,d);
//                            if (d!=c && !map_pos.contains(cst.id(child)))
//                            {
//                                std::cout << "pair 2: ( ( " << position.first << ", " << position.second << ")" << std::endl;
//                            }
//                        }
                    }
                }
               
//                for(int i=1; i<=cst.depth(child);i++)
//                {
//                    for(int j=1; j<=cst.depth(sib);j++)
//                    {
//                        char c = cst.edge(child,i);
//                        std::cout << c << " - " ;
//                        char d = cst.edge(sib,j);
//                        std::cout << d << " " ;
//                        if(c!=d)
//                        {
//                            std::cout << "result: ( (" << i << "," << i+cst.depth(*it)-1 << "), (" << j << "," << j+cst.depth(*it)-1 << ")" << std::endl;
//
//                        }
//                    }
//                }
            }
        }
    }
}

void My_cst::A(node_type v, char c)
{
    if(cst.is_leaf(v))
    {
        get_i(c,v);
        map_pos.insert(std::make_pair(cst.id(v),position));
    }
    else{
        for(auto& child : cst.children(v))
        {
            A(child, c);
        }
    }
}

void My_cst::get_i(char c, node_type v)
{
    std::ifstream is;
    is.open (name_f, std::ios::binary );
    is.seekg (0, std::ios::end);
    int length = is.tellg();
    int index = length - cst.depth(v) + 1;
    
    position = std::make_pair(c,index);
    
}


int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "usage: " << argv[0] << " file" << std::endl;
        return 1;
    }
    
    My_cst test;
    
    test.repeat(argv[1]);
    
    return 0;
}
