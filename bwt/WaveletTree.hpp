/**
 *
 * Duplifinder.hpp
 * Created by Adrien Gide on 2019/06/28.
 */
#ifndef WVLT_TREE
#define WVLT_TREE
#pragma once

#include <iostream>
#include <utility>
#include <map>

#include "Node.hpp"

class Node;
class WaveletTree
{
    friend class Node;
public:
    typedef std::map<std::pair<int,int>, Node* > map_node;
    typedef std::map<char,std::pair<int,long> > occu_type;

public:
    WaveletTree(std::string );
    Node getNode(std::pair<int,int> );
//    inline occu_type getOccus(){return occus;};
//    inline map_node getTree(){return tree;};
    map_node tree;
    occu_type occus;

private:
    Node *root;    
    void fill_occus();

};
#endif //WVLT_TREE


