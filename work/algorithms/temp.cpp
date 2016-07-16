#include <iostream>
using namespace std;

template <class T>
class Node{
public:
	T data;
	Node & link;
	Node<T>(){}
};

template<class T>
class LinearList{
private:
	Node<T> & first();
public:
	LinearList(){}
	~LinearList(){}
	LinearList<T> & Insert(const T& x);
};

template<class T>
LinearList<T> & LinearList<T> :: Insert(const T & x ){
	Node<T> * p = new Node<T>();
	p -> data = x;
	//p -> link = first;
	//first = p;
	return * this;
}

int main(int argc , char ** argv){
	LinearList<int> temp;
	temp.Insert(2);
	return 0;
}
