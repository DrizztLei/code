#include <iostream>
using std::cout;
using std::cin;
using std::endl;
template <class T>
struct node{
	T data;
	node * left , * right;
	node(T info = NULL , node * l = NULL , node * r = NULL){data = info ; left = l ; right = r;}
};
/**
template<class T>
void preOrder(node<T> * t){ // DLR 
	if(t == NULL) return;
	cout << t->data << "\t";
	preOrder(t->left);
	preOrder(t->right);
}
template<class T>
void postOrder(node<T> * t){ // LRD
	if(t == NULL) return ;
	postOrder(t -> left);
	postOrder(t -> right);
	cout << t -> data << "\r";
}

template<class T>
void midOrder(node<T> * t){ // LDR
	if(t==NULL) return;
	midOrder(t->left);
	cout << t->data << "\t";
	midOrder(t->right);
}
*/
template <class T>
struct Snode{
	node<T> * data;
	Snode  * next;
	Snode(node<T> * t , Snode<T> * n = NULL){data = t; next = n;}
};

template<class T>
void preOrder(node<T> * root){
	Snode<T> * stack = new Snode<T>(root);
	node<T> * current;
	Snode<T> * tmp;
	cout << "Pre Traversal ." << endl;
	while(stack != NULL){
		current = stack -> data;
		tmp = stack;
		stack = stack -> next;
		delete tmp;
		cout << current -> data;
		if(current -> right != NULL)
			stack = new Snode<T> (current -> right , stack);
		if(current -> left != NULL)
			stack = new Snode<T> (current -> left , stack);
	}
}
