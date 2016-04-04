#include <iostream>
using std::cout;
using std::endl;
using std::cin;
template <class T>
class Data{
public:
	T data;
	Data * next;
	int position;
};
template <class T>
class Stack{
public:
	Data<T> Node;
	void init();
	bool isEmpty();
	void push(T x);
};

template<class T>
void Stack<T>::init(){
	Node.next = NULL;
	Node.position = -1;
}
template<class T>
bool Stack<T>::isEmpty(){
	return Node.position == -1;
}

template<class T>
void Stack<T>::push(T x){
	Data<T> temp = x;
	temp.next = & Node;
	Node = temp;
	Node.position = Node.next->position + 1;
}


int main(int argc , char ** argv){
	Stack<int> * stack = new Stack<int>();
	stack -> init();
	return 0;
}
