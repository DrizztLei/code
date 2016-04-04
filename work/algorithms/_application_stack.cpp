#include <iostream>
#include <exception>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::exception;
using std::string;

template<class T>
struct node{
    T info;
    node * next;
    node(T data  , node * Node = NULL){info = data ; next = Node;}
};

template<class T>
class Stack
{
private:
    node<T> * head;
public:
    Stack(T data);
    Stack();
    ~Stack();
    void push(T insert);
    T top();
    T pop();
    void clear();
    bool isEmpty();
};

template<class T>
inline Stack<T> :: Stack(T data){
    head = new node<T>(data);
}

template<class T>
Stack<T> :: Stack(){}

template<class T>
Stack<T> :: ~Stack(){
    node<T> * temp;
    while(head != NULL){
        temp = head;
        head = head -> next;
        delete temp;
    }
}

template<class T>
void Stack<T> :: push(T insert){
    if(head == NULL)
    {
        head = new node<T>(insert);
        return ;
    }
    head = new node<T>(insert , head);
}

template<class T>
T Stack<T> :: top(){
    if(head == NULL) {cout << "Error . Stack is empty ." << endl; throw exception(); return NULL;}
    return head -> info;
}

template<class T>
T Stack<T> :: pop(){
    if(head == NULL){
        cout << "Error . Stack is empty . " << endl;
        throw exception();
        return NULL;
    }
    node<T> * temp = head;
    T data = head -> info;
    head = head -> next;
    delete temp;
    return data;
}

template<class T>
void Stack<T> :: clear(){
    node<T> * temp = head;
    while(head != NULL){
        temp = head;
        head = head -> next;
        delete temp;
    }
}

template<class T>
bool Stack<T> :: isEmpty(){
    return head == NULL;
}

void finaldoit(){
}

