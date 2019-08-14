
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
//        string str( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));
//
//        string str("el_anele_lepanelen");
//        for (int i=0; i<str.size();i++)
    
//            if (str[i]=='\n')
//                str[i] = '#';
    if (is)
    {
//        clock_t time = clock();
//        construct(cst, name_file,1);
//
//
        string s( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));
//
//        string s = "mississi$ppi";

        construct_im(csa,s ,1);
//        cout << " i SA ISA  LF BWT   T[SA[i]..SA[i]-1]" << endl;
//        csXprintf(cout, "%2I %2S %3s %2p %3B   %:3T", csa);

//        init_bwt();
        cout << endl;


        for(int i=0; i<=s.size();i++)
        {
//            const char* tp = s[i];
//            cout << s[i] << endl;
//            cout << tp[0] << endl;
//            char dol = '$';
//            const char * dollar = &dol;
            
            if (s[i] != '$')
                bwt.push_back(csa.bwt[i]);
            else if (0 == csa.bwt[i])
                bwt.push_back('$');
//            else
//                bwt.push_back(csa.bwt[i]);

            str.push_back(s[i]);
        }

//        cout << s << endl;
//        cout << str << endl;
//        cout << bwt << endl;
        
        
        wt = new WaveletTree(bwt);

        occus = wt->occus;
        
//        fill_occus(bwt);
        cout << "Time bwt : " << clock() / (double) CLOCKS_PER_SEC << " second(s) "<< endl;

//        cout << csa.bwt << endl;
//        cout <<bwt<<endl;
        
//        for(int i=0; i<120;i++)
//        {
//            cout << csa.bwt[i];
//            i+=s.size()-1;
//        }
        cout <<endl;
        
        int n = str.size();
        bit.resize(n+1);

        bit[0] = 1;

        bit[n] = 1;

     

        int limit = occus.size()-1;


        auto end = occus.end();
        --end;
        
//        cout << "start " << endl;

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


//        cout << "hey"<<endl;


        int last_lb=-1, last_idx=-1, l = 0;
        bool locMax = true;
        long size;
        
        

        bool nonempty = true;

        while(nonempty)
        {
//            cout << "no"<<endl;
//            cout << "---------------------------------------------------------" <<endl;
//            cout << "step ---> " << l << endl;
            
//            vector<pair<char,int> > szs;
            map<char,int> szs;
            for (map_queue::iterator it=m_queue.begin(); it!=m_queue.end();it++)
                if (!it->second.empty())
//                    szs.push_back(make_pair(it->first,it->second.size()));
                    szs.insert(make_pair(it->first,it->second.size()));
            
            if (!szs.empty())
            {
                for(pair<char,int> p : szs)
                {
                        char c = p.first;
                        size = p.second;
//                    cout << "size " <<size<<endl;

    //                    for (pair <char, queue<pair<long,long> > > p : m_queue)
                    //                        size.insert(make_pair(p.first,p.second.size()));
                    //
                    //
                    //                    for (pair<char, long> p : size)
                    //                    {
                    while (size > 0)
                    {
                        
                        pair<string,pair<long,long> > obj = m_queue[c].front();
                        
//                        cout << " - " << obj.first<< endl;
                        
                        pair<long,long> inter = obj.second;
//                        cout << "  - (" << inter.first << "," << inter.second << ")"<<endl;
                        m_queue[c].pop();
                        size--;
                        
//                        cout << " last_idx "<< last_idx<<endl;
//                        cout << " lb "<< inter.first<< " - rb+1 "  << inter.second+1<< endl;
//
//                        cout << " bit[rb+1]  "<< bit[inter.second]<<endl;
                        if( bit[inter.second] == 0)
                        {
//                            cout << "   case 1"<<endl;

//
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
//                                cout << "  tmp pair: " << tmp.second.first << " : "<< tmp.second.second << endl;
                                string ttt;
                                ttt.push_back(tmp.first);
                                for (int i=0; i<obj.first.size(); i++)
                                    ttt.push_back(obj.first[i]);
//                                cout << "   - size : " << ttt.size() << " str : ";
//                                for (int y =0;y<ttt.size();y++)
//                                    cout<< ttt[y];
//                                cout  << endl;
                                res.insert(make_pair(ttt,tmp.second));
                                m_queue[tmp.first].push(make_pair(ttt,tmp.second));
                                lit.pop();
                            }
                        }
                        else if (last_idx == inter.first)
                        {
//                            cout << "   case 2"<<endl;

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
//                            cout << "  tmp pair: " << tmp.second.first << " : "<< tmp.second.second << endl;
                                string ttt;
                                ttt.push_back(tmp.first);
                                for (int i=0; i<obj.first.size(); i++)
                                    ttt.push_back(obj.first[i]);
//                                cout << "   - size : " << ttt.size() << " str : ";
//                                for (int y =0;y<ttt.size();y++)
//                                    cout<< ttt[y];
//                                cout  << endl;
                                res.insert(make_pair(ttt,tmp.second));
                                
                                m_queue[tmp.first].push(make_pair(ttt,tmp.second));
                                list.pop();
                                
                            }
                        }
//                        else
//                            cout << "   case 3 "<<endl;
            

                        
                    }
                    //                    }
//                    cout <<endl;
                }
                
            }
            else
            {
                nonempty=false;
            }
            l++;
