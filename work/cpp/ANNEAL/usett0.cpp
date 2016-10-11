#include <iostream>
#include "tabtenn0.h"
using namespace std;
int main(int argc ,char * argv[]){
	TableTennisPlayer * ttp = new TableTennisPlayer("fdf" , "fj" , true);
	(*ttp).Name();
	delete ttp;
	return 0;
}
