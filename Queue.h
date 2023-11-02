#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template<typename T>
class Queue{
private:

    struct node{
        T data;
        node *next=nullptr;
        node(const T &data):data(data){}
    };

    node *_front=nullptr;
    node *_back=nullptr;
    int _size=0;

public:

    Queue(){}

    ~Queue(){
        node *current=_front,*prev=_front;
        while(current!=nullptr){
            current=current->next;
            delete prev;
            prev=current;
        }
    }

    Queue(const Queue<T> &other){
        node *current=other._front,*this_node;
        this_node=new node(current->data);
        this->_front=this_node;
        current=current->next;
        while(current!=nullptr){
            node *n=new node(current->data);
            this_node->next=n;
            this_node=n;
            current=current->next;
        }
        this->_back=this_node;
        this->_size=other._size;
    }

    Queue<T> &operator=(const Queue<T> &other){
        if(this==&other) return *this;
        node *current=other._front,*this_node;
        this_node=new node(current->data);
        this->_front=this_node;
        current=current->next;
        while(current!=nullptr){
            node *n=new node(current->data);
            this_node->next=n;
            this_node=n;
            current=current->next;
        }
        this->_back=this_node;
        this->_size=other._size;
        return *this;
    }

    void push(const T &data){
        if(_size==0){
            _front=new node(data);
            _back=_front;
            _size++;
            return;
        }
        node *n=new node(data);
        _back->next=n;
        _back=n;
        _size++;
    }

    void pop(){
        if(_size==0) return;
        node *n=_front;
        _front=_front->next;
        delete n;
        _size--;
    }

    T &front(){
        return _front->data;
    }

    T &back(){
        return _back->data;
    }

    int size(){
        return _size;
    }

    bool empty(){
        return _size==0;
    }

};

#endif