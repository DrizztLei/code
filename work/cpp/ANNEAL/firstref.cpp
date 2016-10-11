#include <iostream>

using namespace std;

int main(int argc , char * argv[]){
	int rats = 101;
	int * pt = & rats;
	int & biness = (*pt);
	int count = 290;
	pt = & count ;
	cout<<"RAT IS : "<< rats <<endl;
	cout<<"*PT IS :" << *pt <<endl;
	cout<<"&BINESS IS :"<<biness<<endl;
	
	return 0;
}
