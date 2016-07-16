#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::exception;
using std::string;
template<class T>
struct node {
	T data;
	node * next;
};

template<class T>
class stack
{
private:
	node<T> * _link_stack ;
public:
	void init();
	bool isEmpty();
	T top();
	T pop();
	void push(T);
	stack();
	~stack();
};

template<class T>
void stack<T> :: init(){
}

template<class T>
stack<T>:: stack(){
	init();
}

template<class T>
bool stack<T>:: isEmpty(){
	return _link_stack == NULL;
}

template<class T>
T stack<T>:: pop(){
	if(_link_stack == NULL){
		cerr << "Error in _link_stack == NULL . " << endl;
		throw std::exception();
	   	return NULL;
	}
	node<T> * temp = _link_stack;
	T target = temp->data;
	_link_stack = _link_stack -> next;
	delete temp;
	return target;
}

template<class T>
T stack<T>:: top(){
	return _link_stack -> data;
}

template<class T>
void stack<T>::push(T in){
	node<T> * insert = new node<T>;
	insert -> data = in;
	insert -> next = _link_stack ;
	_link_stack = insert;
}

template<class T>
stack<T> :: ~stack(){
	node<T> * temp = _link_stack;
	while(_link_stack){
		_link_stack = _link_stack -> next;
		delete temp;
		temp = _link_stack;
	}
}

bool _is_match(string input){
	stack<char> * left = new stack<char>();
	char ch ;
	int length = input.length();
	for(int i = 0 ; i < length ; i++){
		ch = input[i];
		if(ch == '(' || ch == '[' || ch == '{'){
			left -> push(ch);
		}else if(ch==')' || ch == ']' || ch == '}'){
			if(left -> isEmpty()) return false;
				char temp = left -> pop();
				if(ch == ')'){
					if(temp != '(') return false;
				}else if(ch == ']'){
					if(temp != '[') return false;
				}else {
					if(temp != '{') return false;
				}
		}
	}
	return left->isEmpty();
}

int _binary_output(int input){
	int size ;
	size = 2;
	int div = 1;
	while(div <= input) div *= size;
	div /= size;
	int result;
	while(div != 0){
		result = input / div;
		cout << result ;
		input -= result * div;
		div /= size;
	}
	cout << endl;
}

int _binary_stack(int input){
	stack<int> * temp = new stack<int>();
	while(input > 0){
		temp -> push(input%2);
		input /= 2;
	}
	while(!temp -> isEmpty()){
		cout << temp -> pop();
	}
	cout << endl;
	temp -> ~stack();
}

int main(int argc , char ** argv){
	//	string input = "";
	//	cout << "Input the expression here : " << endl; 
	//	getline(cin , input);
	//	cout << (_is_match(input)==1?"TRUE":"FALSE") << endl;
	int input;
	cin >> input;
	//	_binary_output(input);
	_binary_stack(input);
	return 0;
}

