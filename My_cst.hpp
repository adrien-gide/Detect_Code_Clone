//
//  My_cst.hpp
//  
//
//  Created by Adrien Gide on 2019/05/21.
//

#ifndef repeat_hpp
#define repeat_hpp

#include <stdio.h>
#include <iostream>
#include <sdsl/suffix_trees.hpp>
#include <vector>
#include <string>

typedef sdsl::cst_sct3<> cst_t;

class My_cst : public cst_t
{
public:
    typedef sdsl::cst_bfs_iterator<cst_t> iterator;
    typedef std::map<size_type, std::vector<std::pair<char,int>> > pos_type;
    typedef std::map<size_type, std::vector<std::pair< std::pair<int,int>, std::pair<int,int>> > > results_type;

private:
    
    cst_t cst;
    std::pair<char,int> position;
    pos_type map_pos;
    results_type results_array;
    const char* name_f;
    std::string origin;
    
public:
    inline results_type getResults() {return results_array;};
    inline cst_t getCST() {return cst;};
    void repeat(const char* name_file,int threshold);
    void printlist();
    int compare(My_cst c);
    
private:
    bool get_i(char c, node_type v);
    void A(node_type v, char c);

};


#endif /* repeat_hpp */
