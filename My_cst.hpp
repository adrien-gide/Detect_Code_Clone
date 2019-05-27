//
//  My_cst.hpp
//  
//
//  Created by Adrien Gide on 2019/05/21.
//

#ifndef repeat_hpp
#define repeat_hpp

#define MAX_NODES 50
#define MAX_CHILDREN 50


#include <stdio.h>
#include <iostream>
#include <sdsl/suffix_trees.hpp>
#include <vector>

typedef sdsl::cst_sct3<> cst_t;

class My_cst : public cst_t
{
private:
    
    cst_t cst;
    std::pair<char,int> position;
//    std::map<size_type, std::list<std::pair<char,int>>> map_pos;
    std::vector< std::vector<std::pair<char,int> > > pair_array;
    const char* name_f;
    
public:
    
    void A(node_type v, char c,int id=0);
    void repeat(char* name_file);
    bool get_i(char c,node_type v);
    void printlist();
};


#endif /* repeat_hpp */
