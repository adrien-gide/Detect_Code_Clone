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
                    if( map_pos.count(cst.id(*it))==1 )
                    {
//                        std::cout << "id node : " << cst.id(child) << " - pair : ( " << map_pos.at(cst.id(child)).first << ", " << map_pos.at(cst.id(child)).second << ")" << std::endl;
////                        std::cout << "id node : " << cst.id(*it) << " - pair : ( " << map_pos.at(cst.id(*it)).first << ", " << map_pos.at(cst.id(*it)).second << ")" << std::endl;
//                        for(int d=0; d<128; d++)
//
//                            A(sib,d);
//                            if (d!=c && !map_pos.contains(cst.id(child)))
//                            {
//                                std::cout << "pair 2: ( ( " << position.first << ", " << position.second << ")" << std::endl;
//                            }
//
                    }
                }
               
//                for(int i=1; i<=cst.depth(child);i++)
//
//                    for(int j=1; j<=cst.depth(sib);j++)
//
//                        char c = cst.edge(child,i);
//                        std::cout << c << " - " ;
//                        char d = cst.edge(sib,j);
//                        std::cout << d << " " ;
//                        if(c!=d)
//                        {
//                            std::cout << "result: ( (" << i << "," << i+cst.depth(*it)-1 << "), (" << j << "," << j+cst.depth(*it)-1 << ")" << std::endl;
//
//                        }
//
//
//            }
    }
    
}

void My_cst::A(node_type v, char c)
{
    if(cst.is_leaf(v))
    {
        if(get_i(c,v))
        {
            map_pos.insert(std::make_pair(cst.id(v),position));
        }
    }
    else
        for(auto& child : cst.children(v))
            A(child, c);
    
}

bool My_cst::get_i(char c, node_type v)
{
    std::ifstream is(name_f);
    std::string origin( (std::istreambuf_iterator<char>(is) ), (std::istreambuf_iterator<char>()  ));
                       
    int length = origin.size();
    int index = length - cst.depth(v) + 1;
                       
    if( c == origin[index - 1] )
    {
        std::cout << origin[index - 1] <<std::endl;
        position = std::make_pair(c,index+1);
        
        for(int i=index; i<length; i++)
            std::cout << origin[i];
        std::cout<< " : index "<< cst.id(v)<<std::endl;
        return true;
    }
    
    is.close();
    return false;
}

void My_cst::printlist()
{
    for (std::map<size_type, std::pair<char,int>>::iterator it=map_pos.begin(); it!=map_pos.end(); ++it)
    {
        std::cout << "id node : " << it->first << " - pair : ( " << it->second.first << ", " << it->second.second << ")" << std::endl;
    }
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
    
    test.printlist();
    
    return 0;
}
