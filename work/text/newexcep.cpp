#include <new>
#include <iostream>
#include <cstdlib>

using namespace std;

struct Big{
	double stuff[20000];
};

int main(int argc ,char * argv[]){
	Big * bp;
	try{
		cout<<"trying to get a big block of memory : \n";
		bp = new Big[100];
		cout << "Got past the new request : " << 100 * 20000 <<endl;
	}catch(bad_alloc & bm){
		cout << "Catch the exception : \n";
		cout << bm.what() << endl;
		exit(EXIT_FAILURE);
	}
	cout << bp[0].stuff[0]<<endl;
	delete[] bp;
	return 0;
}
