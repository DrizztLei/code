#include <iostream>
#include "stock1.h"
#include <cstring>
using namespace std;

Stock :: Stock(){
	cout << "The object was called by the struct" << endl;
	cout << "Default constructor called ." << endl;
	strcpy (company , "no name");
}

Stock :: Stock (const char * so , int n , double pr){
	cout << "Constructor using " << *so << " called \n";
	strncpy (company , so , 29);
	company[29] = '\n';
	if( n < 0){
		cerr << "number of shares isn't in right state . "<<endl;
	}else{
		shares = n;
	}
	share_val = pr;
	set_tot();
}

Stock :: ~ Stock()
{
	cout << "Byes " << company << "!\n";
}

void Stock :: buy(int num , double price ){
	shares += num;
	share_val = price ;
	set_tot();
}

void Stock :: sell(int num , double price){
	if(num > price ){
		cerr << "You can't sell more than you have"<<endl;
	}else {
		shares -= num;
		share_val = price;
		set_tot();
	}
}

void Stock :: update(double price){
	share_val = price;
	set_tot();
}

void Stock :: show(){
	cout << "Company : " << company << " Shares: " << shares << endl << " Share Price :$ " << share_val << " Total Worth : $ " << total_val << endl;
}

//int main(int argc ,char * argv[]){
//	cout << "ALL THING DONE SUDDENLY >> ." <<  endl ;
//	return 0;
//}
