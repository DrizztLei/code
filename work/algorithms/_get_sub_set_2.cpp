#include <iostream>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::string;

void up(bool * check , int length){
	int count = 0;
	while(true){
		if(!check[count]) {
			check[count] = true;
			break;
		}else{
			check[count] = false;
			count++;
		}
	}
}

void show(bool * check , char * expression , int length){
	cout << "{ " ;
	for(int i = 0 ; i < length ; i ++){
		if(check[i]) {
			cout << expression[i] << " ";
		}
	}
	cout << "}" << endl;
}

void _get_sub(char * expression ,int length) {
	bool * check = new bool[length];
	for(int i = 0 ; i < length ; i++) check[i] = false;
	int count = 1 << length;
	cout << count << endl;
	for(int i = 0 ; i < count ; i++){
		up(check ,length);
		show(check , expression , length);
	}
}

int main(int argc , char ** argv){
	cout << "Input the numbers : " << endl;
	int n;
	cin >> n;
	char * temp = new char[n];
	cout << "Input your expression : " ;
	for(int i = 0 ; i < n ; i++){
		cin >> temp[i];
	}
	_get_sub(temp , n);
	delete [] temp;
	return 0;
}
