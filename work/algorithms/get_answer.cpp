#include <iostream>
#include <cstring>
#include <stdio.h>
using std::cout;
using std::endl;
using std::cin;
using std::string;


struct TreeNode{
    TreeNode * left , * right;
    char elem;
};

void BinaryTreeFormOrderings(char * inorder , char * preorder , int length){
    if(length == 0 ){
        return;
    }
    TreeNode * node = new TreeNode;
    node -> elem = *preorder;
    int rootIndex = 0;
    for(;rootIndex < length ; rootIndex++){
        if(inorder[rootIndex] == *preorder){
            break;
        }
    }
    BinaryTreeFormOrderings(inorder , preorder + 1 , rootIndex);
    BinaryTreeFormOrderings(inorder + rootIndex + 1 , preorder + rootIndex + 1 , length - (rootIndex + 1));
    cout << node -> elem ;
    return ;
}

int main(int argc, char ** argv){
    printf("Testing . \n");
    char * pr = "GDAFEMHZ";
    char * in = "ADEFGHMZ";
    BinaryTreeFormOrderings(in , pr , 8);
    printf("\n");
    return 0;
}
