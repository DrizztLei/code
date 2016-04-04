#include <iostream>
using namespace std;

struct date{
	char name[20];
	mutable int test;
};

int main(int argc , char * argv[]){
	const date dd = {"dd" , 3456};
	dd.test = 2345;
	cout<< dd.test << endl;
	return 0;
}
