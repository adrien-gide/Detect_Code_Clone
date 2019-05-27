//
//  My_cst.hpp
//  
//
//  Created by Adrien Gide on 2019/05/21.
//

#ifndef repeat_hpp
#define repeat_hpp

#define NOT_FOUND -1

#include <stdio.h>
#include <iostream>
#include <sdsl/suffix_trees.hpp>


typedef sdsl::cst_sct3<> cst_t;

class My_cst : public cst_t
{
private:
    cst_t cst;
    std::pair<char,int> position;
    std::map<size_type, std::pair<char,int>> map_pos;
    const char* name_f;
    char* suff;
    
public:
    void A(node_type v, char c);
    void repeat(char* name_file);
    bool get_i(char c,node_type v);
    void printlist();
};


#endif /* repeat_hpp */
