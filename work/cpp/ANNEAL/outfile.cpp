#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main(int argc , char * argv[]){
	char automobile[50];
	int year;
	double a_price , b_price;
	ofstream out;
	out.open("TXT");
	cout << "Enter the make and model of automobile : * " << endl;
	cin.getline (automobile , strlen (automobile ) );
	cout << "The length of automobile is : " << strlen(automobile )<<endl;
	cout << "Enter the model year";
	cin >> year;
	cout << "Enter the original asking price : " <<endl;
	cin >> a_price;
	b_price = 0.913 * a_price;
	cout << endl;
	cout << fixed;
	cout.precision(2);
	cout.setf(ios_base::showpoint);
	cout << "Make and model : " << automobile << endl;
	out << fixed;
	out.precision(2);
	out.setf(ios_base::showpoint );
	out << "Make and model : " << automobile <<endl;
	out.close();
	return 0;
}
