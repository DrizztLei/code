#include <iostream>
#include <string>
using namespace std;
/**
   parent(i)
   return floor(i/2)
   left 2*i
   right 2*i+1
*/



void encapsulation(int *& result , int & r_length){
	string str = "";
	cout << "Input the expression you wanna : " << endl;
	while(str.length() == 0){
		getline(cin , str);
	}
	int length = str.length() , count = 0;
	int * temp = new int[length];
	for(int i = 0 ; i < length ; i++)
		temp[i] = 0;
	for(int i = 0 ; i < length ; i++){
		if(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'){
			cout << temp[count] << endl;
			count ++;
		}else{
			temp[count] = temp[count] * 10 + str[i] - '0';
		}
	}
	int * array = new int[++count];
	for(int i = 0 ; i < count ; i++){
		array[i] = temp[i];
		cout << array[i] << "\t" ;
	}
	cout << endl;
	result = array;
	r_length = count;
	delete temp;
}

int main(int argc, char ** argv){
	int * array , length;
	encapsulation(array , length);
	cout << length << endl;
	delete array;
	return 0;
}
