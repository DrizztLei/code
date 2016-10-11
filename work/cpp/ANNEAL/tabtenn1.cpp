#include <iostream>
#include "tabtenn1.h"
#include <cstring>

using namespace std;

TableTennisPlayser :: TableTennisPlayser(const cahr * fn , const char * ln , bool ht){
	strncpy (firstname , fn , LIM - 1);
	firstname[LIM - 1] = '\0';
	strncpy (lastname , fn , LIM - 1);
	lastname[LIM - 1] = '\0';
	hasTable = ht;
}

void TableTennisPlayser :: Name() const
{
	cout<<lastname<<" , "<< firstname<<endl;
}	

RatedPlayer :: RatedPlayer (unsigned int r , const char * fn , const char * ln , bool ht) : TableTennisPlayser(fn , ln , ht)
{
	rating = r;
}																							

RatedPlayer :: RatedPlayer(unsigned int r , const TableTennisPlayser & tp): TableTennisPlayser (tp) , rating(r)
{
	
}	
	
