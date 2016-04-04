#include <iostream>
#include "coordin.h"
using namespace std;
int main(){
	cout << "Hello world " << endl;
	rect rplace ;
	polar pplace ;
	cout << "Enter the x and y :"<<endl;
	while(cin >> rplace.x >> rplace.y){
		pplace = rect_to_polar(rplace);
		show_polar(pplace);
		cout << "Next two numbers (q to quit)";
	}
	cout << "Byes . ";
	return  0;
}
