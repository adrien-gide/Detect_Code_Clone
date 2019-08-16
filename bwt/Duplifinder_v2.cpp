
//
//  Duplifinder_v2.cpp
//
//
//  Created by Adrien Gide on 2019/08/08.
//
//
#include "Duplifinder_v2.hpp"

using namespace std;


void Duplifinder_v2::repeat(const char* name_file, int ml, int mo, bool multiple)
{
    ifstream is(name_file);

    mocc = mo;
    mlength = ml;

    if (is)
    {
        string s( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));
//        string s = "mississi$ppi";

        
        construct_im(csa,s ,1);     //Construction of a Compressed Suffix Array (CSA) in order to get the Burrow's and Wheeler's Transform (BWT) in an efficient time
        
        
//        cout << " i SA ISA  LF BWT   T[SA[i]..SA[i]-1]" << endl;
//        csXprintf(cout, "%2I %2S %3s %2p %3B   %:3T", csa);

        cout << endl;


        for(int i=0; i<=s.size();i++)
        {
            if (s[i] != '$')
                bwt.push_back(csa.bwt[i]);
            else if (0 == csa.bwt[i])
                bwt.push_back('$');

            str.push_back(s[i]);
        }

//        cout << str << endl;
//        cout << bwt << endl
//        cout << csa.bwt << endl;

        
        wt = new WaveletTree(bwt);

        occus = wt->occus;
        
        cout << "Time bwt : " << clock() / (double) CLOCKS_PER_SEC << " second(s) "<< endl;
        cout <<endl;
        
        int n = str.size();
        bit.resize(n+1);

        bit[0] = 1;

        bit[n] = 1;

     

        int limit = occus.size()-1;


        auto end = occus.end();
        --end;
        

        for(WaveletTree::occu_type::iterator it=occus.begin(); it!=end; it++)
        {
            stocker_t st;

            if(limit>0)
            {

                auto nx = next(it,1);

                string tt;

                tt.push_back(it->first);

                auto p = make_pair(it->second.second+1, nx->second.second);

                res.insert(make_pair(tt,p));

                st.push(make_pair(tt,p));
                limit--;
            }
            
            m_queue.insert(make_pair(it->first,st));
        }




        int last_lb=-1, last_idx=-1, l = 0;
        bool locMax = true;
        long size;
        
        

        bool nonempty = true;

        while(nonempty)
        {
            map<char,int> szs;
            for (map_queue::iterator it=m_queue.begin(); it!=m_queue.end();it++)
                if (!it->second.empty())
                    szs.insert(make_pair(it->first,it->second.size()));
            
            if (!szs.empty())
            {
                for(pair<char,int> p : szs)
                {
                        char c = p.first;
                        size = p.second;
                    while (size > 0)
                    {
                        
                        pair<string,pair<long,long> > obj = m_queue[c].front();
                        
                        pair<long,long> inter = obj.second;
                        m_queue[c].pop();
                        size--;
                        if( bit[inter.second] == 0)
                        {
                            bit[inter.second] = 1;
                            if(last_lb==-1)
                                last_lb=inter.first;
                            last_idx=inter.second+1;
                            if(inter.second != inter.first)
                                locMax=false;
                            stt lit;
                            getIntervals(inter,lit);

                            while(!lit.empty())
                            {
                                pair<char,pair<long,long> > tmp = lit.top();
                                string ttt;
                                ttt.push_back(tmp.first);
                                for (int i=0; i<obj.first.size(); i++)
                                    ttt.push_back(obj.first[i]);
                                
                                res.insert(make_pair(ttt,tmp.second));
                                m_queue[tmp.first].push(make_pair(ttt,tmp.second));
                                lit.pop();
                            }
                        }
                        else if (last_idx == inter.first)
                        {
                            if(inter.second != inter.first)
                                locMax=false;
                            
                            auto p_proc = make_pair(obj.first,make_pair(last_lb, obj.second.second));
                            process(l, p_proc, locMax);
                            last_lb = -1;
                            last_idx = -1;
                            locMax = true;
                            stt list;
                            getIntervals(inter,list);

                            while(!list.empty())
                            {
                                pair<char,pair<long,long> > tmp = list.top();
                                string ttt;
                                ttt.push_back(tmp.first);
                                for (int i=0; i<obj.first.size(); i++)
                                    ttt.push_back(obj.first[i]);

                                res.insert(make_pair(ttt,tmp.second));
                                
                                m_queue[tmp.first].push(make_pair(ttt,tmp.second));
                                list.pop();
                                
                            }
                        }
                    }
                }
                
            }
            else
            {
                nonempty=false;
            }
            l++;

        }
        cout<<endl;

    }
    is.close();
    

