#include <iostream>
using namespace std;
template <class T>
struct node{
	T data;
	node * next;
};
template<class T>
void init(node<T> & s)
{
	s = NULL;
}


template<class T>
void push(node<T> & s ,T data)
{
	node<T> temp = new node<T>;
	temp.data = data;
	temp.next = &s;
	s = temp;
}

template<class T>
T pop(node<T> & s){
	T temp = s.data;
	s = (*s->next);
	return temp;
}

int main (int argc ,char ** argv){
	return 0;
}
