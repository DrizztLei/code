#include "tabtenn0.h"
#include <iostream>
#include <cstring>
using namespace std;
TableTennisPlayer::TableTennisPlayer (const char * fn , const char * ln , bool ht){
	strncpy (firstname , ln , LIM - 1);
	firstname[LIM - 1] = '\0';
	strncpy (lastname , ln , LIM - 1);
	lastname [LIM - 1 ] = '\0';
	hasTable = ht;
}

void TableTennisPlayer::Name()const
{
	cout << lastname << " , " << firstname<<endl;
}

