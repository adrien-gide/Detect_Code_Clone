// Copyright (c) 2012 Adam Serafini

#include <map>
#include <sstream>
#include <fstream>

#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h"

using namespace std;

SuffixTree::SuffixTree() {
    // Internal node IDs start at zero and decrement. For example, the root node,
    // which can be considered the first internal node has an ID of 0. The next
    // internal node has an ID of -1, followed by -2 and so forth.
    
    // While not neccessary for the algorithm to function, each node having a
    // unique ID is important when using Graphiz to visualize the structure.
    internal_node_ID = 0;
    
    current_end = new int(0);
    root = new Node(NULL, 1, current_end, internal_node_ID);
}

void SuffixTree::construct(std::string s) {
    length = s.length();
    tree_string = s;
    
    // Construct Implicit Tree I(1).
    (*current_end)++;
    last_leaf_extension = new Node(root, 1, current_end, 1);
    root->add_child(*this, last_leaf_extension);
    
    for (int i = 1; i < length; i++)
        SPA(i);
}

// SPA: Single Phase Algorithm (Gusfield, 1997)
void SuffixTree::SPA(int i) {
    // Do phase i + 1.
    
    Suffix previous_suffix(last_leaf_extension, *current_end);
    
    // Increment the current_end pointer: this implicitly applies Rule 1 to all
    // leaf edges in the tree.
    (*current_end)++;
    
    // Explicitly compute successive extensions starting at j(i) + 1 where (i)
    // is the ID of the last leaf extension from the previous phase.
    for (int j = (last_leaf_extension->ID + 1); j <= i + 1; j++) {
        Rule rule_applied = SEA(previous_suffix, j, i);
        if (rule_applied == RULE_3)
            break;
    }
}

// SEA: Single Extension Algorithm (Gusfield, 1997)
SuffixTree::Rule SuffixTree::SEA(Suffix& previous_suffix, int j, int i) {
    int begin_index, end_index;
    Node* origin = previous_suffix.walk_up(begin_index, end_index);
    Suffix suffix = (origin == root ? get_suffix(root, j, i)
                     : get_suffix(origin->suffix_link, begin_index, end_index));
    
    Rule rule_applied;
    if (suffix.RULE2_conditions(*this, i + 1)) {
        RULE2(suffix, i + 1, j);
        rule_applied = RULE_2;
    } else {
        rule_applied = RULE_3;
    }
    
    if (previous_suffix.new_internal_node)
        previous_suffix.node->suffix_link = suffix.node;
    
    previous_suffix = suffix;
    return rule_applied;
}

// The 'skip/count' trick for suffix tree traversal (Gusfield, 1997)
Suffix SuffixTree::get_suffix(Node* origin, int begin_index, int end_index) {
    int char_index = *origin->end_index;
    
    while (begin_index <= end_index) {
        origin = origin->get_child(*this, begin_index);
        if (origin->edge_length() < end_index - begin_index + 1)
            char_index = *origin->end_index;
        else
            char_index = origin->begin_index + (end_index - begin_index);
        begin_index+=origin->edge_length();
    }
    return Suffix(origin, char_index);
}

std::string SuffixTree::get_substr(int start_pos, int end_pos) {
    if (start_pos > end_pos) return std::string();
    // This is 1-indexed to match the algorithm's original description in the
    // paper. For example, "foobar".get_substr(2, 4) == "oob".
    return tree_string.substr(start_pos - 1, end_pos - start_pos + 1);
}

char SuffixTree::get_char_at_index(int index) const {
    // Also 1-indexed. For example, "foobar".get_char_at_index(4) == 'b'
    return tree_string[index - 1];
}

void SuffixTree::RULE2(Suffix& suffix, int char_index, int new_leaf_ID) {
    if (!suffix.ends_at_node()) {  // eg. in case 2 (path ends inside an edge)
        suffix.node->split_edge(*this, suffix.char_index, --internal_node_ID);
        suffix.node = suffix.node->parent;
        suffix.new_internal_node = true;
    }
    Node* new_leaf = new Node(suffix.node, char_index, current_end, new_leaf_ID);
    suffix.node->add_child(*this, new_leaf);
    last_leaf_extension = new_leaf;
}

std::string SuffixTree::log_tree() {
    return "digraph g{\n" + log_node(root) + "}";
}

std::string SuffixTree::log_node(Node* parent) {
    std::map<int, Node*>::iterator it = parent->children.begin();
    
    std::stringstream buffer;
    
    // Internal nodes (nodes with ID <= 0) are unlabelled points, leaves
    // (nodes with ID > 0) show the ID as plaintext.
    buffer << parent->ID << "[shape="
    << ((parent->ID <= 0) ? "point" : "plaintext") << "];\n";
    
    for (; it != parent->children.end(); it++) {
        // Child nodes are stored on the parent node in a map of integers
        // (it->first) to Node pointers (it->second).
        Node* child_node = it->second;
        buffer << parent->ID << "->" << child_node->ID << " [label = \""
        << get_substr(child_node->begin_index, *(child_node->end_index))
        << "\"];\n" << log_node(child_node);
    }
    
    // Print the suffx link, if there is one.
    Node* suffix_link = parent->suffix_link;
    if (suffix_link)
        buffer << "\"" << parent->ID << "\" -> " << "\""
        << suffix_link->ID << "\" [style=dashed arrowhead=otriangle];\n";
    
    return buffer.str();
}


