#ifndef DSU_H
#define DSU_H

#include "Vector.h"
#include "HashMap.h"

template<typename T>

class DSU{
private:

    HashMap<T,T> parent;
    HashMap<T,int> rank;
    int _sets=0;

public:

    DSU(){}

    DSU(Vector<T> &data){
        for(int i=0;i<data.size();i++){
            parent[data[i]]=data[i];
            rank[data[i]]=0;
        }
        _sets=data.size();
    }

    DSU(const DSU<T> &other){
        this->parent=other.parent;
        this->rank=other.rank;
        this->_sets=other._sets;
    }

    DSU<T> &operator=(const DSU<T> &other){
        if(this==&other) return *this;
        this->parent=other.parent;
        this->rank=other.rank;
        this->_sets=other._sets;
        return *this;
    }

    void make_set(const T &x){
        if(parent.find()!=parent.end()){
            parent[x]=x;
            rank[x]=0;
            _sets++;
        }
    }

    T find(const T &x){
        if(parent[x]!=x){
            parent[x]=find(parent[x]);
        }
        return parent[x];
    }

    void union_(const T &x,const T &y){
        T root_x=find(x);
        T root_y=find(y);
        if(root_x==root_y) return;
        if(rank[root_x]<rank[root_y]){
            parent[root_x]=root_y;
        }
        else if(rank[root_x]>rank[root_y]){
            parent[root_y]=root_x;
        }
        else{
            parent[root_x]=root_y;
            rank[root_y]++;
        }
        find(root_x);find(root_y);
        _sets--;
    }

    bool connected(const T &x,const T &y){
        return find(x)==find(y);
    }

    int size(){
        return parent.size();
    }

    int sets(){
        return _sets;
    }

};

#endif