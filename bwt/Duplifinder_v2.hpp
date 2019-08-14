/**
 *
 * Duplifinder_v2.hpp
 * Created by Adrien Gide on 2019/08/08.
 */

#ifndef Duplifinder_v2_hpp
#define Duplifinder_v2_hpp
#pragma once

#define TMP_FILE3 "tmp3.txt"


#include <iostream>
#include <vector>
#include <map>
#include <sdsl/suffix_arrays.hpp>
#include <stack>
#include <iterator>
#include <queue>
#include <boost/filesystem.hpp>
#include <stdio.h>

#include "WaveletTree.hpp"

//sdsl::int_vector<1>,sdsl::rank_support_v<0,1> 
typedef sdsl::wt_huff<sdsl::int_vector<1>,sdsl::rank_support_v<0> > wt_t;
typedef sdsl::csa_wt<> csa_t;

class WaveletTree;

class Duplifinder_v2
{
    friend class WaveletTree;
    
public:
    typedef std::queue<std::pair<std::string,std::pair<long,long> > > stocker_t;
    typedef std::map<char, stocker_t > map_queue;
    typedef std::map< std::string,std::pair<long, long>> pairs_t;
    typedef std::stack<std::pair<char,std::pair<long,long> > > stt;
    
public:
    WaveletTree *wt;
    csa_t csa;
    map_queue m_queue;
    std::vector<int> bit;
    int mlength;
    int mocc;
    std::string str;
    pairs_t res;
    std::string bwt;
    sdsl::bit_vector bit_bwt;
//    std::map<std::string,int> lg_map;
    bool mult = false;
    int lg_max = 0;
    WaveletTree::occu_type occus;
    
public:
    void repeat(const char* name_file, int ml=2, int mo=2,bool multiple=false);
    void compare(std::set<std::string> files, unsigned int min_lgth=2, unsigned int min_occ=500);

    
private:
//    void fill_occus(std::string &);
    void getinter(std::pair<long,long> , std::pair<int,int> , stt &);
    void getIntervals(std::pair<long,long> , stt &);
    void process(int , std::pair<std::string,std::pair<long,long> > , bool );
    bool superMax(std::pair<std::string,std::pair<long,long> > );
    int rank( bool , std::pair<int,int> ,int );
    int rank(int );
    void init_bwt();


};

#endif /* Duplifinder_v2_hpp */
