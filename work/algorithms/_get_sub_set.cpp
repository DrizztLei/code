#include <iostream>
#include <cstring>
using std::cout;
using std::cin;
using std::cout;
using std::string;
using std::endl;

void show(bool * check , char * output , int length){
	for(int i = 0 ; i < length ; i++)
		if(check[i]) cout << output[i] << " ";
	cout <<  "}";
	cout << endl;
}
void _show_sub_set(string  expression){
	int length = expression.length();
	char * temp = new char[length];
	int count = 0;
	for(int i = 0 ; i < length ; i++) {
		if(!(expression[i] == ' ' || expression[i] == '\t')) temp[count++] = expression[i];
	}
	temp[count]	= '\0';
	int char_length = count;
	bool * check = new bool[char_length];
	for(int select_length = 0 ; select_length <= char_length ; select_length++){
		for(int start = 0 ; start + select_length <= char_length ; start++){
			for(int select_point = start ; select_point < start + select_length ; select_point++){
				//cout << "Select_point : " << select_point << endl;
				//cout <<  "start : " << start << endl;
				//cout << "select_length : " << select_length << endl;
				for(int i = 0 ; i < char_length ; i++){
					check[i] = (i >= select_point && i <select_point + select_length)?true:false;
					cout << check[i] << "\t";
					//if(i+1 == char_length) cout << "for check ." << endl <<"select length : " << select_length << endl;
				}
				for(int count = select_point ; count < char_length ; count++){
					if(count == select_point) {
						cout <<  "{" ;
						show(check , temp , char_length);
						check[count] = false;
					}else if(check[count]){
						continue;
					}else if(!check[count]){
						check[count] = true;
						cout <<  "{";
						show(check , temp , char_length);
						check[count] = false;
					}
				}
			}
		}
	}
}

int main(int argc , char ** argv){
	string  expression = "";
	cout << "Input the expression : " << endl;
	getline(cin , expression);
	_show_sub_set(expression);
	return 0;
}
