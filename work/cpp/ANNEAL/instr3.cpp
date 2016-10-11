#include <iostream>
int main(){
	using namespace std;
	cout<<"Input your test :"<<endl;
	const int Size = 20;
	char name[Size];
	cin.get(name , Size ) .get();
	cout<<"The result is "<<name<<endl;

	return 0;
}