//            cout << " end " << endl;

//            cout << "---------------------------------------------------------" <<endl;

        }
        cout<<endl;

    }
    is.close();
    

//    for(pairs_t::iterator it=res.begin(); it!=res.end(); it++)
//        cout << it->first << " - (" << it->first.size()<<")"<<endl;
//    cout<<endl;
//    cout<<endl;

//    cout << bwt << endl;
//    for( int i : bit_bwt)
//        cout << i << ", ";
//    cout <<endl;


//    for(pairs_t::iterator it=res.begin(); it!=res.end(); it++)
//        if(it->first.size()>=mlength && it->second.second - it->second.first + 1 > 0 )
//            process(it->first.size(),*it,false);

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
            
//            if(multiple)
//            {
//                set<string> tmp2;
//                cout << "  - \e[3mInside these files\e[0m : " << endl;
//                int val = 0;
//                for(map<string,int>::iterator lg = lg_map.begin() ; lg != lg_map.end() ; lg++)
//                {
//                    for(pair< pair<int,int>, pair<int,int>> p : tmp)
//                    {
//                        if ( p.first.first <= lg->second && p.first.first >= val )
//                            tmp2.insert(lg->first);
//
//                        if ( p.second.first <= lg->second && p.second.first >= val )
//                            tmp2.insert(lg->first);
//                    }
//                    val = lg->second;
//                }
//
//                for( string f : tmp2)
//                    cout << "      - "<< f << endl;
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
            
            //            if(multiple)
            //            {
            //                set<string> tmp2;
            //                cout << "  - \e[3mInside these files\e[0m : " << endl;
            //                int val = 0;
            //                for(map<string,int>::iterator lg = lg_map.begin() ; lg != lg_map.end() ; lg++)
            //                {
            //                    for(pair< pair<int,int>, pair<int,int>> p : tmp)
            //                    {
            //                        if ( p.first.first <= lg->second && p.first.first >= val )
            //                            tmp2.insert(lg->first);
            //
            //                        if ( p.second.first <= lg->second && p.second.first >= val )
            //                            tmp2.insert(lg->first);
            //                    }
            //                    val = lg->second;
            //                }
            //
            //                for( string f : tmp2)
            //                    cout << "      - "<< f << endl;
            cout << endl;

        }
//        }
//        if (locMax && superMax(p))
//            cout << "   " << p.first << " -[" << inter.first << " .. " << inter.second << "] is a supermaximal repeat" << endl;

        
    }
}

int Duplifinder_v2::rank(int limit)
{
    sdsl::rank_support_v<1> b_rank(&bit_bwt);
    
    return b_rank(limit);
}


//void Duplifinder_v2::fill_occus(string &str)
//{
//    occu_type::iterator it;
//
//    for(int i = 0; i < str.size(); i++)
//    {
//        it = occus.find(str[i]);
//
//        if (it == occus.end())
//        {
////            int size = occus.size();
//            occus.insert(make_pair(str[i],make_pair(0,1)));
//        }
//        else
//            it->second.second++;
//    }
//
//    int sum=0;
//    int tmp;
//    int i=1;
//    for(occu_type::iterator o=occus.begin(); o != occus.end(); o++)
//    {
//        o->second.first = i++;
//        tmp = o->second.second;
//        o->second.second=sum;
//        sum+=tmp;
//        cout << o->first << " ->  (" << o->second.first<< ", "<< o->second.second << ")  " << endl;
//    }
////    int size = occus.size();
//    occus.insert(make_pair('~',make_pair(occus.size()+1,sum)));
//}

