/**
 *
 * Duplifinder.hpp
 * Created by Adrien Gide on 2019/06/28.
 */

#ifndef Duplifinder_hpp
#define Duplifinder_hpp
#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <sdsl/suffix_arrays.hpp>
#include <sdsl/suffix_trees.hpp>
#include <sdsl/rmq_support_sparse_table.hpp>
#include <stack>
#include <utility>
#include <iterator>
#include <queue>

typedef sdsl::csa_wt<sdsl::wt_huff<sdsl::rrr_vector<63> > > csa_t;
typedef sdsl::cst_sada<csa_t> cst_t;


class Duplifinder
{
public:
    typedef std::queue<std::pair<std::string,std::pair<long,long> > > stocker_t;
    typedef std::map<char, stocker_t > map_queue;
    typedef std::map<char,std::pair<int,long> > occu_type;
    typedef std::map< std::string,std::pair<long, long>> pairs_t;
    typedef std::stack<std::pair<char,std::pair<long,long> > > stt;
    
public:
    cst_t cst;
    map_queue m_queue;
    occu_type occus;
    std::vector<int> bit;
    int mlength;
    int mocc;
    std::string str;
    pairs_t res;
    std::string bwt;
//    std::vector<int> lcp_array;
    
public:
     void repeat(const char* name_file,int m=254, bool multiple=false, int ml=2, int mo=2);
    
private:
//    void lcp_construct(std::string &str,int m);
    void fill_occus(std::string &str);
    void getinter(std::pair<long,long> i_j, std::pair<int,int> l_r, stt &st);
    void getIntervals(std::pair<long,long> pair, stt &li);
    void process(int l, std::pair<std::string,std::pair<long,long> > p, bool loc);
    bool superMax(std::pair<std::string,std::pair<long,long> > p);
    int rank( bool search, std::pair<int,int> bounds,int limit);
    void init_bwt();
};

#endif /* Duplifinder_hpp */
