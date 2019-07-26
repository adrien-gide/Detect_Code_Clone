// Copyright (c) 2012 Adam Serafini

#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <string>
#include <vector>
#include <map>
#include <set>

class SuffixTree;
class Node {
    friend class SuffixTree;
    friend class Suffix;
private:
    Node(Node*, int, int*, int);
    inline int edge_length() {return *end_index - begin_index + 1;}
    void add_child(const SuffixTree&, Node*);
    inline void remove_child(const SuffixTree&, Node*);
    inline bool is_leaf() {return children.empty();}
    void split_edge(const SuffixTree&, int, int);
    Node* get_child(const SuffixTree&, int char_index);
    int get_key(const SuffixTree&, Node*, int) const;
    
    std::set<int> res_A;
    Node* parent;
    std::map<int, Node*> children;
    std::vector<int> labels;
    Node* suffix_link;
    int begin_index;
    int* end_index;
    int ID;
    int breath=0;
    
    int size();

};

#endif   // SRC_NODE_H_
