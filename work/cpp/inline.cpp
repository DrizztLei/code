#include <iostream>



using namespace std;
inline double sqrt(double x){return x*x;}
int main(int argc ,char * argb[]){
	double a , b , c =3.4;
	a = sqrt(c);
	b = sqrt(c) - 2/sqrt(c);
	cout << "Result is :" << a << endl;
	cout << "Result is :" << b << endl;
	return 0;
}
