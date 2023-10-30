#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <iostream>
using namespace std;

template<typename T>
class ForwardList{
private:

	struct node{
		T data;
		node *next=nullptr;
		node(const T &key):data(key){}
	};

	node *root=nullptr;
    int _size=0;

public:

	struct iterator{
    private:
        node *current;
    public:
        bool end(){
            return current==nullptr;
        }
        iterator(node *n=nullptr):current(n){}
        iterator(const iterator &other){
            this->current=other.current;
        }
        iterator operator=(const iterator &other){
            this->current=other.current;
            return *this;
        }
        iterator &operator++(){
            current=current->next;
            return *this;
        }
        iterator operator++(int){
            iterator prev=*this;
            current=current->next;
            return prev;
        }
        bool operator==(const iterator &other){
            return this->current==other.current;
        }
        bool operator!=(const iterator &other){
            return this->current!=other.current;
        }
        T &operator*(){
            return current->data;
        }
        T *operator->(){
            return &current->data;
        }

        friend class ForwardList<T>;
	};

	ForwardList(){}

    ForwardList(ForwardList<T> &other){
        if(other.size()!=0){
            this->_size=other._size;
            auto it=other.begin();
            root=new node(*it);
            it++;
            node *current=root,*prev=root;
            for(it;it!=other.end();it++){
                current=new node(*it);
                if(prev){
                    prev->next=current;
                    prev=current;
                }
            }
        }
    }

    ForwardList<T> operator=(ForwardList<T> &other){
        if(this==&other) return *this;
        if(other.size()!=0){
            this->_size=other._size;
            auto it=other.begin();
            root=new node(*it);
            it++;
            node *current=root,*prev=root;
            for(it;it!=other.end();it++){
                current=new node(*it);
                if(prev){
                    prev->next=current;
                    prev=current;
                }
            }
        }
        return *this;
    }

    ~ForwardList(){
        node *prev;
        node *current=root;
        while(current!=nullptr){
            prev=current;
            current=current->next;
            delete prev;
        }
    }

    void clear(){
        node *prev;
        node *current=root;
        while(current!=nullptr){
            prev=current;
            current=current->next;
            delete prev;
        }
        root=nullptr;
    }
    
	void push_front(const T &key){
        node *n=new node(key);
        n->next=root;
        root=n;
        _size++;
	}

    void pop_front(){
        if(root==nullptr) return;
        node *temp=root;
        root=root->next;
        _size--;
        delete temp;
    }

    int size(){
        return _size;
    }

    void remove(const T &key){
        if(_size==0) throw runtime_error("what");
        if(_size==1){
            pop_front();
            return;
        }
        node *current=root;
        while(current->next->data!=key){
            current=current->next;
        }
        node *n=current->next;
        current->next=n->next;
        delete n;
        _size--;
    }

    void remove(iterator it){
        node *n=it.current;
        if(n==nullptr) throw runtime_error("what");
        if(n==root){
            pop_front();
            return;
        }
        node *current=root;
        while(current->next!=n){
            current=current->next;
        }
        current->next=n->next;
        delete n;
        _size--;
        return;
    }

    iterator find(const T &key){
        node *current=root;
        while(current!=nullptr){
            if(current->data==key){
                return iterator(current);
            }
            current=current->next;
        }
        return end();
    }

    iterator begin(){
        return iterator(root);
    }

    iterator end(){
        return iterator(nullptr);
    }

};

#endif 