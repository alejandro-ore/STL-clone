#ifndef LIST_H
#define LIST_H

template<typename T>
class List{
private:

	struct node{
		T data;
		node *next=nullptr;
        node *prev=nullptr;
		node(const T &key):data(key){}
	};

	node *_front=nullptr;
    node *_back=nullptr;
    int _size=0;

public:

	struct iterator{
    private:
        node *current;
        node *get_node(){
            return current;
        }
    public:
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
        iterator &operator--(){
            current=current->prev;
            return *this;
        }
        iterator operator--(int){
            iterator prev=*this;
            current=current->prev;
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

	};

	List(){}

    List(List<T> &other){
        if(other.size()!=0){
            this->_size=other._size;
            auto it=other.begin();
            _front=new node(*it);
            it++;
            node *current=this->_front,*prev=this->_front;
            for(it;it!=other.end();it++){
                current=new node(*it);
                if(prev){
                    prev->next=current;
                    prev=current;
                }
            }
            this->_back=current;
        }
    }

    List<T> operator=(List<T> &other){
        if(this==&other) return *this;
        if(other.size()!=0){
            this->_size=other._size;
            auto it=other.begin();
            _front=new node(*it);
            it++;
            node *current=this->_front,*prev=this->_front;
            for(it;it!=other.end();it++){
                current=new node(*it);
                if(prev){
                    prev->next=current;
                    prev=current;
                }
            }
            this->_back=current;
        }
        return *this;
    }

    ~List(){
        node *prev;
        node *current=_front;
        while(current!=nullptr){
            prev=current;
            current=current->next;
            delete prev;
        }
    }

    void push_back(const T &key){
        node *n=new node(key);
        n->prev=_back;
        if(_back) _back->next=n;
        _back=n;
        if(_size==0) _front=_back;
        _size++;
    }
    
	void push_front(const T &key){
        node *n=new node(key);
        n->next=_front;
        if(_front) _front->prev=n;
        _front=n;
        if(_size==0) _back=_front;
        _size++;
	}

    void pop_back(){
        if(_size==0) return;
        node *temp=_back;
        _back=_back->prev;
        _size--;
        delete temp;
        if(_size==0) _front=nullptr;
    }

    void pop_front(){
        if(_size==0) return;
        node *temp=_front;
        _front=_front->next;
        _size--;
        delete temp;
        if(_size==0) _back=nullptr;
    }

    int size(){
        return _size;
    }

    iterator begin(){
        return iterator(_front);
    }

    iterator end(){
        return iterator(nullptr);
    }

};

#endif 