# include <cstring>
# include <iostream>
# include <climits>

using namespace std;

int main(){
	float temp = 2342.321;
    cout << temp << endl;
	short xx;
    xx = 1;
    cout << xx << endl;
	int dd;
	char ch;
    ch = '2';
    cout << ch << endl;
	cout << "int is\t" << sizeof(int)<<"\tof Inter here"<<endl;
	dd = 65535;

	cout << "Over the limit of int "<< ++dd<<endl;
	return 0 ;

}
