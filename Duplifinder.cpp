/**
 *
 * Duplifinder.cpp
 * Created by Adrien Gide on 2019/05/21.
 */

#include "Duplifinder.hpp"

using namespace sdsl;
using namespace std;

void Duplifinder::repeat(const char* name_file,unsigned int threshold, bool multiple)
{
    
    ifstream is(name_file);
    
    clock_t time =clock();
    construct(cst, name_file,1);
    cout << " Time tree construction : " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
    
    iterator begin = iterator(&cst, cst.root());
    iterator end   = iterator(&cst, cst.root(), true, true);
    
    /// Iniitializing the pair(s) (character, position) for each node/leaf with a corresponding size
    
    cout << cst.nodes() << endl;
    cout << cst.size() << endl;
    cout << " Threshold: "<< threshold << endl;
    int d = 0;
    
    if (is.good())
    {
        string tmp( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));
        
        origin = tmp;
        cout << "Time A : " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;

        for(iterator w=begin; w != end; w++)
        {
            d++;
            if (cst.id(*w)!=cst.id(cst.root()))
                if (!cst.is_leaf(*w))
                    if (cst.depth(*w)>=threshold)
                    {
                        set<pair< pair<int,int>, pair<int,int>> > tmp;
                        pos_type res_A;
                        
                        for (auto& child : cst.children(*w))
                            res_A.insert(make_pair(cst.id(child),A(child)));
                        
//                        cout << " Remaining: "<< cst.nodes() - d;
//
//                        cout << " - passed: " << d <<  " - Time at step : " << ( clock() - time )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
                        /// Loops on each children pair for a node
                        for(int k = 1; k <= cst.degree(*w);k++)
                        {
                            for(int l = k+1; l <= cst.degree(*w); l++)
                            {
                                auto v_f = cst.select_child(*w,l);
                                auto v_g = cst.select_child(*w,k);
                                
                                if( !res_A[cst.id(v_f)].empty() )
                                    if(!res_A[cst.id(v_g)].empty() )
                                        for( pair<char,int> i : res_A[cst.id(v_f)])
                                            for( pair<char,int> j : res_A[cst.id(v_g)])
                                                if (j.first!=i.first)
                                                {
                                                    pair< pair<int,int>, pair<int,int>> p = make_pair( make_pair(i.second, i.second+cst.depth(*w)-1), make_pair(j.second, j.second+cst.depth(*w)-1));
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
                        if(!(tmp.empty()))
                        {
                            cout << "\nRepeat string :";
                            for(int i=tmp.begin()->first.first-1; i<tmp.begin()->first.second; i++)
                                cout<< origin[i];
                            cout<<endl;
                            
                            cout << "\n  - Length of the repeat string : " << cst.depth(*w)<< endl;
                            cout << "  - Occurences (including repeats in a same file): " << cst.size(*w)<<endl;
                            
                            if(multiple)
                            {
                                if(mult)
                                {
                                    set<string> tmp2;
                                    cout << "  - Inside these files : " << endl;
                                    int val = 0;
                                    for(map<string,int>::iterator lg = lg_map.begin() ; lg != lg_map.end() ; lg++)
                                    {
                                        for(pair< pair<int,int>, pair<int,int>> p : tmp)
                                        {
                                            if ( p.first.first <= lg->second && p.first.first >= val )
                                                tmp2.insert(lg->first);
                                            
                                            if(p.second.first <= lg->second && p.second.first >= val )
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
//                            results_array.insert( make_pair(cst.id(*w), tmp));
            
        }
        
    }
    is.close();
}

set<pair<char,int> > Duplifinder::A(node_type v)
{
    pos_type::iterator it;
    set<pair<char,int> > s;
    if(cst.is_leaf(v))
    {
        if(get_i(v) && cst.id(cst.parent(v))!=cst.id(cst.root()))
        {
            s.insert(position);
            return s;
        }
    }
    else
        for(auto& child : cst.children(v))
        {
            set<pair<char, int>> tmp = A(child);
            
            for(pair<char,int> p : tmp)
                s.insert(p);
            
            return s;
        }
    return s;
}

bool Duplifinder::get_i( node_type v)
{
    int length;
    int index;
    length = origin.size();
    index = length - cst.depth(v) + 1;
    
    
    //                    cout << origin[index - 1] <<endl;
    position = make_pair(origin[index - 1] ,index+1);
    
    //                    for(int i=index; i<length; i++)
    //                        cout << origin[i];
    //                    cout<< " : node "<< cst.id(v)<<endl;
    return true;
}

void Duplifinder::printlist()
{
    if (!results_array.empty())
    {
//            for (pos_type::iterator it=map_pos.begin(); it!=map_pos.end(); it++)
//            {
//                cout << "\n id node : " << it->first << endl;
//
//                for (pair<char,int> p : it->second)
//                    cout << "  pair : (" << p.first << ", " << p.second << ")" << endl;
//            }
        //    cout << "\n------------------------------------------------------------"<<endl;

        for (results_type::iterator it=results_array.begin(); it!=results_array.end(); it++)
        {
            if (it->first!=cst.id(cst.root())  )
            {
                cout << "\nRepeat string :";
                for(int i=it->second.begin()->first.first-1; i<it->second.begin()->first.second; i++)
                    cout<< origin[i];
                cout<<endl;
                
                cout << "\n  - Length of the repeat string : " << cst.depth(cst.inv_id(it->first))<< endl;
                cout << "  - Occurences : " << cst.size(cst.inv_id(it->first))<<endl;
                
                if(mult)
                {
                    set<string> tmp;
                    cout << "  - Inside these files : " << endl;
                    int val = 0;
                    for(map<string,int>::iterator lg = lg_map.begin() ; lg != lg_map.end() ; lg++)
                    {
                        for(pair< pair<int,int>, pair<int,int>> p : it->second)
                        {
                            if ( p.first.first <= lg->second && p.first.first >= val )
                                tmp.insert(lg->first);
                            
                            if(p.second.first <= lg->second && p.second.first >= val )
                                tmp.insert(lg->first);
                        }
                            val = lg->second;
                    }
                    
                    for( string f : tmp)
                        cout << "      - "<< f << endl;
                    
                    cout<<"\n"<<endl;
                    
                }
//                for (pair<pair<int,int>,pair<int,int>> p : it->second)
//                    cout<< "  result: [ (" << p.first.first << "," << p.first.second << "), (" << p.second.first << "," << p.second.second << ") ]" << endl;
            }
        }
        
    }
    else
        cout << "No maximal pair(s) for this threshold ! " << endl;
}



void Duplifinder::compare(set<string> files, unsigned int threshold)
{
    ofstream merge(TMP_FILE, ios_base::binary);
    
    double lg = 0;
    int id = 0;
    for (string f : files)
    {
        ifstream tmp(f, ios_base::binary);
        if (tmp.good())
        {
            merge << tmp.rdbuf() << "\n$id$: " << id++ << endl;
            lg += tmp.tellg();
            lg_map.insert(make_pair(f,lg));
            if (lg_max <= tmp.tellg())
                lg_max = tmp.tellg();
        }
        tmp.close();
    }
    cout << lg_max <<endl;
    cout << "Time concat : " << ( clock() )/ (double) CLOCKS_PER_SEC << " second(s)"<< endl;
    merge.close();
    mult = true;
    repeat(TMP_FILE, threshold, mult);
    
}
