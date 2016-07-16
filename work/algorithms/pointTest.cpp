#include <iostream>
using namespace std;

void changed(char * temp){
	*temp = 'd';
}

struct node{
	int x;
};

void changeX(node temp){
	temp.x = 345678;
}

int main(int argc , char ** argv){
	char temp = '3';
	changed(&temp);
	cout << temp << endl;
	node test;
	test.x = 2345;
	cout << test.x << endl;
	node * hello;
	cout << test.x << endl;
	cout << "DONE ALL THINGS . " << endl;
	return 0;
}
