
//
//  Duplifinder.cpp
//
//
//  Created by Adrien Gide on 2019/06/28.
//
//
#include "Duplifinder.hpp"

using namespace std;

//void Duplifinder::repeat(const char* name_file,int m, bool multiple, int ml, int mo)
//{
//    ifstream is(name_file);
//
//    mocc = mo;
//    mlength = ml;
//
//    if (is.good())
//    {
//        clock_t time = clock();
//
////        construct(cst, name_file,1);
//////        cout << " i SA ISA  LF BWT   T[SA[i]..SA[i]-1]" << endl;
//////        csXprintf(cout, "%2I %2S %3s %2p %3B   %:3T", csa);
////
////        string s( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));
//
//
//        string s = "mississippi$";
//        contruct_im(cst,s,1);
//
//        str = s;
//        int n = str.size();
//
//        bit.resize(n);
//
//
//    }
//}


void Duplifinder::repeat(const char* name_file,int m, bool multiple, int ml, int mo)
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
    if (is.good())
    {
        clock_t time = clock();
//        construct(cst, name_file,1);
////        cout << " i SA ISA  LF BWT   T[SA[i]..SA[i]-1]" << endl;
////        csXprintf(cout, "%2I %2S %3s %2p %3B   %:3T", csa);
//
//        string s( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));

        string s = "mississippi$";
        construct_im(cst, s,1);

        cout << " Time tree construction : " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;

        str = s;
        init_bwt();

        int n = str.size();

        bit.resize(n+1);

        bit[1] = 1;

        bit[n+1] = 1;

        fill_occus(str);

        int limit = occus.size()-1;
        cout << "limit "<<limit << endl;
//        for (char i=0; i<127;i++)
//        {
//            stack<pair<long,long> > st;
//
//            auto it = occus.find(i);
//            if(it!=occus.end() && limit>0)
//            {
//                cout << i << " :: " << occus.at(i) << endl;
//
//                auto nx = it;
//                advance(nx,1);
//
//                st.push(make_pair(it->second+1, nx->second));
//                nonempty++;
//                limit--;
//            }
//
//            m_queue.insert(make_pair(str[i],st));
//        }

        auto end = occus.end();
        --end;

        for(occu_type::iterator it=occus.begin(); it!=end; it++)
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

//            cout << "st: "<< st.top().first << " :: "<  st.top().second<<endl;
            m_queue.insert(make_pair(it->first,st));
        }

        cout << "m_queue  size "<< m_queue.size()<<endl;


//        map_queue::iterator it;

//        for(it=m_queue.begin(); it!=m_queue.end(); it++)
//            if(!it->second.empty() )
//                                cout << it->first << " :: " << it->second.top().first<<"," <<it->second.top().second << endl;
//            cout<<it->first<< " ::    " <<it->second.size()<<endl;
//        cout << "hey"<<endl;


        int last_lb=-1, last_idx=-1, l = 1;
        bool locMax = true;
        long size;
        
        

        bool nonempty = true;

        while(nonempty)
        {
//            cout << "no"<<endl;
            cout << "---------------------------------------------------------" <<endl;
            cout << "step ---> " << l << endl;
            
            vector<pair<char,int> > szs;
            for (map_queue::iterator it=m_queue.begin(); it!=m_queue.end();it++)
                if (!it->second.empty())
                    szs.push_back(make_pair(it->first,it->second.size()));
            
            if (!szs.empty)
                
                for(pair<char,int> p : szs)
                {
                        char c = p.first;
                        size = p.second;
                    cout << "size " <<size<<endl;

    //                    for (pair <char, queue<pair<long,long> > > p : m_queue)
                    //                        size.insert(make_pair(p.first,p.second.size()));
                    //
                    //
                    //                    for (pair<char, long> p : size)
                    //                    {
                    while (size > 0)
                    {
                        cout << " - cond"<< endl;
                        
                        pair<string,pair<long,long> > obj = m_queue[c].front();
                        
                        cout << " - " << obj.first<< endl;
                        
                        pair<long,long> inter = obj.second;
                        cout << " - (" << inter.first << "," << inter.second << ")"<<endl;
                        m_queue[c].pop();
                        size--;
                        
                        if( bit[inter.second+1] == 0)
                        {
                            cout << " case 1"<<endl;
                            bit[inter.second+1] = 1;
                            if(inter.second != inter.first)
                                locMax=false;
                            if(last_lb==-1)
                                last_lb=inter.first;
                            last_idx=inter.second+1;
                            
                            stt lit;
                            getIntervals(inter,lit);
                            
                            while(!lit.empty())
                            {
                                pair<char,pair<long,long> > tmp = lit.top();
                                //                            cout << "  tmp pair: " << tmp.first << " : "<< tmp.second << endl;
                                string ttt;
                                ttt.push_back(tmp.first);
                                for (int i=0; i<obj.first.size(); i++)
                                    ttt.push_back(obj.first[i]);
                                cout << "   - size : " << ttt.size() << " str : ";
                                for (int y =0;y<ttt.size();y++)
                                    cout<< ttt[y];
                                cout  << endl;
                                res.insert(make_pair(ttt,tmp.second));
                                
                                m_queue[tmp.first].push(make_pair(ttt,tmp.second));
                                lit.pop();
                            }
                        }
                        else if (last_idx == inter.first)
                        {
                            cout << " case 2"<<endl;
                            
                            if(inter.second != inter.first)
                                locMax = false;
                            process(l, obj, locMax);
                            last_lb = -1;
                            last_idx = -1;
                            locMax = true;
                            stt list;
                            getIntervals(inter,list);
                            
                            while(!list.empty())
                            {
                                pair<char,pair<long,long> > tmp = list.top();
                                //                            cout << "  tmp pair: " << tmp.first << " : "<< tmp.second << endl;
                                string ttt;
                                ttt.push_back(tmp.first);
                                for (int i=0; i<obj.first.size(); i++)
                                    ttt.push_back(obj.first[i]);                                    cout << "   - size : " << ttt.size() << " str : ";
                                for (int y =0;y<ttt.size();y++)
                                    cout<< ttt[y];
                                cout  << endl;
                                res.insert(make_pair(ttt,tmp.second));
                                
                                m_queue[tmp.first].push(make_pair(ttt,tmp.second));
                                list.pop();
                            }
                        }
                        else
                            cout << " case 3"<<endl;
                        
                    }
                    //                    }
                }
            else
                nonempty=false;
            l++;
            cout << "---------------------------------------------------------" <<endl;

        }
        cout<<endl;

    }
    is.close();
    

    for(pairs_t::iterator it=res.begin(); it!=res.end(); it++)
        cout << it->first << " - (" << it->second.first << "," << it->second.second << ")"<<endl;

    cout<<endl;
    

}

