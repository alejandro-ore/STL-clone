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

int main(){
    Vector<int> v;
    for(int i=1;i<=10;i++) v.push_back(i);
    DSU<int> a(v);
    DSU<int> b;
    b=a;
}