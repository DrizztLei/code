#include <iostream>
using namespace std;
struct node {
	int data;
	node * prev , * next;
};

void init(node * head , node * tail)
{
	head = new node;
	tail = new node;
	head -> next = NULL;
	head -> prev = NULL;
	tail -> next = NULL;
	tail -> prev = NULL;
}

void insert(node * head , int i , int x)
{
	node * temp = head;
	for(int k = 0 ; k < i ; k++) temp = temp->next;
	node * result = new node;
	result -> data = x ;
	result -> prev = temp;
	result -> next = temp -> next;
	temp -> next = result;
	result -> next -> prev = result;
}

void remove(node * head , int i)
{
	node * temp = head , * result;
	for(int k = 0 ; k < i ; k++) temp = temp->next;
	result = temp -> next;
	temp -> next = result -> next;
	result -> next -> prev = temp;
	delete result;
}
int main(int argc ,char * argv[])
{
	return 0;
}
