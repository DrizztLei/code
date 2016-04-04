#include <iostream>
#include "dma.h"

using namespace std;
int main(int argc ,char * argv[])
{
	baseDMA shirt("Portabelly" , 78);
	lacksDMA ballon ("red" , "Billom" , 3);
	hasDMA map("Meractor " , "Buffalo Keys" , 34);
	cout << shirt << endl;
	cout << ballon << endl;
	cout << map << endl;
	lacksDMA baseDMA2 (ballon);
	hasDMA map2;
	cout << baseDMA2 <<endl;
	cout <<< map2 << endl;
	return 0;
}
	
