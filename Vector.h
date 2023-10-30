#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class Vector{
private:

    T *arr=nullptr;
    int _size=0;
    int capacity=8;

    void recapacity(int n){
        if(n<=capacity) return;
        T *temp=new T[n];
        for(int i=0;i<capacity;i++){
            temp[i]=arr[i];
        }
        delete arr;
        arr=temp;
        capacity=n;   
    }

public:

    struct iterator{
    private:
        Vector<T> *v;
        int pos;
    public:
        iterator(Vector<T> *v,int pos):v(v),pos(pos){}
        iterator(const iterator &other){
            this->v=other.v;
            this->pos=other.pos;
        }
        iterator operator=(const iterator &other){
            this->v=other.v;
            this->pos=other.pos;
        }
        iterator &operator++(){
            pos++;
            return *this;
        }
        iterator operator++(int){
            iterator prev=*this;
            pos++;
            return prev;
        }
        iterator &operator--(){
            pos--;
            return *this;
        }
        iterator operator--(int){
            iterator prev=*this;
            pos--;
            return prev;
        }
        iterator &operator+(int n){
            pos+=n;
            return *this;
        }
        iterator &operator-(int n){
            pos-=n;
            return *this;
        }
        bool operator==(const iterator &other){
            return this->pos==other.pos&&this->v==other.v;
        }
        bool operator!=(const iterator &other){
            return this->pos!=other.pos&&this->v==other.v;
        }
        T &operator*(){
            return (*v)[pos];
        }
        T *operator->(){
            return &(*v)[pos];
        }
    };

    Vector(){
        arr=new T[capacity];
    }

    ~Vector(){
        delete[] arr;
    }

    Vector(const Vector<T> &other){
        this->capacity=other.capacity;
        this->_size=other._size;
        this->arr=new T[capacity];
        for(int i=0;i<_size;i++){
            this->arr[i]=other.arr[i];
        }
    }

    Vector<T> &operator=(const Vector<T> &other){
        if(this==&other) return *this;
        this->capacity=other.capacity;
        this->_size=other._size;
        this->arr=new T[capacity];
        for(int i=0;i<_size;i++){
            this->arr[i]=other.arr[i];
        }
        return *this;
    }

    void push_back(T x){
        if(_size==capacity){
            recapacity(capacity*2);
        }
        arr[_size++]=x;
    }

    void pop_back(){
        if(_size==0) return;
        _size--;
    }

    void resize(int n,T x=T{0}){
        if(n<_size) return;
        if(n>capacity){
            recapacity(n);
        }
        for(int i=_size;i<n;i++){
            arr[i]=x;
        }
        _size=n;
    }

    int size(){
        return _size;
    }

    T &operator[](int n){
        return arr[n];
    }

    iterator begin(){
        return iterator(this,0);
    }

    iterator end(){
        return iterator(this,_size);
    }

};

#endif