void Duplifinder::process(int l, pair<string,pair<long,long> > p, bool locMax)
{
    cout << "process"<<endl;
    auto inter = p.second;

    cout << "l " << l << "-[" << inter.first << " .. " << inter.second << "]"<<endl;

    if( l >= mlength && (inter.second - inter.first+1) >= mocc)
    {
        auto end =occus.end();
        --end;
        --end;
        cout << "cond"<<endl;

        if (locMax && superMax(p))
            cout << "   " << l << "-[" << inter.first << " .. " << inter.second << "] is a supermaximal repeat" << endl;
        else if (rank(true,make_pair(occus.begin()->second.first,end->second.first) ,inter.second) -rank(true, make_pair(occus.begin()->second.first,end->second.first),inter.first) > 0)
             cout << "   " << l << "-[" << inter.first << " .. " << inter.second << "] is a maximal repeat" << endl;
    }
}


void Duplifinder::fill_occus(string &str)
{
    occu_type::iterator it;

    for(int i = 0; i < str.size(); i++)
    {
        it = occus.find(str[i]);

        if (it == occus.end())
        {
//            int size = occus.size();
            occus.insert(make_pair(str[i],make_pair(0,1)));
        }
        else
            it->second.second++;
    }

    int sum=0;
    int tmp;
    int i=1;
    for(occu_type::iterator o=occus.begin(); o != occus.end(); o++)
    {
        o->second.first = i++;
        tmp = o->second.second;
        o->second.second=sum;
        sum+=tmp;

        cout << o->first << " ->  (" << o->second.first<< ", "<< o->second.second << ")  " << endl;
    }
//    int size = occus.size();
    occus.insert(make_pair('~',make_pair(occus.size()+1,sum)));
}

void Duplifinder::getIntervals(pair<long,long> pair, stt &li)
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