int calculator(){
    Stack<char> * operation = new Stack<char>();
    Stack<int> * number = new Stack<int>();
    cout << "Input the expression : " << endl;
    string expression = "";
    getline(cin , expression);
    expression = "(" + expression + ")";
    int length = expression.length() , store = 0 ,figure_1 , figure_2;
    char ch ;
    for(int i = 0 ; i < length ; i++){
        ch = expression[i];
        //cout << "ch : " << ch << endl;
        switch(ch){
        case '+' :{
            while(!(operation -> isEmpty()) && (operation -> top() == '+' || operation -> top() == '-' || operation -> top() == '*' || operation -> top() == '/')){
                ch = operation -> pop();
                figure_1 = number -> pop();
                figure_2 = number -> pop();
                if(ch == '+') {
                    //cout << "+ here " << endl;
                    //cout << "Figure_1 get : " << figure_1 << endl;
                    //cout << "Figure_2 get : " << figure_2 << endl;
                    number -> push(figure_2 + figure_1);
                    //cout << "We get the number value : " << number -> top() << endl;
                }else if (ch == '-'){
                    //cout << "- here " << endl;
                    //cout << "Figre_1 get : " << figure_1 << endl;
                    //cout << "Figure_2 get: " << figure_2 << endl;
                    number -> push(figure_2 - figure_1);
                    //cout << "We get the number value : " << number -> top() << endl;
                }else if(ch == '*') {
                    //cout << "* here " << endl;
                    //cout << "Figure_1 : " << figure_1 << "\nFigure_2 : " << figure_2 << endl;
                    number -> push(figure_2 * figure_1);
                    //cout << "We get the number value : " << number -> top() << endl;
                }else {
                    //cout << "/ here " << endl;
                    //cout << "Figure_1 : " << figure_1 << "\nFigure_2 : " << figure_2 << endl;
                    number -> push(figure_2 / figure_1);
                    //cout << "We get the number value : " << number -> top() << endl;
                }
            }
            operation -> push('+');
            //cout << "Push the + to operation . " << endl;
            break;
        }
        case '-' :{
            while(!(operation -> isEmpty()) && (operation -> top() == '+' || operation -> top() == '-' || operation -> top() == '*' || operation -> top() == '/')){
                ch = operation -> pop();
                figure_1 = number -> pop();
                figure_2 = number -> pop();
                if(ch == '+') {
                    //cout << "Figure_1 get : " << figure_1 << endl;
                    //cout << "Figure_2 get : " << figure_2 << endl;
                    number -> push(figure_1 + figure_2);
                    //cout << "Push the + to number ." << endl;
                }else if(ch == '-') {
                    //cout << "Figure_1 get: " << figure_1 << endl;
                    //cout << "Figure_2 get: " << figure_2 << endl;
                    number -> push(figure_2 - figure_1);
                    //cout << "Push the - to number ." << endl;
                }else if(ch == '*') {
                    //cout << "* here " << endl;
                    //cout << "Figure_1 : " << figure_1 << "\nFigure_2 : " << figure_2 << endl;
                    number -> push(figure_2 * figure_1);
                    //cout << "We get the number value : " << number -> top() << endl;
                }else {
                    //cout << "/ here " << endl;
                    //cout << "Figure_1 : " << figure_1 << "\nFigure_2 : " << figure_2 << endl;
                    number -> push(figure_2 / figure_1);
                    //cout << "We get the number value : " << number -> top() << endl;
                }
            }
            operation -> push('-');
            //cout << "Push the - to operation : " << endl;
            break;
        }
        case '*' :{
            while(!(operation -> isEmpty()) && (operation -> top() == '*' || operation -> top() == '/')){
                figure_1 = number -> pop();
                figure_2 = number -> pop();
                ch = operation -> pop();
                if(ch == '*') {
                    //cout << "Figure_1 get : " << figure_1 << endl;
                    //cout << "Figure_2 get : " << figure_2 << endl;
                    number -> push(figure_2 * figure_1);
                    //cout << "Push the * to number ." << endl;
                }else if(ch == '/'){
                    //cout << "Figure_1 get: " << figure_1 << endl;
                    //cout << "Figure_2 get: " << figure_2 << endl;
                    number -> push(figure_2 / figure_1);
                    //cout << "Push the * to number ." << endl;
                }
                //cout << "We check the number : " << number -> top() << endl;
            }
            //cout << "We push the * " << endl;
            operation -> push('*');
            break;
        }
        case '/' :{
            while(!(operation -> isEmpty()) && (operation -> top() == '*' || operation -> top() == '/')){
                figure_1 = number -> pop();
                figure_2 = number -> pop();
                ch = operation -> pop();
                if(ch == '*') {
                    //cout << "Figure_1 get : " << figure_1 << endl;
                    //cout << "Figure_2 get : " << figure_2 << endl;
                    number -> push(figure_2 * figure_1);
                    //cout << "Push the / to number ." << endl;
                }else if(ch == '/'){
                    //cout << "Figure_1 get: " << figure_1 << endl;
                    //cout << "Figure_2 get: " << figure_2 << endl;
                    number -> push(figure_2 / figure_1);
                    //cout << "Push the / to number ." << endl;
                }
                //cout << "We check the number : " << number -> top() << endl;
            }
            //cout << "We push the / " << endl;
            operation -> push('/');
            break;
        }
        case ' ' :
        case '\t':{
            break;
        }
        case '(' :{
            //cout << "We push the (" << endl;
            operation -> push('(');
            break;
        }
        case ')' :{
            //cout << "Run the when we match the ) " << endl;
            while(!(operation -> isEmpty()) && operation -> top() != '('){
                figure_1 = number -> pop();
                figure_2 = number -> pop();
                ch = operation -> pop();
                if(ch == '+'){
                    //cout << "In Matching of + " << endl;
                    number -> push(figure_2 + figure_1);
                }else if(ch == '-'){
                    //cout << "In Matching of - " << endl;
                    number -> push(figure_2 - figure_1);
                }else if(ch == '*'){
                    //cout << "In Matching of * " << endl;
                    number -> push(figure_2 * figure_1);
                }else if(ch == '/'){
                    //cout << "In Matching of / " << endl;
                    number -> push(figure_2 / figure_1);
                }
            }
            if(operation -> isEmpty()) {throw exception();return;}
            //cout << "Check if the operation is ( : " << operation -> pop() << endl;
            operation -> pop();
            break;
        }
        default:{
            if(ch >= '0' && ch <='9'){
                //cout<<"char of  : " << count_int << " . The value is : "<<ch<<endl;
                //cout << "Number[count_int] : " << number[count_int] << endl;
                store = 10 * store + (ch - '0');
                //cout << "The store is now : " << store << endl;
                //cout<<"The result is : " << number[count_int] << endl;
                //cout << number[count_int] << endl << "Count_int\t" << count_int<<endl;
                //if(i+1 == length || expression[i+1] <'0'|| expression[i+1] > '9') {
                if(i+1 == length || !(expression[i+1] >= '0' && expression[i+1] <= '9')){
                    number -> push(store);
                    //cout << "Push the number to number : " << store << endl;
                    //cout << "Top() the value : " << number -> top() << endl;
                    store = 0;
                    //count_int ++;
                }
            }
            //cout << "The i is : " << i << endl;
        }
        }
    }
    //cout << "ALL thing done suddenly . " << endl;
    /**if(operation != NULL)
       delete operation;
       if(number != NULL)
       delete number;
       if(!number -> isEmpty())*/
    int result = number -> top() ;
    delete operation;
    delete number;
    cout << "The result is : " << result << endl;
    //cout << "Done  " << endl;
    return result;
}

int main(int argc , char ** argv){
    calculator();
    return 0;
}
