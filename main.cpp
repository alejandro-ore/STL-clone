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

template<typename T>
struct temp{
    temp(){}
};

#include <bits/stdc++.h>

int main(){
    HashMap<int,Queue<int>> a;
    a.insert(1,Queue<int>());
    a[1].push(1);
    a[1].push(2);
    a[1].push(3);
    a[1].push(4);
    a[1].push(5);
    while(!a[1].empty()){
        cout<<a[1].front()<<" ";
        a[1].pop();
    }
}