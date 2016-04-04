#ifndef LINK_H_
#define LINK_H_
#include <iostream>
#include <exception>
using std::cout;
using std::cin;
using std::endl;

template<class T>
class Link
{
 private:
	struct node{
		T info;
		node * prev , * next;
	};
	node * Node;
 public:
	~Link();
	Link(T data , int position);
	Link(T data);
	Link();
	void add();
	bool insert(int position);
	bool remove(int position);
	int search(T target);
	bool init();
};

template<class T>
Link<T> :: Link(T data){
	node * position = Node;
	while(position->next != NULL){
		position = position -> next;
	}
	position->info = data;
}

template<class T>
Link<T> :: Link(){
	Node -> prev = Node -> next = NULL;
}

template<class T>
Link<T> :: Link(T data , int position){
	try{ 
	node * temp = & Node;
	for(int i = 0 ; i < position ; i++) temp = temp -> next;
	node * result = new node;
	result -> info = data;
	result -> next = temp -> next;
	result -> prev = temp;
	result -> next -> prev = result;
	temp -> next = result;
	}catch (std::exception & e) {
		cout << "Exception : " << e.what() << endl;
		throw exception();
	}
}

template<class T>
Link<T> :: ~Link(){
	if(Node == NULL) return;
	node * temp = Node ;
	while(Node != NULL){
		delete temp;
		temp = Node;
		Node = Node -> next;
	}
}

#endif
