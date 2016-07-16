#include <iostream>

using namespace std;

class hello{
private :
	int a;
	void haha();
	void print(){cout << "haha prit"<<endl;}
public :
	void set();
};

void hello :: haha(){
	cout << "Haha" <<endl;
}

void hello :: haha(){
	cout<<"This is my december ." << endl;
}

int main(int argc ,char * argv[]){
	hello he = hello();
	hello haha();
	hello * temp = new hello();
	(*temp).print();
	cout << he.a<<endl;
	return 0;
}
