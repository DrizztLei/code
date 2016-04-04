#include <iostream>
using std::cout;
using std::cin;
using std::endl;

struct node {
	int start , swapNode , timesPop ;
	node * next;
	node (int n1 = 0 , int n2 = 0 , int n3 = 0 , node * n4 = NULL){
		start = n1;
		swapNode = n2 ;
		timesPop = n3;
		next = n4;
	}
};

void swap(int data[] , int idex1 , int idex2){
	int temp = data[idex1];
	data[idex1] = data[idex2];
	data[idex2] = temp;
}

void all_range(int n){
	node * stack = NULL , * tmp;
	int * a = new int[n];
	int i ;
	int start , swapNode , timesPop ;
	start = 0;
	for(int j = 0 ; j < n ; j++) a[j] = j;
	for(swapNode = 0 ; swapNode < n ;++ swapNode)
		stack = new node(start, swapNode , 0 , stack);
	while(stack != NULL){
		tmp = stack;
		stack = stack -> next;
		if(tmp -> start == n-1){
			for(i = 0 ; i < n ; ++i) cout << a[i] << "\t" ;
			cout << endl;
		}
		else {
			swap(a , tmp -> start , tmp -> swapNode);
			if( tmp -> timesPop == 0) {
				stack = new node(tmp->start , tmp->swapNode , 1 , stack);
				++tmp->start;
				for(tmp -> swapNode = tmp -> start;tmp -> swapNode < n; ++ tmp->swapNode)
					stack = new node(tmp -> start , tmp -> swapNode , 0 , stack);
			}
		}
		delete tmp;
	}
}
//The method is to prove if the matrix can be changed really by XOR(^) when we call the function
void changed(int * temp){
	temp[1] ^= temp[0];
	temp[0] ^= temp[1];
	temp[1] ^= temp[0];
}


int main(int argc , char ** argv){
	
	all_range(4);
	return 0;
}

