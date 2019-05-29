//
//  My_cst.cpp
//  
//
//  Created by Adrien Gide on 2019/05/21.
//

#include "My_cst.hpp"
#include <string>

using namespace sdsl;
using namespace std;

void My_cst::repeat(char* name_file)
{
    name_f = name_file;
    construct(cst, name_file,1);
    
    iterator begin = iterator(&cst, cst.root());
    iterator end   = iterator(&cst, cst.root(), true, true);
    
    for(iterator init=begin; init != end; init++)
        for(int c=0;c<128;c++)
            A(*init,c);
    
    
    for(iterator w=begin; w != end; w++)
    {
        vector<pair< pair<int,int>, pair<int,int>> > tmp;
        for(int k = 1; k <= cst.degree(*w);k++)
            for(int l = k+1; l <= cst.degree(*w); l++)
            {
                auto v_f = cst.select_child(*w,l);
                auto v_g = cst.select_child(*w,k);
                
                if( !( map_pos[cst.id(v_f)].empty()) )
                    
                    for( pair<char,int> i : map_pos[cst.id(v_f)])
                        if(!(map_pos[cst.id(v_g)].empty()) )
                            for( pair<char,int> j : map_pos[cst.id(v_g)])
                                if (j.first!=i.first)
                                {
                                    pair< pair<int,int>, pair<int,int>> p =make_pair( make_pair(i.second, i.second+cst.depth(*w)-1), make_pair(j.second, j.second+cst.depth(*w)-1));
                                    if(find(tmp.begin(), tmp.end(), p) != tmp.end()){}
                                    else
                                        tmp.push_back(p);
                                }
                
                //                for(int i=1; i<=cst.depth(child);i++)
                //
                //                    for(int j=1; j<=cst.depth(sib);j++)
                //
                //                        char c = cst.edge(child,i);
                //                        cout << c << " - " ;
                //                        char d = cst.edge(sib,j);
                //                        cout << d << " " ;
                //                        if(c!=d)
                //                        {
                //                            cout << "result: ( (" << i << "," << i+cst.depth(*it)-1 << "), (" << j << "," << j+cst.depth(*it)-1 << ")" << endl;
                //
                //                        }
                //
                //
            }
        if(!(tmp.empty()))
            results_array.insert( make_pair(cst.id(*w), tmp));
    }
}

void My_cst::A(node_type v, char c)
{
    pos_type::iterator it;
    vector<pair<char,int>> vect;
    
    
    if(cst.is_leaf(v))
    {
        if(get_i(c,v))
        {
            
            int place;
            if(cst.id(v)==20)
                place = 20;
            else
                place = cst.id(cst.parent(v));
            
            
            it= map_pos.find(place);
            
            if (it != map_pos.end())
            {
                if (find(it->second.begin(), it->second.end(), position) != it->second.end()){}
                else
                    map_pos[place].push_back(position);
            }
            else{
                map_pos.insert(make_pair(place,vect));
                map_pos[place].push_back(position);
            }
            
            
            map_pos.insert(make_pair(cst.id(v),vect));
            if( map_pos[cst.id(v)].empty())
                map_pos[cst.id(v)].push_back(position);
        }
    }
    else
        for(auto& child : cst.children(v))
        {
            A(child, c);
            
            if((it = map_pos.find(cst.id(v))) != map_pos.end())
            {
                if(!(cst.is_leaf(child)))
                    for(pair<char,int> p : map_pos[cst.id(child)])
                    {
                        
                        if (find(it->second.begin(), it->second.end(), p) != it->second.end()){}
                        else
                            map_pos[cst.id(v)].push_back(p);
                    }
            }
            else
            {
                map_pos.insert(make_pair(cst.id(v),vect));
                for(pair<char,int> p : map_pos[cst.id(child)])
                    map_pos[cst.id(v)].push_back(p);
                
            }
        }
    
    
}

bool My_cst::get_i(char c, node_type v)
{
    ifstream is(name_f);
    string origin( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));
    
    int length = origin.size();
    int index = length - cst.depth(v) + 1;
    
    if( c == origin[index - 1] )
    {
        //        cout << origin[index - 1] <<endl;
        position = make_pair(c,index+1);
        
        //        for(int i=index; i<length; i++)
        //            cout << origin[i];
        //        cout<< " : node "<< cst.id(v)<<endl;
        return true;
    }
    is.close();
    return false;
}

void My_cst::printlist()
{
    for (pos_type::iterator it=map_pos.begin(); it!=map_pos.end(); it++)
    {
        cout << "\n id node : " << it->first << endl;
        
        for (pair<char,int> p : it->second)
            cout << "  pair : (" << p.first << ", " << p.second << ")" << endl;
    }
    cout << "------------------------------------------------------------"<<endl;
    
    for (results_type::iterator it=results_array.begin(); it!=results_array.end(); it++)
    {
        cout << "\n id node :" << it->first << endl;
        
        for (pair<pair<int,int>,pair<int,int>> p : it->second)
            cout<< "  result: [ (" << p.first.first << "," << p.first.second << "), (" << p.second.first << "," << p.second.second << ") ]" << endl;
    }
    cout << "\n------------------------------------------------------------\n"<<endl;
    //    for(int i=0;i<pair_array.size(); i++) {
    //        for (int j=0;j<pair_array[i].size(); j++)
    //            cout << "  pair : (" << pair_array[i][j].first << ", " << pair_array[i][j].second << ")" << endl;
    //        cout << endl;
    //    }
    //    int i = 0;
    //    for (vector<pair<char,int>> v : pair_array)
    //    {
    //        cout << " i : " << i++ << endl;
    //        for (pair<char,int> p : v)
    //            cout << "  pair : (" << p.first << ", " << p.second << ")" << endl;
    //        cout<<endl;
    //    }
    
}