//    for(pairs_t::iterator it=res.begin(); it!=res.end(); it++)
//        cout << it->first << " - (" << it->first.size()<<")"<<endl;
//    cout<<endl;
//    cout<<endl;

}

void Duplifinder_v2::process(int l, pair<string,pair<long,long> > p, bool locMax)
{
    auto inter = p.second;
//
//    cout << " l  " << l <<  "  - (" << inter.first << "," << inter.second << ")"<<endl;
//    cout << mlength << ", " << mocc << endl;
    
    if( l >= mlength && (inter.second - inter.first + 1) >= mocc)
//    if( l >= mlength)
    {
        auto end =occus.end();
        --end;
        --end;

//        cout << "      rank  : " << rank(1 ,inster.second) -rank(1,inter.first) << endl;
//        if (rank(inter.second) -rank(inter.first) > 0)
//        {
        
        if(locMax && superMax(p))
        {
            cout << "\n\e[4mSupermaximal repeat :\e[0m";
            for (int i=0; i<p.first.size()-1; i++)
                cout << p.first[i];
            cout << endl;
            
            cout << "  - \e[3mLength of the repeat string\e[0m : " << p.first.size()-1<< endl;
            cout << "  - \e[3mOccurences (including repeats in a same file)\e[0m: " << inter.second - inter.first + 1<<endl;
            
            cout << endl;


        }
        else if (rank(inter.second) -rank(inter.first) > 0)
        {
            cout << "\n\e[4mMaximal repeat :\e[0m";
            for (int i=0; i<p.first.size()-1; i++)
                cout << p.first[i];
            cout << endl;

            cout << "  - \e[3mLength of the repeat string\e[0m : " << p.first.size()-1<< endl;
            cout << "  - \e[3mOccurences (including repeats in a same file)\e[0m: " << inter.second - inter.first + 1<<endl;
            
            cout << endl;

        }

        
    }
}

int Duplifinder_v2::rank(int limit)
{
    sdsl::rank_support_v<1> b_rank(&bit_bwt);
    
    return b_rank(limit);
}

void Duplifinder_v2::getIntervals(pair<long,long> pair, stt &li)
{
    auto end =occus.end();
    --end;
    --end;

    getinter(pair,make_pair(occus.begin()->second.first,end->second.first) ,li);

}

