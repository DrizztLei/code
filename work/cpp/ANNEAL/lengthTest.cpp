#include <iostream>
#include <cstring>
int main(int argc , char * argv[]){
	using namespace std;
	char temp [23] = "fjldksjflkdjslf";
	cout << "size of temp is : " << sizeof(temp)<<endl;
	cout << "strlen () of temp is " << strlen (temp)<<endl;
	cout << "The temp is : " << temp << endl;
	temp[4] = '\0';
	cout << "size of temp (changed) is : " << sizeof(temp) << endl;
	cout << "strlen () of temp (changed) is : " << strlen (temp) <<endl;
	cout << "The temp(changed) is : " << temp <<endl;
	return 0;
}
