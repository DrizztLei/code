#ifndef TABTENN1_H_
#define TABTENN1_H_
using namespace std;
class TableTennsPlayer
{
 private:
	enum{LEN = 20};
	char firstname[LIM];
	char lastname[LIM];
	bool hasTable;
 public:
	TableTennsPlayer(const char * fn = "none" , const char * ln = "none" , bool ht = false);
	void Name()const;
	bool HasTable() const{ return hasTable;}
	void ResetTable(bool v){ hasTable = v ;}
};

class RatedPlayer: public TableTennsPlayer
{
 private:
	unsigned int rating;
 public:
	RatedPlayer(unsigned int r = 0 , const char * fn = "none" , const char * ln = "none" , bool ht = false );
	RatedPlayer(unsigned int r , const TableTennsPlayer & tp);
	unsigned int Rating(){return rating;}
	void ResetRating (unsigned int r) {rating = r;}
}

#endif
