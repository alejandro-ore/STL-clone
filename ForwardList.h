#ifndef FORWARDLIST_H
#define FORWARDLIST_H

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

 //       template<typename K>
   //     friend class HashMap<T,K>;
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

    iterator begin(){
        return iterator(root);
    }

    iterator end(){
        return iterator(nullptr);
    }

    //template<typename K>
    //friend class HashMap<T,K>;
};

#endif 