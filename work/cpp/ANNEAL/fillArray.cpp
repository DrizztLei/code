#include <iostream>

int fill_array(double ar[] , int limit){
	using namespace std;
	double temp;
	int i ;
	for (i = 0 ; i < limit ; i ++){
		cout << "Enter value :" << (i+1) << endl;
		cin >> temp;
		if(!cin){
			cin.clear();
			while(cin.get() != '\n')
				continue;
			cout << "Bad input : input process terminalted .\n";
			break;
		}else if (temp < 0){
			break;
		}
		ar[i] = temp;
	}
	return i;
}

int main(int argc , char * argv[]){
	double array [20] ;
	fill_array(array , 20);
	return 0;
}
