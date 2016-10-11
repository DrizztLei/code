#ifndef STRING_H_
#define STRING_H_
#include <iostream>

using std :: ostream;
using std :: istream;

class String
{
 private :
	char * str;
	int len;
	static int num_strings;
	static const int CINLIM = 80;
 public :
	String(const char *);
	String();
	String(const String &);
	~String();
	//overloaded operator methods
	String & operator= (const String &);
	String & operator= (const char *);
	char & operator[] (int );
	const char & operator[] (int) const;
	
	//overloaded operator friends
    friend bool operator<(const String & , const String &);
	friend bool operator>(const String & , const String &);
	friend bool operator==(const String & , const String &);
	friend ostream & operator<<(ostream & , const String &);
	friend istream & operator>>(istream & , String &);
	static int HowMany();
};
#endif
