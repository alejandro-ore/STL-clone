#include "bits.h"
using namespace std;

template<typename T,typename K,template<class,class> class container>
void print(container<T,K> &a){
    for(auto it=a.begin();it!=a.end();it++){
        cout<<"("<<it->first<<","<<it->second<<") ";
    }
    cout<<"\n";
}

template<typename T,template<typename> class container>
void print(container<T> &a){
    for(auto it=a.begin();it!=a.end();it++){
        cout<<*it<<" ";
    }
    cout<<"\n";
}

#include <functional>

struct pair_hash
{
    int operator () (const std::pair<int, int>& p) const {
        int h1 = std::hash<int>{}(p.first);
        int h2 = std::hash<int>{}(p.second);

        return static_cast<int>(h1^h2);
    }
};

int main(){
    HashSet<pair<int,int>,pair_hash> a;
    a.insert({1,2});
    a.insert({2,1});
    a.insert({2,2});
    for(auto it=a.begin();it!=a.end();it++){
        cout<<"("<<it->first<<","<<it->second<<")\n";
    }
}