void Duplifinder_v2::getIntervals(pair<long,long> pair, stt &li)
{
    auto end =occus.end();
    --end;
    --end;

    getinter(pair,make_pair(occus.begin()->second.first,end->second.first) ,li);

//    while(!li.empty())
//    {
//        std::pair<char, std::pair<long, long> > it = li.top();
//        cout << "  "<< it.first << " :: " << it.second.first<<"," <<it.second.second << endl;
//        li.pop();
//    }
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

//        pair<long,long> a0 = make_pair(rank(false,l_r,i_j.first-1), rank(false,l_r,i_j.second) );
        
        int m = (l_r.first + l_r.second)/2 ;


//        long x1=0, x2=0;
//        for(int i=l_r.first; i<m; i++)
//        {
//            auto x = next(occus.begin(),l_r.first-1);
//
//            x1+=wt.rank(i_j.first-1,x->first);
//            x2+=wt.rank(i_j.second,x->first);
//        }
//
//        pair<long,long> a0 = make_pair(x1,x2);
//
//
        pair<long,long> a0 = make_pair(wt->tree[l_r]->rank(0,i_j.first-1),wt->tree[l_r]->rank(0,i_j.second) );
        
        
        
        pair<long,long> a1 = make_pair(i_j.first-1-a0.first, i_j.second - a0.second);
//
//        cout << "       a0  "<< a0.first << " ::  " << a0.second << "  b0"<< endl;
//        cout << "       a1  "<< a1.first << " ::  " << a1.second << "  b1"<< endl;


//        auto b1 = next(occus.begin(),l_r.first-1);
//        auto b2 = next(occus.begin(),l_r.second-1);



//        cout <<" m " << m<<endl;

        if(a0.second > a0.first)
        {
//            cout <<"  a0 "<<a0.first << "  " <<  a0.second<<endl;
//            cout <<"  l "<<l_r.first << " / r " <<  m<<endl;


            getinter(make_pair(a0.first + 1, a0.second), make_pair(l_r.first,m), list);
        }
        if(a1.second > a1.first)
        {
//            cout <<"   a1 "<<a1.first << " " <<  a1.second<<endl;
//            cout <<"   l "<<m+1 << " / r " <<  l_r.second<<endl;


            getinter(make_pair(a1.first + 1, a1.second), make_pair(m+1,l_r.second),list);
        }
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


//    auto b1 = next(occus.begin(),bounds.first-1);
//    auto b2 = next(occus.begin(),bounds.second-1);
//
//    cout << "   b1 " << b1->second.first << " b2 " << b2->second.first << endl;

    string tmp;
    for (int i = 0; i<bwt.size();i++)
        if(occus.find(bwt[i])!=occus.end())
            if ( occus[bwt[i]].first <= bounds.second && occus[bwt[i]].first >=  bounds.first && occus[bwt[i]].first < occus.size())
                tmp.push_back(bwt[i]);

//
//    for(occu_type::iterator o=occus.begin(); o != occus.end(); o++)
//        cout << o->first << " ->  (" << o->second.first<< ", "<< o->second.second << ")  " << endl;

//    for (int i = 0; i<limit;i++)
//        cout << tmp[i];
//    cout<<endl;

    int cpt=0;
//    int m = (b1->second.first + b2->second.first)/2;

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

//string t, int n, int k
void Duplifinder_v2::init_bwt()
{
//    clock_t time = clock();

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
        {
//            cout<<"  "<<j<<endl;

            table[i].push_back(str[(i+j) % size]);
//        sort(table.begin(),table.end(),[](string a, string b){return a>b;} );
        }
    }
    
    cout << "Time init : " << clock() / (double) CLOCKS_PER_SEC << " second(s) "<< endl;

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
//    clock_t time =clock();

    double lg = 0;
    int id = 0;
    for (string f : files)
    {
        ifstream tmp(f, ios_base::binary);
        if (tmp.good())
        {

            merge << tmp.rdbuf();
//            lg += tmp.tellg();
//            lg_map.insert(make_pair(f,lg));
//            if (lg_max <= tmp.tellg())
//                lg_max = tmp.tellg();
        }
        tmp.close();
    }
    cout << "Time concat : " <<  clock()/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
    merge.close();
    mult = true;
    repeat(TMP_FILE3, min_length);
}
