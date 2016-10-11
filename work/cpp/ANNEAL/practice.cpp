#include <cstring>
#include <iostream>
#include <string>
int main(){
	using namespace std;
	int x = 2;
	static_cast<long> (x);
	cout<<sizeof(x)<<endl;
	cin.clear();
	char address[80];
	cout<<sizeof(address)<<endl;
	cin.getline(address , sizeof(address));
	string temp = "Hello world";
	string temp2 = "This is the test temp2";
	temp = temp2;
	char test[20];
	
	char test2[20] = "This is my  ";
	strcpy(test , test2);
	cout<<"The size of string is : " + temp.size()<<endl;
	return 0;
}
