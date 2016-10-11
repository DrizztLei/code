#include <iostream>
#include <string>
#include <new>

using namespace std;

const int BUF = 512;

class JustTesting
{
private:
	string words;
	int number;
public:
	JustTesting( const string & s = "Just Testing ." , int n = 0){words = s ; number = n ; cout << "Object has been created now ." << endl;}
	~JustTesting(){}
	void show(){cout<<"String is :" <<words << "\nnumber is :" << number <<endl;}
};


int main(int argc , char * argv[]){
	char * buffer = new char[BUF];
	JustTesting * p1 , * p2;
	p1 = new JustTesting("hahahah" , 2345);
	p2 = new JustTesting();
	cout << "Memory block address :\n" << "buffer : "<<p1<<endl;
	JustTesting * import = new (buffer) JustTesting;
	cout << "This is the (void *) buffer " << (void *) buffer << "\t heap: " <<import <<endl;
	p1 -> show();
	p2 -> show();
	import -> show();
	//	delete p2;
	//	delete p1;
	cout << "Done here "<< endl;
	cout << "Now we test the new (buffer + sizeof (justTesting)) JustTesting(\"Buffer\" , 23456)"<<endl;
	//	JustTesting * very = new (buffer + 2*sizeof(JustTesting) JustTesting ("Very nice"));
	//	very -> show();
	delete p2;
	delete p1;
	//	delete very;
	import -> ~JustTesting ();
	delete[] buffer;
	return 0;
	}
