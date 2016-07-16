#include <iostream>
using std::cout;
using std::endl;
using std::cin;
template<class T>
struct Node{
	T data;
	Node<T> * left , * right;
};



template<class T>
struct Snode{
	Node<T> * root;
	int TimesPop;
	Snode<T> * next;
	Snode<T>(Node<T> * t = NULL , int Integer = 0 , Snode<T> * Next = NULL){root = t ; TimesPop = Integer ; next = Next;
	}
};

template<class T>
void midOrder(Node<T> * root){
	Snode<T> * stack = new Snode<T>(root);
	Snode<T> * current;

	cout << "Mid Traversal . " << endl;
	while(stack != NULL){
		current = stack;
		stack = stack -> next;
		if(++current -> TimesPop == 2){
			cout << current -> root -> data;
			if(current -> root -> right != NULL)
				stack = new Snode<T>(current -> root -> right , 0 , stack);
			delete current;
		}
		else {
			current -> next = stack;
			stack = current;
			if(current -> root -> left != NULL)
				stack = new Snode<T> (current -> root -> left , 0 ,stack);
		}
	}
}