void SuffixTree::loop(Node* v,int lower_bound,unsigned int upper_bound, bool multiple)
{
    v->breath=v->edge_length()+v->parent->breath;
    
    if(v->is_leaf())
        v->res_A.insert(length - v->breath);
    else
    {
        for (map<int, Node*>::iterator it = v->children.begin(); it!=v->children.end(); it++)
        {
            v->labels.push_back(it->first);
            if (it->second->res_A.empty())
                loop(it->second,lower_bound,upper_bound,multiple);

            for (int i : it->second->res_A)
                v->res_A.insert(i);
        }
        
        if(v->breath>=lower_bound && v->breath<=upper_bound )
        {
            set<pair< pair<int,int>, pair<int,int> > > tmp;
            for(int k = 0; k < v->labels.size();k++)
                for(int l = k+1; l < v->labels.size(); l++)
                {
                    Node* v_f = v->children[v->labels[k]];
                    Node* v_g = v->children[v->labels[l]];
                    
                    
                    if(!v_f->res_A.empty() && !v_g->res_A.empty())
                    {
                        for( int i : v_f->res_A)
                            for( int j : v_g->res_A)
                            {
                                if (tree_string[i-1]!=tree_string[j-1])
                                {
                                    pair< pair<int,int>, pair<int,int>> p = make_pair( make_pair(j, j+v->breath-1), make_pair(i, i+v->breath-1));
                                    if(multiple)
                                    {
                                        for(map<string,int>::iterator lg = lg_map.begin() ; lg != lg_map.end() ; lg++)
                                            if ( ( p.first.first <= lg->second && p.second.first > lg->second) || ( p.first.first > lg->second && p.second.first <= lg->second ) )
                                                tmp.insert(p);
                                    }
                                    else
                                        tmp.insert(p);
                                }
                            }
                    }
                }
            
            if(!(tmp.empty()))
            {
                cout << "\n\e[4mRepeat string :\e[0m";
                set<pair< pair<int,int>, pair<int,int>> >::iterator it = tmp.begin();
                for(int i=it->first.first; i<=it->first.second; i++)
                    cout<< tree_string[i];
                cout<<endl;
                
                cout << "  - \e[3mLength of the repeat string\e[0m : " << v->breath<< endl;
                cout << "  - \e[3mOccurences (including repeats in a same file)\e[0m: " << v->size()<<endl;
                
                if(multiple)
                {
                    set<string> tmp2;
                    cout << "  - \e[3mInside these files\e[0m : " << endl;
                    int val = 0;
                    for(map<string,int>::iterator lg = lg_map.begin() ; lg != lg_map.end() ; lg++)
                    {
                        for(pair< pair<int,int>, pair<int,int>> p : tmp)
                        {
                            if ( p.first.first <= lg->second && p.first.first >= val )
                                tmp2.insert(lg->first);
                            
                            if ( p.second.first <= lg->second && p.second.first >= val )
                                tmp2.insert(lg->first);
                        }
                        val = lg->second;
                    }
                    
                    for( string f : tmp2)
                        cout << "      - "<< f << endl;
                    
                    cout<<"\n"<<endl;
                    
                    
                }
            }
            
            
        }
    }
}


void SuffixTree::repeat(const char* name_file, int lower_bound,unsigned int upper_bound, bool multiple)
{
    ifstream is(name_file);
    
    clock_t time = clock();
    
    if (is.good())
    {
        string tmp( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));
        
        construct(tmp);
        cout << "Time construct : " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
        
        map<int, Node*>::iterator it = root->children.begin();
        
        
        for (; it!=root->children.end(); it++)
            loop(it->second, lower_bound,upper_bound,multiple);
    }
    is.close();
    
}

void SuffixTree::compare(set<string> files,int lower_bound,unsigned int upper_bound)
{
    ofstream merge(TMP_FILE, ios_base::binary);
    
    clock_t time = clock();
    double lg = 0;
    int id = 0;
    for (string f : files)
    {
        ifstream tmp(f, ios_base::binary);
        if (tmp.good())
            merge << tmp.rdbuf() << "\n$id$:" << id++ << endl;
        lg += tmp.tellg();
        lg_map.insert(make_pair(f,lg));
        if (lg_max <= tmp.tellg())
            lg_max = tmp.tellg();
        tmp.close();
    }
    cout << "Time concat : " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
    merge.close();
    
    repeat(TMP_FILE,lower_bound,true);
}
