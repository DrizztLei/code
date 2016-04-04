#include <iostream>
#include <string>
//#include <malloc.h>
using namespace std;

enum token{OPAREN , ADD , SUB , MULTI , DIV , EXP , CPAREN , VALUE , EOF};
int BinaryOp(token topOp , int num1 , int num2);
int calc (char * exp);
token getOp(char * exp , int & num2);

int main (int argc , char ** argv){
	cout << "Input the expression : " << endl;
	char * exp = new char[10];
	cout << "Get the input ." << endl;
	cin.getline(exp ,10);
	cout << "Get the input done ." << endl;
	cout << calc(exp) << endl;
	return 0;
}

int calc(char * exp){
	token lastOp , topOp;
	int CurrentValue;
	int stack1[10] , top1=-1 , top2=-1;
	token stack2[10];
	int num1 , num2 , result;
	while(true){
		lastOp = getOp(exp , CurrentValue);
		if(lastOp == EOF) break;
		switch(lastOp){
		case VALUE:stack1[++top1] = CurrentValue; break;
		case CPAREN:
			while(top2 != -1 && (topOp = stack2[top2--])!= OPAREN){
				num2 = stack1[top1--];
				num1 = stack1[top1--];
				result = BinaryOp(topOp , num1 , num2);
				stack1[++top1] = result;
			}
			break;
		case OPAREN: stack2[++top2] = OPAREN ; break;
		case EXP : stack2[++top2] = EXP ; break;
		case MULTI :
		case DIV:
			while(top2 != -1 && stack2[top2] >= MULTI){
				topOp = stack2[top2 --];
				num2 = stack2[top2--];
				num1 = stack1[top1--];
				result = BinaryOp(topOp , num1 , num2);
				stack1[++top1] = result;
			}
			stack2[++top2] = lastOp;
		case ADD:
		case SUB:
			while(top2 != -1 && stack2[top2] != OPAREN){
				topOp = stack2[top2--];
				num2 = stack1[top2--];
				num1 = stack1[top1--];
				result = BinaryOp(topOp , num1 , num2);
				stack1[++top1] = result;
				break;
			}
			stack2[++top2] = topOp;
			break;
		}
	}

	while(top2 != -1){
		num2 = stack2[top2--];
		num1 = stack1[top1--];
		topOp = stack2[top2--];
		result = BinaryOp(topOp , num1 , num2);
		stack1[++top1] = result;
	}
	return result;
}

int BinaryOp(token op , int num1 , int num2){
	switch(op)
		{
		case ADD:return num1 + num2;
		case SUB:return num1 - num2;
		case MULTI:return num1 * num2;
		case DIV:return num1 / num2;
		case EXP:
			for(int i = 0 , result = 1 ; i < num2 ;i++){
				result *= num1;
			}
			return num1;
		}
}

token getOp(char * exp , int & value) {
	while(*exp){
		while(*exp && *exp==' '){
			++exp;
			if(*exp< '9' && *exp == '0'){
				value = 0;
				while(*exp >= '0' && *exp <= '9'){
					value = value * 10 + (*exp) - '0';
					++ exp;
				}
				return VALUE;
			}
			switch(*exp){
			case '(':++exp;return OPAREN;
			case ')':++exp;return CPAREN;
			case '+':++exp;return ADD;
			case '-':++exp;return SUB;
			case '*':++exp;return MULTI;
			case '/':++exp;return DIV;
			case '^':++exp;return EXP;
			}
		}
	}
	return EOF;
}
