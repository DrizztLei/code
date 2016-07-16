#include<iostream>
#include<exception>
using namespace std;
const int MAXSIZE = 100;
struct orderStack {
	int data[MAXSIZE];
	int top_p;
};

void init(orderStack & s){
	s.top_p = -1;
}

bool isEmpty(const orderStack & s){
	return s.top_p == -1;
}

void push(orderStack & s , int info) throw (exception){
	if(s.top_p == MAXSIZE -1) {
		cout << "Over . Please check and do again .";
		throw "Stack over .";
	}
	s.data[++s.top_p] = info;
}

int pop(orderStack & s){
	if(s.top_p == -1) throw "Arrays out of bounds .";
	return s.data[s.top_p--];
}

int top(const orderStack & s){
	return s.data[s.top_p];
}

int main(int argc , char ** argv){
	orderStack temp;
	init(temp);
	cout << isEmpty(temp) << endl;
	push(temp , 23456);
	cout << top(temp) << endl;
	return 0;
}
