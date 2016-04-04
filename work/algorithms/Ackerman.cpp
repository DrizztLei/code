#include <iostream>
using std::cin;
using std::endl;
using std::cout;

struct node{
	int data;
	node * next;
	node (int info=0 , node * nextNode = NULL){
			  data = info;
			  next = nextNode;
	}
};

int pop(node * & s){
	int data = s -> data;
	node * tmp = s;
	s = s -> next;
	delete tmp;
	return s -> data;
}

int Ackerman(int m , int n ){
	node * stack = NULL;
	stack = new node(m , stack);
	stack = new node(n , stack);

	while(true){
		n = pop(stack);
		if(stack == NULL )return n;
		m = pop(stack);
	}

	if(m != 0 && n != 0 ){
		stack = new node(m-1 , stack);
		stack = new node(m , stack);
		stack = new node(n-1 ,stack);
	}else if(m!= 0 && n == 0){
		stack = new node(m-1 ,stack);
		stack = new node(1 ,stack);
	}else stack = new node(n+1 , stack);
}

int main(int argc , char ** argv){
	return 0;
}
