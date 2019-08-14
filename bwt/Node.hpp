/**
 *
 * Node.hpp
 * Created by Adrien Gide on 2019/08/08.
 */
#ifndef NODE
#define NODE
#pragma once

#include <string>
#include <vector>
#include <set>

#include "WaveletTree.hpp"

class WaveletTree;

class Node
{
    friend class WaveletTree;
    
public:
    Node(WaveletTree&, std::string ,std::pair<int,int> );
    int rank(int , int );
//    inline std::vector<int> getBit(){return bit_vector;};
    std::vector<int> bit_vector;
    std::string final_string;

private:
    Node *left;
    Node *right;
//    std::string final_string;

};

#endif //NODE
