#include <iostream>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::string;
/**
   void _show_sub_set(string expression){
   int length = expression.length();
   char * temp = new char[length];
   int count = 0;
   for(int i = 0 ; i < length ; i++) {
   if(!(expression[i] == ' ' || expression[i] == '\t')) temp[count++] = expression[i];
   }
   temp[count] = '\0';
   int char_length = count;
   bool * check = new bool[char_length];
   for(int i = 0 ; i < char_length ; i++){
   check[i] = false;
   }
   int end = 1 << char_length;
   for(int i = 0 ; i < end ; i++){

   }
   }
*/

void build(char * str , int * tag , int n){
	if(n == 5){
		cout << "{" ;
		for(int i = 0 ; i < 5 ; i++)
			if(tag[i] == 1 )
				cout << str[i] << " ";
		cout << "}" << endl;
		return;
	}
	tag[n] = 0;
	build(str , tag , n+1);
	tag[n] = 1;
	build(str , tag , n+1);
}

void _get_sub(int* target , bool * check , int current , int length){
	if(current == length){
		cout << "{ ";
        for(int i = 0 ; i < length ; i++) if(check[i]) cout << target[i] << " ";
		cout <<"}" << endl;
		return ;
	}
	check[current] = true;
	_get_sub(target , check , current + 1 , length);
	check[current] = false;
	_get_sub(target , check , current + 1 , length);
}

int main(int argc , char ** argv){
	/**string  expression = "";
       cout << "Input the expression : " << endl;
       getline(cin , expression);
       _show_sub_set(expression);*/
	int n ;
	cout << "Input the number : " << endl;
	cin >> n;
	int * target = new int[n];
	bool * check = new bool[n];
	for(int i = 0 ; i < n ; i++){
		check[i] = false;
		target[i] = i+1;
	}
	_get_sub(target , check , 0 , n);
	return 0;
}
