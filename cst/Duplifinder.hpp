//
//  Duplifinder.hpp
//  
//
//  Created by Adrien Gide on 2019/05/21.
//

#ifndef Duplifinder_hpp
#define Duplifinder_hpp
#pragma once

#define TMP_FILE2 "tmp.txt"

#include <stdio.h>
#include <iostream>
#include <sdsl/suffix_trees.hpp>
#include <vector>
#include <string>


//typedef sdsl::cst_sct3<> cst_t;
typedef sdsl::cst_sada<> cst_t;


class Duplifinder : public cst_t
{
public:
    typedef sdsl::cst_bfs_iterator<cst_t> iterator;
    typedef std::unordered_map<size_type, std::set<int> > pos_type;
    typedef std::unordered_map<size_type, std::set<std::pair< std::pair<int,int>, std::pair<int,int>> > > results_type;

private:
    
    cst_t cst;
    int position;
    pos_type map_pos;
    results_type results_array;
    std::string origin;
    std::map<std::string,int> lg_map;
    bool mult = false;
    int lg_max = 0;
    
public:
    /**
     * \brief Main fonction for the detection of code clone.
     *
     * This will create a compressed suffix tree for the file we want to test. It will also traverse it in order to find the repeats on the file.
     * \param lower_bound Minimum length for the repeat
     * \param multple Indicate if we have multiple files
     */
    void repeat(const char* name_file,unsigned int lower_bound=2,unsigned int upper_bound=500, bool multiple=false);

    /**
     * \brief Display function
     *
     * Printing the results corresponding to the pairs found by the function repeat.
     * \see repeat
     */
    void printlist();
    
    /**
     * \brief Compare multiple files.
     *
     * Compare multiple files by concatenate them and pass the concatenated file at the function repeat.
     * \param files Set with the names of the files we want to compare
     * \param lower_bound Minimum length for the repeat
     * \see repeat
     */
    void compare(std::set<std::string> files, unsigned int lower_bound=2, unsigned int upper_bound=500);
    
private:
    /**
     * \brief Principal function for positions of each node.
     *
     * Will use the function get_i to match a pair (character, position) with a node. A leaf will only have one pair, a node can have multiple pairs.
     * It will be equivalent to the number of leaves under this node.
     * \see get_i
     */
    
    void A(node_type v);
    
    /**
     * \brief Supplying function for positions of each node.
     *
     * It will get the start position of the suffix corresponding at each node and the character before.
     * \see A
     */
    bool get_i(node_type v);
};


#endif /* Duplifinder_hpp */