void Duplifinder_v2::getinter(pair<long,long> i_j, pair<int,int> l_r, stt &list)
{

//     cout << "( "<< i_j.first << " ::  " << i_j.second << " )" <<endl;
    if(l_r.first== l_r.second )
    {
//        auto it = occus.find(str[l_r.first]);

        auto tmp = next(occus.begin(),l_r.first-1);

        char c = tmp->first;
        
//        cout << "    c:"<< c << endl;
//
//        cout << "      "<< occus[c].second + i_j.first << " :: " << occus[c].second + i_j.second << endl;
        if (c != '$')
            list.push(make_pair(c,make_pair(occus[c].second + i_j.first, occus[c].second + i_j.second)) );
    }
    else
    {
//        cout << " "<< l_r.first << " ::  " << l_r.second << endl;
        
        int m = (l_r.first + l_r.second)/2 ;

        pair<long,long> a0 = make_pair(wt->tree[l_r]->rank(0,i_j.first-1),wt->tree[l_r]->rank(0,i_j.second) );
        
        
        
        pair<long,long> a1 = make_pair(i_j.first-1-a0.first, i_j.second - a0.second);
//
//        cout << "       a0  "<< a0.first << " ::  " << a0.second << "  b0"<< endl;
//        cout << "       a1  "<< a1.first << " ::  " << a1.second << "  b1"<< endl;

//        cout <<" m " << m<<endl;

        if(a0.second > a0.first)
            getinter(make_pair(a0.first + 1, a0.second), make_pair(l_r.first,m), list);
        if(a1.second > a1.first)
            getinter(make_pair(a1.first + 1, a1.second), make_pair(m+1,l_r.second),list);
    }
}

bool Duplifinder_v2::superMax(pair<string,pair<long,long> > p)
{
    bool pd = true;
    stt lit;
    getIntervals(p.second, lit);
    
    while(!lit.empty())
    {
        if(lit.top().second.first != lit.top().second.second)
            {
                pd = false;
            }
        lit.pop();
    }

//    if (lit.size() == 1)
//        pd=false;
    
    return pd;
}


int Duplifinder_v2::rank( bool search, pair<int ,int> bounds, int limit)
{
//    cout << "  b1 " << bounds.first << " b2 " << bounds.second << " limit " << limit << endl;

    string tmp;
    for (int i = 0; i<bwt.size();i++)
        if(occus.find(bwt[i])!=occus.end())
            if ( occus[bwt[i]].first <= bounds.second && occus[bwt[i]].first >=  bounds.first && occus[bwt[i]].first < occus.size())
                tmp.push_back(bwt[i]);


//    for (int i = 0; i<limit;i++)
//        cout << tmp[i];
//    cout<<endl;

    int cpt=0;

    int m = (bounds.first + bounds.second)/2;

    if(!search)
    {
        for (int i = 0; i<limit;i++)
            if(occus[tmp[i]].first <= m && limit >=0)
                cpt++;
    }
    else
        for (int i = 0; i<limit;i++)
            if(occus[tmp[i]].first > m && limit >=0)
                cpt++;
//    cout << "   cpt : "<<cpt<<"   m: " << m<<endl << endl;


    return cpt;
}

void Duplifinder_v2::init_bwt()
{

    vector<string> table;
    int size = str.size();
    table.resize(size);
    
    cout<<size<<endl;
    
    cout << "Time  start : " << clock()/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;

    string tmp;
    for (int i=0; i<size; i++)
    {
        cout<<i<<endl;

        for(int j=0; j<size; j++)
            table[i].push_back(str[(i+j) % size]);
    }
    
    cout << "Time init : " << clock() / (double) CLOCKS_PER_SEC << " second(s)"<< endl;

    sort(table.begin(),table.end(),[](string a, string b){return a<b;} );

    bit_bwt.resize(size);
    
    auto c = table[0][size-1];
    for(int i=0; i<size;i++)
    {
        if(table[i][size-1]!=c)
            bit_bwt[i] = 1;
        else
            bit_bwt[i] = 0;

        c = table[i][size-1];
        bwt.push_back(c);
    }
    bit_bwt[0] = 1;

}

void Duplifinder_v2::compare(set<string> files, unsigned int min_length,unsigned int min_occ)
{
    ofstream merge(TMP_FILE3, ios_base::binary);

    for (string f : files)
    {
        ifstream tmp(f, ios_base::binary);
        if (tmp.good())
            merge << tmp.rdbuf();
        tmp.close();
    }
    cout << "Time concat : " <<  clock()/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
    merge.close();
    mult = true;
    repeat(TMP_FILE3, min_length,min_occ);
}
