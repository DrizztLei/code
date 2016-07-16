#include <iostream>
#include <math.h>
using namespace std;
const int SIZE = 40;
struct seqList{
	int data[SIZE];
	int len;
};

void init(seqList & L){ L.len = 0; }
void clear(seqList & L){L.len = 0; }
int length(const seqList & L ){return L.len;}
int visit(const seqList & L , int i){return L.data[i];}
void traverse(const seqList & L)
{
	for (int i = 0 ; i < L.len; i++){
		cout << L.data[i] <<endl;
	}
}

int search (const seqList list , int & info){
	int i;
	for(i = 0 ; i < list.len && list.data[i] != info ;i++){
		if(i == list.len ) return -1;
	}
	return i;
}

int prior(const seqList & list , int info){
	int index = search(list , info);
	if(index == 0){
		cout << "Without driver behind ." << endl;
		return -1;
	}	
	return list.data[index - 1];
}

void insert(seqList & L , int i , int info){
	if(L.len == SIZE) {
		cout << "Malloc failed ." << endl;
		return;
	}
	for(int index = L.len; index > i ; index --){
		L.data[index] = L.data[index - 1];
	}
	L.data[i] = info;
	++L.len;
}

void remove(seqList & L , int i){
	int length = L.len;
	for(int index = i ; i < length - 1 ; i++ ){
		L.data[index] = L.data[index + 1];
	}
	--L.len;
}

int main(int argc , char * argv[]){
	return 0;
}
