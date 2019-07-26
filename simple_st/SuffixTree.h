// Copyright (c) 2012 Adam Serafini

#ifndef SRC_SUFFIXTREE_H_
#define SRC_SUFFIXTREE_H_

#define TMP_FILE "tmp.txt"

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <set>


class Suffix;
class Node;
class SuffixTree {
public:
    SuffixTree();
    void construct(std::string);
    std::string log_tree();
    char get_char_at_index(int) const;
    void compare(std::set<std::string> files,int lower_bound=2,unsigned int upper_bound=500);
    void repeat(const char* name_file, int lower_bound=2,unsigned int upper_bound=500, bool multiple=false);
    void loop(Node* v,int lower_bound,unsigned int upper_bound, bool multiple);
    
    
    
private:
    
    int lg_max = 0;
    std::map<std::string,int> lg_map;
    std::string tree_string;
    std::string log_node(Node* parent);
    std::string get_substr(int, int);
    // Suffix Extension rules (Gusfield, 1997)
    enum Rule {RULE_2, RULE_3};
    
    // SPA: Single Phase Algorithm (Gusfield, 1997)
    void SPA(int);
    
    // SEA: Single Extension Algorithm (Gusfield, 1997)
    Rule SEA(Suffix&, int, int);
    
    // The 'skip/count' trick for traversal (Gusfield, 1997)
    Suffix get_suffix(Node*, int, int);
    
    // Apply Suffix Extension Rule 2 (Gusfield, 1997)
    void RULE2(Suffix&, int, int);
    
    Node* root;
    int internal_node_ID;
    int length;
    int* current_end;
    Node* last_leaf_extension;
};

#endif  // SRC_SUFFIXTREE_H_