void Duplifinder::getinter(pair<long,long> i_j, pair<int,int> l_r, stt &list)
{

//     cout << "( "<< i_j.first << " ::  " << i_j.second << " )" <<endl;
    if(l_r.first== l_r.second)
    {
//        auto it = occus.find(str[l_r.first]);

        auto tmp = next(occus.begin(),l_r.first-1);

        char c = tmp->first;
        cout << "    c:"<< c << endl;

        cout << "      "<< occus[c].second + i_j.first << " :: " << occus[c].second + i_j.second << endl;

        list.push(make_pair(c,make_pair(occus[c].second + i_j.first, occus[c].second + i_j.second)) );
    }
    else
    {
//        cout << " "<< l_r.first << " ::  " << l_r.second << endl;

        pair<long,long> a0 = make_pair(rank(false,l_r,i_j.first-1), rank(false,l_r,i_j.second) );
//        pair<long,long> a0 = make_pair(cst.csa.wavelet_tree.rank(i_j.first-1,0),cst.csa.wavelet_tree.rank(i_j.second,0) );
        pair<long,long> a1 = make_pair(i_j.first-1-a0.first, i_j.second - a0.second);

//        cout << "       a0  "<< a0.first << " ::  " << a0.second << "  b0"<< endl;
//        cout << "       a1  "<< a1.first << " ::  " << a1.second << "  b1"<< endl;


//        auto b1 = next(occus.begin(),l_r.first-1);
//        auto b2 = next(occus.begin(),l_r.second-1);

        int m = (l_r.first + l_r.second)/2 ;


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

bool Duplifinder::superMax(pair<string,pair<long,long> > p)
{
    bool pd = true;
    stt lit;
    getIntervals(p.second, lit);
    
    while(!lit.empty())
        if(lit.top().second.first != lit.top().second.second)
            {
                pd = false;
                lit.pop();
            }
    

    return pd;
}


int Duplifinder::rank( bool search, pair<int ,int> bounds, int limit)
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

    for (int i = 0; i<limit;i++)
        if(occus[tmp[i]].first <= m && limit >=0)
            cpt++;
//    cout << "   cpt : "<<cpt<<"   m: " << m<<endl << endl;


    return cpt;
}

void Duplifinder::init_bwt()
{
    vector<string> table;
    int size = str.size();
    table.resize(size);
    
    for(int i=0; i<size;i++)
        for(int j=i; j<size+i; j++)
            table[i].push_back(str[j % size]);
    
    
    sort(table.begin(),table.end(),[](string a, string b){return a<b;} );

    for(int i=0; i<size;i++)
        bwt.push_back(table[i][size-1]);
    
//    for(int i=0; i<size;i++)
//        cout << table[i] << endl;
//    cout << endl;
//    cout << bwt << endl;

}

//void Duplifinder::lcp_construct(string &str, int m)
//{
//    cout << " start"<< endl;
//
//    int n = str.size();
//    vector<int> last_occu;
//
//    last_occu.resize(n);
//      cout << " size occu"<< endl;
//
//    lcp_array[0] = -1;
//    lcp_array[n] = -1;
//    lcp_array[csa.lf[0]] = 0;
//
//    cout << " inits"<< endl;
//
//    int l;
//    int tmp=0;
//
//    cout << csa.size()<<endl;
//    cout << lcp_array.size()<<endl;
//    cout << last_occu.size()<<endl;
//    cout << n <<endl;
//
//
//    for(int i=1; i<n; i++)
//    {
//        cout<<"i : " << i<<endl;
//
//        if (lcp_array[i]==0)
//        {
//            l = 0;
//            if (csa.lf[i] < i)
//            {
//                l = max(lcp_array[csa.lf[i]]-1,0);
//                if ((csa.bwt[i] == csa.bwt[i-1]) && l<m)
//                {
//                    cout<<" goto"<<endl;
//                    goto CONTINUE;
//                }
//            }
//            while ( (str[csa[i] + l] == str[csa[i-1] + l] )&& l<m)
//            {
////                cout<<" boucle"<<endl;
//                l++;
//            }
//        CONTINUE:
//            lcp_array[i] = l;
//            cout<<" continue"<<endl;
//
//        }
//        if (csa.lf[i]>i)
//        {
//            rmq_t rmq(&last_occu);
//            cout<<" st ass"<<endl;
//
//            cout<<"     lf "<<csa.lf[i]<<endl;
//            cout<<"     bwt "<<csa.bwt[i]<<endl;
//            cout<<"     lst "<<last_occu[csa.bwt[i]]<<endl;
//            cout<<"     size "<<rmq.size()<<endl;
//
//            cout<<"     rmq "<<rmq(last_occu[csa.bwt[i]] +1 ,i)<<endl;
//
//            lcp_array[csa.lf[i]] = min(lcp_array[rmq(last_occu[csa.bwt[i]] +1 ,i)] + 1, m+1);
//            cout<<" ed ass"<<endl;
//
//            tmp++;
//        }
//        last_occu[csa.bwt[i]] = i;
//    }
//    for(int i=0; i<lcp_array.size();i++)
//        cout<<i<< " : " << lcp_array[i]<<endl;
//
////    for (int w : last_occu)
////        cout << "   occu : "<< w<<endl;
//
//    cout << " loop  "<< endl;
//    vector<int> bit;
//    bit.resize(n);
//
//    for (int i=0; i<n; i++)
//        if (lcp_array[i]>m)
//            bit[csa[i]] = 1;
//
//    cout << " loop2"<< endl;
//
//
//    vector<int> phi;
//    phi.resize(bit.size());
//
//    for(int i=0; i<n;i++)
//        if(lcp_array[i]>m && csa.bwt[i]!=csa.bwt[i-1])
//            phi[csa.wavelet_tree.rank(csa[i],1)]=csa[i-1];
//
//    cout << " loop3"<< endl;
//
//
//    int j_i = 0;
//    l = m + 1;
//    vector<int> plcp;
//    int n_i = lcp_array.size() - tmp;
//
//    plcp.resize(n_i);
//
//    for(int j=0; j<n; j++)
//        if(bit[j] == 1)
//        {
//            if( j!=0 && bit[j-1] == 1)
//                l--;
//            else
//                l = m+1;
//
//            if (phi[j_i]!=0)
//                while (str[j+l] == str[phi[j_i]+l])
//                    l++;
//            plcp[j_i] = l;
//            j_i++;
//        }
//    cout << " loop4 "<< endl;
//
//    for (int i=0; i<n; i++)
//        if(lcp_array[i]>m)
//            lcp_array[i] = plcp[csa.wavelet_tree.rank(csa[i],1)];
//    cout << " loop5d"<< endl;
//
//}
//
