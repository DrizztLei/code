#include <iostream>
#include <new>
#include <cstring>
#include <string.h>
using namespace std;

struct set{
	int * data;
	int len;
};

void setOp(set a , set b , set & c , set & d){
	int * temp_in = new int[a.len+b.len];
	int count_a = 0;
	int count_b = 0;
	int count_c = 0;
	int count_d = 0;
	int result = a.len + b.len;
	c.data = new int[result];
	c.len = result;
	d.data = new int[result];
	d.len = result;
	while(count_a < a.len && count_b < b.len){
		if(a.data[count_a] == b.data[count_b]){
			cout << a.data[count_a] <<"\t==\t" << b.data[count_b]<<endl;
			d.data[count_d++] = a.data[count_a++];
			c.data[count_c++] = b.data[count_b++];
		}else if(a.data[count_a] < b.data[count_b]){
			c.data[count_c++] = a.data[count_a++];
		}else{
			c.data[count_c++] = b.data[count_b++];
		}
	}
	while(count_a < a.len) c.data[count_c++] = a.data[count_a++];
	c.data[count_c] = '\0';
	while(count_b < b.len) c.data[count_c++] = b.data[count_b++];
	d.data[count_d] = '\0';
}

int main(int argc ,char ** argv){
	set a;
	set b;
	a.len = 4;
	a.data = new int [4];
	for(int i = 0 ; i < 4 ; i++){
		a.data[i] = i*3;
		cout << a.data[i] <<  "\t" ;
	}
	cout << endl;
	b.len = 5;
	b.data = new int[5];
	for(int i = 0 ; i < 5 ; i++){
		b.data[i] = i;
		cout << b.data[i] << "\t";
	}
	cout << endl;
	set c;
	set d;
	setOp(a , b , c , d);
	for(int i = 0; i < 9 ;i++){
		cout<<c.data[i] <<"\t" ;
	}
	cout << endl;
	for(int i = 0; i < 9; i++){
		cout<<d.data[i] <<"\t";
	}
	cout << endl;
	return 0;
}
