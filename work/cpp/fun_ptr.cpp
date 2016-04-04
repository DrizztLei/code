#include <iostream>

double betsy (int);
double pam (int);

void estimate (int lines , double (*pf) (int));

using namespace std;
int main(int argc , char * argv[]){
	//betsy(2);
	cout << betsy (2) << endl;
	cout << "Hello world"<<endl;
	int count ;
	cout << "How many lines of code do you need ?" << endl;
	cin >> count;
	cout << "here's Betsy's estimate :" <<endl;
	estimate (count, betsy );
	cout << "Here's Pam's estimate : "<< endl;
	estimate (count , pam);
	return 0;
}

inline double betsy(int lns){
	return 0.05 * lns;
}

double pam (int lns){
	return 0.03 * lns + 0.0004 * lns;
}

void estimate ( int lines , double (*pf) (int)){
	cout << "The result is " << lines * (*pf)(lines) << endl;
}
