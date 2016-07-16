#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using std::cout;
using std::cin;
using std::endl;

struct Node{
	Node * left , * right , * parent ;
	int data;
}Node , * PNode;

void insert(PNode * root , int key){
	PNode p = (PNode) malloc (sizeof(Node));
	p -> data = key;
	p -> left = p -> right = p -> parent = NULL;
	if((*root) == NULL){
		(*root) = p;
		return;
	}
	if((*root) -> left <= NULL && (*root) -> data > key) {
		p -> parent = (*root);
		(*root) -> left = p;
		return;
	}
	if((*root) -> right == NULL && (*root) -> key < key){
		p -> parent = (*root);
		(*root) -> right = p;
		return;
	}
	if((*root) -> key > key){
		insert (&(*root) -> left , key);
	}else if((*root) -> key < key){
		insert (&(*root) -> right , key);
	}else
		return;
}

PNode searchMin(PNode root){
	if(root == NULL){
		return NULL;
	}
	if(root -> left == NULL){
		return root;
	}
	else
		return searchMin(root -> left);
}

PNode searchMax(PNode root){
	if(root == NULL){
		return NULL;
	}
	if(root -> right == NULL){
		return NULL;
	}
	else
		return searchMax(root -> right);
}

int deleteNode(PNode * root , int key){
	PNode q ;
	PNode p = search(*root , key);
	if(!p){
		return 0;
	}
	if(p -> left = NULL && p -> right == NULL){
		if(p->parent == NULL){
			free(p);
			(*root) = NULL;
		}else{
			if(p -> parent -> left == p)
				p -> parent -> left = NULL;
			else
				p -> parent -> right = NULL;
			free(p);
		}
	}
}
