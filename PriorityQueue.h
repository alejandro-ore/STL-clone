#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include "Vector.h"
using namespace std;

template<typename T,typename func=less<T>>
class PriorityQueue{
private:

    Vector<T> arr;

    void heapify_down(int x){
        int left,right,big;
        while(true){
            left=2*x+1;
            right=2*x+2;
            big=x;

            if(left<arr.size()&&func()(arr[left],arr[big])){
                big=left;
            }
            if(right<arr.size()&&func()(arr[right],arr[big])){
                big=right;
            }
            if(big==x) break;
            
            swap(arr[x],arr[big]);
            x=big;
        }
    }

    void heapify_up(int x){
        int parent=(x-1)/2;
        while(x>0&&func()(arr[x],arr[parent])){
            swap(arr[x],arr[parent]);
            x=parent;
            parent=(x-1)/2;
        }
    }

public:

    PriorityQueue(){}

    ~PriorityQueue(){}

    PriorityQueue(const PriorityQueue<T,func> &other){
        this->arr=other.arr;
    }

    PriorityQueue<T,func> &operator=(const PriorityQueue<T,func> &other){
        if(this==&other) return *this;
        this->arr=other.arr;
        return *this;
    }

    void push(const T &key){
        arr.push_back(key);
        heapify_up(arr.size()-1);
    }

    int top(){
        return arr[0];
    }

    void pop(){
        if(arr.size()!=0){
            arr[0]=arr[arr.size()-1];
            arr.pop_back();
            heapify_down(0);
            return;
        }
        throw runtime_error("queue is empty");
    }

    bool empty(){
        return arr.size()==0;
    }

    int size(){
        return arr.size();
    }

};

#endif