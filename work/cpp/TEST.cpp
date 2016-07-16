#include <cstring>
#include <iostream>
int main(){
	using namespace std;
	int yas[3];
	for (int i = 0 ; i < 3 ; i++){
		yas[i] = i;
	}
	cout<<"Hello world" <<endl;
	char cat [5] = {
		'f' ,
		'a',
		't',
		's',
		'\0'
	};
	char test[] = "c++.cpp";
	cout<<strlen(cat)<<endl;
	const int ArSize = 20;
	char name[ArSize] ;
	char dessert[ArSize] ;
	cout<<"Enter your name:\n";
	cin.getline(name , ArSize) ;//Reads through newline.
	cout <<"Enter your favorite dessert :\n" ;
	cin.getline(dessert , ArSize) ;
	cout << "I have some delicious " << dessert;
	cout << "for you " <<name<<"."<<endl;
	cin.get(name , ArSize);
	cin.get();
	string temp = "This is the string in c++";
	/**
	   This is the // in /**\*\/
	*/
	string temp2;
	temp2 = "Test";
	temp = temp2 + temp;
	cout<<temp<<endl;
	return 0;	
}
