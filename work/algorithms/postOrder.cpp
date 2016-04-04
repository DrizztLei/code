#include <iostream>
using std::cout;
using std::cin;
using std::endl;
template<class T>
struct Node{
	T info;
	Node * left , * right;
	Node<T>(T data = NULL , Node<T> * l = NULL ,Node<T> *  r = NULL){info = data ; left = l ; right = r;}
};

template<class T>
struct Snode{
	Node<T> * root;
	int TimesPop;
	Snode<T> * next;
	Snode<T>(Node<T> * r = NULL , int t = 0 , Snode * n = NULL) : root(r) , TimesPop(r) , next(n) {}
};

template <class T>
void postOrder(Node<T> root){
	Snode<T> * stack = new Snode<T>(root);
	Snode<T> * current;
	cout << "Post Traversal ." << endl;
	while(stack != NULL){
		current = stack;
		stack = stack -> next;
		if(++current->TimesPop == 3){
			if(current->root->left != NULL)
				stack = new Snode<T>(current -> root -> left , 0 , stack);
		}else{
			if(current -> root -> right != NULL)
				stack = new Snode<T>(current -> root -> ri , 0 , stack);
		}
	}
}
