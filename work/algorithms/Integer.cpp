#include <iostream>
using namespace std;
struct node{
	int data ;
	node * next;
};

void input(node * x)
{
	char ch;
	node * p;
	while(x)
		{
				p = x;
				x = x -> next;
				delete p;
		}
	cout<<"Input the number ."<<endl;
	while((ch = cin.get())!='\n'){
		p = new node;
		p -> data = ch - '0';
		p -> next = x;
		x = p;
	}
	if(x == NULL)
		{
			cout << "X == NULL" << endl;
			x = new node;
			x -> data = 0;
			x -> next = NULL;
		}
	while(x){
		cout << x -> data << endl;
		x = x -> next;
	}
	x = p;
}

void output(node * x)
{
	if(x==NULL) {
		cout << "NULL" << endl;
		return;
	}
	output(x->next);
	cout << x -> data << endl;
}

void add(node * n1 , node * n2 ,node * result)
{
	node * temp1 = n1 , * temp2 = n2 , * temp3 = result;
	int temp1_data = temp1 -> data , temp2_data = temp2 -> data , up = (temp1_data+temp2_data)/10 , result_data = (temp1_data + temp2_data + 0)%10;
	cout << "H" << endl;
	while(temp1 != NULL || temp2 != NULL)
		{
			result -> data = result_data;
			if(temp1 == NULL) temp1_data = 0;
			else{
				temp1 = temp1 -> next;
				temp1_data = temp1 -> data;
			}
			if(temp2 == NULL) {
				if(temp1 == NULL) return;
				temp2_data = 0;
			}else{
				temp2 = temp2 -> next;
				temp2_data = temp2 -> data;
			}
			result_data = (temp1_data + temp2_data + up) % 10;
			up = (temp1_data + temp2_data + up) /10;
			result = result -> next;
		}
}

int main(int argc ,char * argv[]){
	
	node * temp1;
	node * with = temp1;
	input(temp1);
	if(!temp1){
		cout << "What the fuck. " << endl;
	}
	while(with){
		cout << with -> data << endl;
	}
	while(temp1){
		with = temp1;
		temp1 = temp1 -> next;
		delete with;
	}
	//		output(temp1);
	//		node * temp2;
	//		input(temp2);
	//		output(temp2);
	//		node * result;
	//		cout << "Ha1" <<endl;
	//		add(temp1 , temp2 , result);
	//		output(result);
}
