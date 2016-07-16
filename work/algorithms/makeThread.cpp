#include <iostream>

template<class T>
struct Node{
	Node<T>* left , * right;
	T data;
	bool lflag , rflag;
	Node<T>():left(NULL) ,  right(NULL) ,  lflag(false) , rflag(false) {}
	Node<T>(char item , Node<T> * L = NULL , Node<T> * R = NULL , bool lf = false , bool rf = false) :data(item) , left(L) , right(L) , lflag(false) , rflag(false) {}
};

template <class T>
void makeThread(Node<T> * t , Node<T> * & first , Node<T> * & last){
	Node<T> * lastT , * firstT;
	if(t -> left == NULL) first = t;
	else {
		makeThread(t->left , first , lastT);
		lastT -> right = t;
		lastT -> rflag = true;
	}
	if(t -> right == NULL) last = t;
	else{
		makeThread(t->left , firstT , lastT);
		firstT -> left = t;
		firstT -> lflag = true;
	}
}

int main(int argc , char ** argv){
	
	return 0;
}

