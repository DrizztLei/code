#include <iostream>
#include <cstring>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
bool isOperator(char ch){
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' == ch == '(' || ch == ')');
}

char * infix_to_suffix(char * infix){
    char opStack[10];
    int top=-1 , pos=0;
    char * result=new char[2*strlen(infix)];

    for(int i = 0 ; infix[i] != '\0' ; i++){
        if(infix[i] == ' ') continue;
        switch(infix[i]){
        case ')':
            while(top != -1 && opStack[top] != '('){
                result[pos++] = ' ';
                result[pos++] = opStack[top--];
            }
            if(opStack[top--] != ')') {
                cerr << "')' needed ~ , Attention ." << endl;
                return "Error.";
            }
            break;
	case '(': opStack[top++] = '('; break;
	case '^': opStack[top++] = '^'; break;
	case '*': case '/' :
            while(top != -1 && (opStack[top] == '*' || opStack[top] == '/'|| opStack[top] == '^')){
                result[pos++] = ' ';
                result[pos++] = opStack[top--];
            }
            opStack[++top] = infix[i];
            break;
	case '+' : case '-' :
            while(top != -1 && opStack[top] != '('){
                result[pos++] = ' ';
                result[pos++] = opStack[top--];
            }
            opStack[++top] = infix[i];
            break;
	default:
            result[pos++] = ' ';
            while(infix[i] != '\0' && !isOperator(infix[i]) && infix[i] != ' ' ){
                result[pos++] = infix[i++];
            }
            --i;
        }
    }
}

int calc_suffix(char * suffix){
    int dataStack[10] , top = -1;
    int num1 , num2 , result;

    for(int i = 0 ; suffix[i] != '\0' ; i++){
        if(suffix[i] == ' ') continue;

        if(!isOperator(suffix[i])){
            result = 0;
            while(suffix[i] != '\0' && suffix[i] != ' '){
                result = result * 10 + suffix[i] - '0';
                ++ i;
            }
            dataStack[++top] = result;
            continue;
        }

        num2 = dataStack[top--];
        num1 = dataStack[top--];

        switch(suffix[i]){
        case '^' : result = pow(num1 , num2 ); break;
        case '*' : result = num1 * num2; break;
        case '/' : result = num1 / num2; break;
        case '+' : result = num1 + num2; break;
        case '-' : result = num1 - num2; break;
        }
        dataStack[++top] = result;
    }
    return result;
}

int main (int argc , char ** argv){

    return 0;
}
