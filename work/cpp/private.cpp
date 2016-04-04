#include <iostream>
#include "private.h"
using namespace std;
int integer = 2456;
void test:: print(){}
void test :: doit (){
		cout << "We'll make it ."<<endl;
	}
int main(){
	test *temp = new test();
	cout << ::integer<<endl;
	cout << (*temp).integer <<endl;
	(*temp).print();
	(*temp).doit();
	return 0;
}
