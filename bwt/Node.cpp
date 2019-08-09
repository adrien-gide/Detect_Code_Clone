/**
 *
 * Duplifinder.hpp
 * Created by Adrien Gide on 2019/06/28.
 */

#include "Node.hpp"


using namespace std;

Node::Node(WaveletTree& wt,string s,pair<int,int> alphabet)
{
    
    if (alphabet.first != alphabet.second)
    {
        string zeros, ones;
        
        int m = (alphabet.first + alphabet.second)/2;
        
        cout << s << endl;
        
        
        for(int i = 0; i < s.size(); i++)
        {
            if(wt.occus[s[i]].first <= m)
            {
                zeros.push_back(s[i]);
                bit_vector.push_back(0);
            }
            else
            {
                ones.push_back(s[i]);
                bit_vector.push_back(1);
            }
        }
//
        cout<<alphabet.first<<", "<<alphabet.second<<endl;
        int size = bit_vector.size();
        for (int o=0; o<size; o++)
            cout << bit_vector[o];
        cout << endl;
        
        left = new Node(wt,zeros, make_pair(alphabet.first,m));

        right = new Node(wt,ones, make_pair(m+1,alphabet.second));
        
    }
    else
        final_string = s;

    pair<pair<int,int>, Node*> p = make_pair(alphabet,this);
    wt.tree.insert(p);

}

int Node::rank(int c, int i)
{
    int cpt=0;
    
    for (int o=0; o<i; o++)
        if(bit_vector[o]==c)
            cpt++;
    
    cout << cpt << endl;
    
    return cpt;
        
}
