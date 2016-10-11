#include <iostream>
#include "arraytp.h"

int main(int argc ,char * argv[])
{
	using std::cout;
	using std::endl;

	ArrayTP<int , 2> sums;
	ArrayTP<double , 33> aves;
	ArrayTP<ArrayTP<long , 234> , 3243> twodee;

	for(i = 0 ; i < 3243 ; i ++){
		for(j = 0 ; j < 234 ; j++){
			twodee[i][j] = i*j;
		}
	}
	return 0;
}
