#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;
using std::cin;

struct TreeNode{
	TreeNode * left , * right ;
	char elem;
};

TreeNode * BinaryTreeFormOrderings(char * inorder , char * aftorder , int length){
	if(length == 0){
		return NULL;
	}
	TreeNode * temp = new TreeNode;
	int rootIndex = 0;
	temp -> elem = *(aftorder + length - 1);
	cout << temp -> elem ;
	for( ; rootIndex < length ; rootIndex++){
		if(inorder[rootIndex] == *(aftorder + length - 1)) {
			break;
		}
	}
	temp -> left = BinaryTreeFormOrderings(inorder , aftorder , rootIndex);
	temp -> right = BinaryTreeFormOrderings(inorder + rootIndex + 1 , aftorder + rootIndex , length - rootIndex - 1);
	return temp;
}

int main(int argc , char ** argv){
	char * af = "AEFDHZMG";
	char * in = "ADEFGHMZ";
	BinaryTreeFormOrderings(in , af , 8);
	cout << endl;
	return 0;
}
