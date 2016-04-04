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

int main(int argc , char ** argv){

	return 0;
}
