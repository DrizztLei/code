#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Test{
private:
public:
	Test (){}
	Test & get_object();
};

void getif(int * temp){
	temp = NULL;
}

void change(int * temp){
	(*temp) = 21345;
}

int test1(){
	int temp  = 213;
	int * d = & temp;
	cout << (*d) << endl;
	getif(d);
	cout << "==NULL? : " << (d == NULL) << endl;
	cout << (*d) << endl;
	change(d);
	cout << (*d) << endl;
 	return 0;
}
int main(int argc , char ** argv){
	return 0;
}
