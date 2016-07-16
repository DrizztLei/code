#include <iostream>
using namespace std;


int main(int argc ,char * argb[]){
	int temp = 234;
	int const & hello = temp;
	const int & world = temp;
	int * const haha = & temp;
	const int * hah2 = & temp;
	int const * hah3 = & temp;
	int const * const hah4 = & temp;
	//	int & const a = temp;
	//	world = 234;
	cout << "TEMP : "<<temp<<endl;
	//	hello = 23;
	return 0;
}
