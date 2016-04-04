#include <cstring>
#include <iostream>
#include "string.h"
using std::cin;
using std::cout;

int String :: num_strings = 0;

int String :: HowMany()
{
	return num_strings;
}

String :: String (const char * temp){
	len = std::strlen(temp);
	str = new char[len + 1];
	std::strcpy (str , temp);
	num_strings++;
}

String ::String(){
	len = 4;
	str = new char[4];
	str[0] = '\0';
	num_strings++;
}

String :: String (const String & string){
	num_strings++;
	len = string.len;
	str = new char[len+1];
	std::strcpy(str , string.str);
}

String :: ~String(){
	--num_strings;
	delete[] str;
}

String & String :: operator=(const String & temp){
	if(this == &temp){
		return * this;
	}
	delete [] str;
	len = temp.len;
	str = new char[len + 1];
	std::strcpy(str , temp.str);
	return *this;
}

String & String :: operator=(const char * temp ){
	delete [] str;
	len = std::strlen(temp);
	str = new char[len + 1];
	std::strcpy (str , temp);
	return * this;
}

char & String :: operator[] (int i){
	return str[i];
}

const char & String :: operator[](int i) const{
	return str[i];
}

bool operator<(const String & str1 , const String & str2){
	return (std::strcmp(str1.str , str2.str));
}

bool operator==(const String & str1 , const String & str2){
	return (std::strcmp(str1.str , str2.str) == 0);
}

ostream & operator<<(ostream & os , const String & temp){
	os << temp.str;
	return os;
}

istream & operator>>(istream & is , String & string){
	char temp [String::CINLIM];
	is.get(temp , String::CINLIM);
	if(is){
		string = temp;
	}
	while(is && is.get()!='\n'){
		continue;
	}
	return is;
}
int main(int argc ,char * argv[]){
		return 0;
}
