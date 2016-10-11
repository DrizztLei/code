#include <iostream>
#include <cstring>
#include <stdio.h>
class Stock
{
private :
	char company[20];
	int shares;
	double share_val;
	double total_val;
	inline	void set_tot(){total_val =share_val *total_val;}
public :
	void acuqire (const char * co , int n , double pr);
	void buy (int num , double price);
	void sell (int num , double price);
	void show();
	Stock();
	~ Stock();
};

void Stock :: buy(int num , double price){
	if (num < 0){
		std::cerr << "Number of shares purchased can't be nagative ." << std::endl;
	}
	else {
		std::cout << "All thinngs done " << std::endl;
	}
}

void Stock :: sell(int num , double price ){
	printf("We sell in price of %d and the amount is %d" , price ,(int)num);
}

Stock :: Stock(){
}

Stock :: ~Stock(){
	using namespace std;
	cout << "The object was cleared " <<endl;
}

int main(int argc ,char * argv[]){
	using std :: cerr;
	cerr << "wo \a do it\n " ;
	Stock stock = Stock();
	Stock * Stock_1 = new Stock();
	Stock Stock_2();
	return 0;
}
