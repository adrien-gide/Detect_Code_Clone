/**
 *
 * Duplifinder.cpp
 * Created by Adrien Gide on 2019/05/21.
 */

#include "Duplifinder.hpp"

using namespace sdsl;
using namespace std;

void Duplifinder::repeat(const char* name_file,int threshold)
{
    name_f = name_file;
    construct(cst, name_file,1);
    
    iterator begin = iterator(&cst, cst.root());
    iterator end   = iterator(&cst, cst.root(), true, true);
    
/// Iniitializing the pair(s) (character, position) for each node/leaf with a corresponding size
    
    for(iterator init=begin; init != end; init++)
        if (cst.id(*init)!=cst.id(cst.root()) && (cst.depth(*init)>=threshold))
            A(*init);
    
    for(iterator w=begin; w != end; w++)
        if (cst.id(*w)!=cst.id(cst.root()) && (cst.depth(*w)>=threshold))
        {
            set<pair< pair<int,int>, pair<int,int>> > tmp;
            
/// Loops on each children pair for a node
            for(int k = 1; k <= cst.degree(*w);k++)
            {
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
                                        tmp.insert(p);
                                    }
                }
            }
            if(!(tmp.empty()))
                results_array.insert( make_pair(cst.id(*w), tmp));
        }
}

void Duplifinder::A(node_type v)
{
    pos_type::iterator it;
    vector<pair<char,int>> vect;
    if(cst.is_leaf(v))
    {
        if(get_i(v) && cst.id(cst.parent(v))!=cst.id(cst.root()))
        {
            int place;
            place = cst.id(cst.parent(v));
            
            it= map_pos.find(place);
            if (it != map_pos.end() )
            {
                if (find(it->second.begin(), it->second.end(), position) == it->second.end())
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
            A(child);
            if((it = map_pos.find(cst.id(v))) != map_pos.end())
            {
                if(!(cst.is_leaf(child)))
                    for(pair<char,int> p : map_pos[cst.id(child)])
                        if (find(it->second.begin(), it->second.end(), p) == it->second.end())
                            map_pos[cst.id(v)].push_back(p);
            }
            else
            {
                map_pos.insert(make_pair(cst.id(v),vect));
                for(pair<char,int> p : map_pos[cst.id(child)])
                    map_pos[cst.id(v)].push_back(p);
            }
        }
}

bool Duplifinder::get_i( node_type v)
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
        
        
//                    cout << origin[index - 1] <<endl;
        position = make_pair(origin[index - 1] ,index+1);
        
//                    for(int i=index; i<length; i++)
//                        cout << origin[i];
//                    cout<< " : node "<< cst.id(v)<<endl;
        return true;
    }
    is.close();
    return false;
}

void Duplifinder::printlist()
{
    //    for (pos_type::iterator it=map_pos.begin(); it!=map_pos.end(); it++)
    //    {
    //        cout << "\n id node : " << it->first << endl;
    //
    //        for (pair<char,int> p : it->second)
    //            cout << "  pair : (" << p.first << ", " << p.second << ")" << endl;
    //    }
    //    cout << "\n------------------------------------------------------------"<<endl;
    if (!results_array.empty())
    {
        int j =0;
        for (results_type::iterator it=results_array.begin(); it!=results_array.end(); it++)
        {
            if (it->first!=cst.id(cst.root())  )
            {
                cout << "\nid : " << j++ << endl;
                cout << "  - Length of the repeat string : " << cst.depth(cst.inv_id(it->first))<< endl;
                cout << "  - Occurences : " << cst.size(cst.inv_id(it->first))<<endl;
                cout << "  - Repeat string :";
                for(int i=it->second.begin()->first.first-1; i<it->second.begin()->first.second; i++)
                    cout<< origin[i];
                cout << "\n" << endl;
                if( !lg_vect.empty())
                    for(int l : lg_vect)
                    {
                        if (it->second.begin()->first.first <= l && it->second.begin()->second.first <= l )
                        {
                            
                        }
                        else if (
                    }
                //                for (pair<pair<int,int>,pair<int,int>> p : it->second)
                //                    cout<< "  result: [ (" << p.first.first << "," << p.first.second << "), (" << p.second.first << "," << p.second.second << ") ]" << endl;
            }
        }
        
    }
    else
        cout << "No maximal pair(s) for this threshold !" << endl;
}




void Duplifinder::compare(set<string> files, int threshold)
{
    ofstream merge("Test files/tmp.txt", ios_base::binary);
    
    for (string f : files)
    {
        ifstream tmp(f, ios_base::binary);
        merge << tmp.rdbuf();
        lg_vect.push_back(tmp.tellg());
        tmp.close();
    }
    merge.close();
    
    repeat("Test files/tmp.txt", threshold);
    
}
