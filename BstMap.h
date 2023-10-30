#ifndef BSTMAP_H
#define BSTMAP_H

#include <iostream>
#include "Queue.h"
#include "Stack.h"
using namespace std;

template<typename T,typename K>
class BstMap{
private:

    struct node{
        pair<const T,K> data;
        node *left=nullptr;
        node *right=nullptr;
        int height=1;
        node(const T &key,const K &value):data(make_pair(key,value)){}
    };

    node *root=nullptr;
    int _size=0;

    int height(node *n){
        return (n!=nullptr)?n->height:0;
    }

    int factor(node *n){
        return height(n->left)-height(n->right);
    }

    node *rotate_left(node *x){
        node *y=x->right;
        node *extra=y->left;
        y->left=x;
        x->right=extra;
        x->height=1+max(height(x->left),height(x->right));
        y->height=1+max(height(y->left),height(y->right));
        return y;
    }

    node *rotate_right(node *x){
        node *y=x->left;
        node *extra=y->right;
        y->right=x;
        x->left=extra;
        x->height=1+max(height(x->left),height(x->right));
        y->height=1+max(height(y->left),height(y->right));
        return y;
    }

    node *balance(node *current){
        if(current==nullptr) return current;
        current->height=1+max(height(current->left),height(current->right));
        int _factor=factor(current);
        if(_factor<-1){
            current->right=(factor(current->right)>0)?(rotate_right(current->right)):(current->right);
            return rotate_left(current);
        }
        if(_factor>1){
            current->left=(factor(current->left)>0)?(rotate_right(current->left)):(current->left);
            return rotate_right(current);
        }
        return current;
    }

    pair<node*,node*> insert_help(node *current,node *parent,const T &key){
        if(current==nullptr){
            // current is null, so we found insertion place. insert from parent
            node *n=new node(key,K());
            _size++;
            if(key<parent->data.first){
                parent->left=n;
            }   
            else{
                parent->right=n;
            }
            return {n,n};
        }
        // p.first: for balancing
        // p.second: for returning
        pair<node*,node*> p;
        if(key<current->data.first){
            // key is lower. go left
            p=insert_help(current->left,current,key);
            current->left=p.first;
        }
        else if(key>current->data.first){
            // key is higher. go right
            p=insert_help(current->right,current,key);
            current->right=p.first;
        }
        else{
            // found key. no insertion done.
            return {current,current};
        }
        // try rotate. use current and parent for base
        node *temp=balance(current);
        if(current==root){
            root=temp;
        }
        return {temp,p.second};
    }

public:

    BstMap(){}

    struct iterator{
    private:
        Stack<node*> traversal;
        void move_left(node *current){
            while(current!=nullptr){
                traversal.push(current);
                current=current->left;
            }
        }
    public:
        iterator(node *n=nullptr){
            if(n!=nullptr) move_left(n);
        }
        iterator(const iterator &other){
            this->traversal=other.traversal;
        }
        iterator &operator=(const iterator &other){
            if(this==&other) return *this;
            this->traversal=other.traversal;
            return *this;
        }
        iterator &operator++(){
            if(traversal.empty()) throw runtime_error("Segmentation fault");
            node *current=traversal.top();
            traversal.pop();
            if(current->right!=nullptr) move_left(current->right);
            return *this;
        }
        iterator operator++(int){
            iterator prev=*this;
            ++(*this);
            return prev;
        }
        bool operator==(iterator other){
            if(other.traversal.size()==0||this->traversal.size()==0){
                if(other.traversal.size()==this->traversal.size()) return true;
                return false;
            }
            return this->traversal.top()==other.traversal.top();
        }
        bool operator!=(iterator other){
            return !(*this==other);
        }
        pair<const T,K> &operator*(){
            return traversal.top()->data;
        }
        pair<const T,K> *operator->(){
            return &(traversal.top()->data);
        }
    };

    K &operator[](const T &key){
        if(root==nullptr){
            root=new node(key,K());
            return root->data.second;
        }
        node *n=insert_help(root,nullptr,key).second;
        return n->data.second;
    }

    void insert(const T &key,const K &value){
        if(root==nullptr){
            root=new node(key,value);
            return;
        }
        node *n=insert_help(root,nullptr,key).second;
        n->data.second=value;
    }

    void print(){
        // debug. to remove.
        Queue<node*> nodes;
        nodes.push(root);
        while(!nodes.empty()){
            node *current=nodes.front();
            nodes.pop();
            cout<<"("<<current->data.first<<","<<current->data.second<<") ";
            if(current==nullptr) continue;
            if(current->left) nodes.push(current->left);
            if(current->right) nodes.push(current->right);
        }
        cout<<"\n";
    }

    void remove(){
        // TODO
    }

    iterator find(const T &key){
        auto it=begin();
        for(it;it!=end();it++){
            if(it->first==key){
                return it;
            }
        }
        return end();
    }

    int size(){
        return _size;
    }

    iterator begin(){
        return iterator(root);
    }

    iterator end(){
        return iterator();
    }

};

#endif