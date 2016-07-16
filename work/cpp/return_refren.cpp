#include <iostream>
#include <string>
using namespace std;
string & return_with_reference(){
	string result = "Result";
	//	string & temp = "The reference for string .";
	string & temp = result;
	return temp;
	//	fdklsajfklajdsf
}

int main(int argc , char * argv[]){
	return_with_reference() = "hello world";
	string temp = "wahaha";
	const string haha = "hello world";
	return_with_reference() = haha;
	return 0;
}
