#ifndef HASHMAP_H
#define HASHMAP_H

#include <functional>
#include "ForwardList.h"

using namespace std;

template<typename T,typename K>
class HashMap{
private:

    int max_collision;
    int capacity;
    ForwardList<pair<const T,K>> *arr;
    int _size=0;

    template<typename t>
    int hash_f(const t &x){
        hash<t> f;
        int result=f(x);
        return abs(result)%capacity;
    }

    template<typename t1,typename t2>
    int hash_f(const pair<t1,t2> &p){
        int h1 = std::hash<int>{}(p.first);
        int h2 = std::hash<int>{}(p.second);
        int result=h1^h2;
        return abs(result)%capacity;
    }

    int power(int a,int b){
        if(b==0) return 1;
        if(b%2==0){
            int x=power(a,b/2);
            return x*x;
        }
        int x=power(a,(b-1)/2);
        return a*x*x;
    }

    bool is_prime(int n){
        if(n==1) return false;
        for(int i=2;i<n;i++){
            if(n%i==0) return false;
        }
        return true;
    }

    void update_capacity(){
        // get 2^(cap)
        int n=power(2,capacity);
        // get next prime
        while(!is_prime(n)) n++;
        capacity=n;
    }

    void rehash(){
        int prev_cap=capacity;
        update_capacity();
        HashMap<T,K> *temp=new HashMap<T,K>(capacity,max_collision);
        for(int i=0;i<prev_cap;i++){
            for(auto it=arr[i].begin();it!=arr[i].end();it++){
                temp->insert(it->first,it->second);
            }
        }
        delete[] this->arr;
        this->arr=temp->arr;
    }

public:

    struct iterator{
    private:
        int pos=0;
        HashMap<T,K> *this_hash=nullptr;
        typename ForwardList<pair<const T,K>>::iterator current;
        iterator(HashMap<T,K> *h,typename ForwardList<pair<const T,K>>::iterator n,int pos,bool end)
        :pos(pos),this_hash(h),current(n){
            if(!end&&current.end()){
                next();
            }
        }
        void next(){
            do{
                if(pos+1!=this_hash->capacity) pos++;
                else return;
            }while(this_hash->arr[pos].size()==0);
            current=this_hash->arr[pos].begin();
        }
    public:
        iterator(){}
        iterator(const iterator &other){
            this->current=other.current;
            this->this_hash=other.this_hash;
            this->pos=other.pos;
        }
        iterator &operator=(const iterator &other){
            if(this==&other) return *this;
            this->current=other.current;
            this->pos=other.pos;
            this->this_hash=other.this_hash;
            return *this;
        }
        iterator &operator++(){
            current++;
            if(current.end()){
                next();
            }
            return *this;  
        }
        iterator operator++(int){
            iterator prev=*this;
            ++(*this);
            return prev;   
        }
        bool operator==(iterator other){
            return this->current==other.current;
        }
        bool operator!=(iterator other){
            return this->current!=other.current;
        }
        pair<const T,K> &operator*(){
            return *current;
        }
        pair<const T,K> *operator->(){
            return &(*current);
        }
        friend class HashMap<T,K>;
    };

	HashMap(int cap=4,int coll=3):capacity(cap),max_collision(coll){
        arr=new ForwardList<pair<const T,K>>[capacity];
    }

    HashMap(const HashMap<T,K> &other){
        this->capacity=other.capacity;
        this->max_collision=other.max_collision;
        this->_size=other._size;
        this->arr=new ForwardList<pair<const T,K>>[this->capacity];
        for(int i=0;i<capacity;i++){
            this->arr[i]=other.arr[i];
        }
    }

    HashMap<T,K> operator=(const HashMap<T,K> &other){
        if(this==&other) return *this;
        this->capacity=other.capacity;
        this->max_collision=other.max_collision;
        this->_size=other._size;
        delete[] this->arr;
        this->arr=new ForwardList<pair<const T,K>>[capacity];
        for(int i=0;i<capacity;i++){
            this->arr[i]=other.arr[i];
        }
        return *this;
    }

    ~HashMap(){
        delete[] arr;
    }

    void insert(const T &key,const K &value){
        int pos=hash_f(key);

        for(auto it=arr[pos].begin();it!=arr[pos].end();it++){
            if(key==it->first){
                return;
            }
        }
        if(arr[pos].size()<max_collision){
            arr[pos].push_front(make_pair(key,value));
            _size++;
        }
        else{
            rehash();
            insert(key,value);
        }
    }

    K &operator[](T key){
        int pos=hash_f(key);
        for(auto it=arr[pos].begin();it!=arr[pos].end();it++){
            if(key==it->first){
                return it->second;
            }
        }
        insert(key,K());
        return (*this)[key];
    }

    void remove(const T &key){
        int pos=hash_f(key);
        for(auto it=arr[pos].begin();it!=arr[pos].end();it++){
            if(key==it->first){
                arr[pos].remove(it);
                _size--;
                return;
            }
        }
    }

    void remove(iterator it){
        arr[it.pos].remove(it.current);
        _size--;
    }

    void clear(){
        delete[] arr;
        _size=0;
        capacity=4;
        arr=new ForwardList<pair<const T,K>>[capacity];
    }

    iterator find(const T &key){
        int pos=hash_f(key);
        for(auto it=arr[pos].begin();it!=arr[pos].end();it++){
            if(key==it->first){
                return iterator(this,it,pos,false);
            }
        }
        return iterator(this,arr[capacity-1].end(),capacity-1,true);
    }

    int size(){
        return _size;
    }

    iterator begin(){
        return iterator(this,arr[0].begin(),0,false);
    }
    
    iterator end(){
        return iterator(this,arr[capacity-1].end(),capacity-1,true);
    }
};

#endif