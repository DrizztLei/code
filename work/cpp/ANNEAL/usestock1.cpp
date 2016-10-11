#include <iostream>
#include "stock1.h"
using namespace std;

int main(int argc , char * argv[]){
	using std :: cout;
	using std :: ios_base;
	cout.precision(2);
	cout.setf(ios_base:: fixed , ios_base :: floatfield);
	cout.setf(ios_base :: showpoint);

	cout << "Using constructors to create new objects \n";
	Stock stock1 ("NanoSmart " , 12 ,20.0);
	stock1.show();
	Stock stock2 = Stock("Boffo Objects" , 2 ,2.0);
	stock2.show();

	cout << "Assingning stock1 to stock2 : \n" ;
	stock2 = stock1;
	stock1.show();
	stock2.show();

	cout<< "Changing the stock1 now " << endl;
	stock1 = Stock("Nifty Foods " , 10 , 50.0);
	cout << "Revised the stock1: " << endl;
	stock1.show();
	cout << "DONE > ." <<endl;
	return 0;
}
