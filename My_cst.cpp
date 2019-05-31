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

void My_cst::repeat(char* name_file, int threshold)
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
        if (cst.id(*w)!=cst.id(cst.root()) && cst.depth(*w)>=threshold)
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
                }
            if(!(tmp.empty()))
                results_array.insert( make_pair(cst.id(*w), tmp));
            
        }
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
            if(cst.id(v)==cst.id(cst.root()))
                place = cst.id(cst.root());
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
    
    int length;
    int index;
    
    if (is.good())
    {
        string tmp( (istreambuf_iterator<char>(is) ), (istreambuf_iterator<char>()  ));
    
        origin = tmp;
        length = origin.size();
        index = length - cst.depth(v) + 1;
    
        if( c == origin[index - 1] )
        {
//                    cout << origin[index - 1] <<endl;
            position = make_pair(c,index+1);
            
//                    for(int i=index; i<length; i++)
//                        cout << origin[i];
//                    cout<< " : node "<< cst.id(v)<<endl;
            return true;
        }
       
    }
    is.close();
    return false;
}

void My_cst::printlist()
{
//    for (pos_type::iterator it=map_pos.begin(); it!=map_pos.end(); it++)
//    {
//        cout << "\n id node : " << it->first << endl;
//
//        for (pair<char,int> p : it->second)
//            cout << "  pair : (" << p.first << ", " << p.second << ")" << endl;
//    }
    cout << "\n------------------------------------------------------------"<<endl;
    int i =0;
    for (results_type::iterator it=results_array.begin(); it!=results_array.end(); it++)
    {
        if (it->first!=cst.id(cst.root()))
        {
            cout << "\nid node : " << i++<< " - Length of the repeat string : " << cst.depth(cst.inv_id(it->first))<< endl;
            
            cout << "  - Occurences : " << cst.degree(cst.inv_id(it->first))<<endl;
            cout << "  - Repeat string : ";
            for(int i=it->second[0].first.first-1; i<it->second[0].first.second; i++)
                cout<< origin[i];
            cout << endl;
//            for (pair<pair<int,int>,pair<int,int>> p : it->second)
//                cout<< "  result: [ (" << p.first.first << "," << p.first.second << "), (" << p.second.first << "," << p.second.second << ") ]" << endl;
        }
    }
    
    cout << "\n------------------------------------------------------------\n"<<endl;
}
