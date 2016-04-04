#include <iostream>
#include <math.h>
using namespace std;
bool IsPrime(int n){
	if( n <=1 || n%2==0 ) return false;
	if( n==2 ) return true;
	int limit = sqrt(n) + 1;
	for(int i = 3 ; i <= limit ; i += 2)
		if(n % i == 0) return false;
	return true;
}

int main(int argc , char * argv[]){
	cout<< IsPrime(2345) <<endl;
	return 0;
}
