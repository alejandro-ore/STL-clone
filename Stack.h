#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template<typename T>
class Stack{
private:

    struct node{
        T data;
        node *next=nullptr;
        node(const T &data):data(data){}
    };

    node *_top=nullptr;
    int _size=0;

public:

    Stack(){}

    Stack(const Stack<T> &other){
        if(other._size!=0){
            node *current=other._top->next;
            this->_top=new node(other._top->data);
            node *this_node=this->_top;
            while(current!=nullptr){
                node *n=new node(current->data);
                this_node->next=n;
                this_node=n;
                current=current->next;
            }
            this->_size=other._size;
        }
    }

    Stack<T> &operator=(const Stack<T> &other){
        if(this==&other) return *this;
        if(other._size!=0){
            node *current=other._top->next;
            this->_top=new node(other._top->data);
            node *this_node=this->_top;
            while(current!=nullptr){
                node *n=new node(current->data);
                this_node->next=n;
                this_node=n;
                current=current->next;
            }
            this->_size=other._size;
        }
        return *this;
    }

    ~Stack(){
        node *current=_top,*prev=_top;
        while(current!=nullptr){
            current=current->next;
            delete prev;
            prev=current;
        }
    }

    void push(const T &data){
        if(_size==0){
            _top=new node(data);
            _size++;
            return;
        }
        node *n=new node(data);
        n->next=_top;
        _top=n;
        _size++;
    }

    void pop(){
        if(_size==0) return;
        node *n=_top;
        _top=_top->next;
        delete n;
        _size--;
    }

    T &top(){
        return _top->data;
    }

    int size(){
        return _size;
    }

    bool empty(){
        return _size==0;
    }

};

#endif