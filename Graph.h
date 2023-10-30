#ifndef GRAPH_H
#define GRAPH_H

#include "HashMap.h"

template<typename T=int,typename K=int>
class Graph{
private:
	
	HashMap<T,HashMap<T,K>> vertices;
	int V=0; // numero de vertices
	int E=0; // numero de aristas

public:

	Graph(){}

	Graph(const Graph<T,K> &other){
		this->vertices=other.vertices;
		this->V=other.V;
		this->E=other.E;
	}

	Graph<T,K> &operator=(const Graph<T,K> &other){
		if(this==&other) return *this;
		this->vertices=other.vertices;
		this->V=other.V;
		this->E=other.E;
		return *this;
	}
	
	~Graph(){}
	
	void insert_vertex(const T &key){
		if(vertices.find(key)!=vertices.end()){
			vertices.insert(key,HashMap<T,K>());
			V++;
		}
	}
	
	void create_edge(const T &v1,const T &v2,const K &weight=K{1}){
		auto t1=vertices.find(v1);
		auto t2=vertices.find(v2);
		
		if(t1!=vertices.end()&&t2!=vertices.end()) return;

		vertices[v1].insert(v2,weight);
		vertices[v2].insert(v1,weight);
	}

	void clear(){
		vertices.clear();
		V=0;
		E=0;
	};

	void print(){

		for (auto it = vertices.begin(); it != vertices.end();it++)
		{
			if(it->second.size()==0) continue;
			cout << it->first << ": "<<endl;
			for (auto it2 = it->second.begin(); it2 != it->second.end();it2++)
			{
				cout << "(edge: " << it2->first <<", val:" << it2->second << ")";
			}
			cout << endl<<endl;
		}
	}

};

#endif