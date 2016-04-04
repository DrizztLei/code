#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
int calculator(const string expression){
	int length = expression.length() , count_char = 0 , count_int = 0;
	char * operation = new char [length];
	int * number = new int [length];
	char ch , pre_ch;
	for(int i = 0 ; i < length ; i++){
		number[i] = 0;
    }
	for(int i = 0 ; i < length ; i++){
		ch = expression[i];
		switch(ch){
		case '+':
		case '-':
		case '*':
		case '/':{
			operation[count_char ++] = ch;
			break;
		}
		case '(':{
			int left = 1 , right = 0;
			string temp_expression = "";
			char ch_expression;
			while(1){
				ch_expression = expression[++i];
				if(ch_expression=='(') left ++;
				if(ch_expression==')') right ++;
				if(left == right) break;
				temp_expression += ch_expression;
			}
			number[count_int++] = calculator(temp_expression);
			break;
		}
		case ' ':
		case '\t':{
			break;
		}
		default:{
			if(ch >= '0' && ch <='9'){
				number[count_int] = 10 * number[count_int] + (ch - '0');
				if(i+1 == length || !(expression[i+1] >= '0' && expression[i+1] <= '9')){
					count_int ++;
				}
			}
		}
		}
	}
	int result = 0;
	for(int i = 0 ; i < count_char ; i++ ){
		ch = operation[i];
		if(ch == '*'){
			number[i+1] *= number[i];
			number[i] = 0;
			if(i==0){
				operation[i] = '+';
			}else if(operation[i-1] == '-'){
				operation[i] = '-';
			}else if(operation[i-1] == '+'){
				operation[i] = '+';
			}
		}else if(ch == '/'){
			number[i+1] = number[i] / number[i+1];
			number[i] = 0;
			if(i==0){
				operation[i] = '+';
			}else if(operation[i-1] == '-'){
				operation[i] = '-';
			}else if(operation[i-1] == '+'){
				operation[i] = '+';
			}
		}
	}
	for(int i = 0 ; i < count_char ; i++){
		ch = operation[i];
		if(ch == '+'){
			number[i+1] += number[i];
			number[i] = 0;
		}else if (ch == '-'){
			number[i+1] = number[i] - number[i+1];
			number[i] = 0;
		}
	}

	for (int i = 0; i < count_int ; i++){
		result += number[i];
	}
	return result;
}
void test(string expression){
	int * number = new int[expression.length()];
	number[0] = 0;
	cout << number[2] << endl;
	for(int i = 0 ;i < expression.length() ; i++)
		cout << number[i] << "\t";
	cout << endl;
	int * matrix  = new int[4];
	for(int i = 0 ; i < 4 ; i++)
		cout << matrix[i] << "\t";
	cout << endl;
	cout << "DONE . " << endl;
}
int main(int argc , char ** argv){
	while(true){
        string expression = "";
        cout << "Input the expression :" << endl;
        getline(cin , expression);
        cout << calculator(expression) << endl;
	}
	return 0;
}
