#include <iostream>
#include <exception>
#include <cstring>

using std::cout;
using std::cin;
using std::cin;
using std::endl;
using std::string;
void quickSort(int * array , int begin , int end);

template<class T>
struct node {
	T info;
	node * next;
	node(T data = 0 ,node *  Next = NULL){next = Next ; info = data;}
};

template<class T>
class linear
{
private:
	node<T> * head;
public :
	void insert(int position , T data);
	void remove(int position);
	int search(T data);
	void traversal();
	//void show();
	void emerge(linear *  other);
	void add(T data);
	node<T> *& get_head();
	linear();
	~linear();
};

template<class T>
int linear<T> :: search(T data){
	node<T> * temp = head;
	int count = 1;
	while(temp != NULL){
		if(data == temp->info){
			return count;
		}else {
			temp = temp -> next;
			count ++ ;
		}
	}
	return 0;
}

template<class T>
node<T> *& linear<T> :: get_head(){
	return head;
}

template<class T>
linear<T> :: ~linear(){
	node<T> * temp ;
	while(head != NULL){
		temp = head;
		head = head -> next;
		delete temp;
	}
}

template<class T>
linear<T> :: linear(){
}

template<class T>
void linear<T> :: add(T data){
	if(head == NULL) {
		head = new node<T>(data);
		return ;
	}
	node<T> * temp = head;
	while(temp -> next != NULL){
		temp = temp -> next;
	}
	temp -> next = new node<T>(data);
}

template<class T>
void linear<T> :: insert(int position , T data){
	int count = 0;
	node<T> * temp = head;
	while(count++ < position){
		if(temp == NULL) {
			cout << "Linear index out of bounds Exception . " << endl;
			throw exception(data);
			return ;
		}
		temp = temp -> next;
	}
	temp -> next = new node<T>(data , temp -> next);
}

template<class T>
void linear<T> :: remove(int position){
	int count = 0;
	node<T> * temp = head;
	while(++count < position){
		if(temp == NULL){
			cout << "Linear index out of bounds Exception . " << endl;
			throw exception(NULL);
			return ;
		}
		temp = temp -> next;
	}
	if(temp == head){
		if(temp == NULL){
			return;
		}
		temp = head -> next;
		head = head -> next;
		delete temp;
	}
	if(temp->next == NULL){
		cout << "What you wanna remove is NULL" << endl;
		return ;
	}else{
		node<T> * target = temp -> next;
		temp -> next = target -> next;
		delete target;
	}
}

template<class T>
void linear<T> :: traversal(){
	node<T> * temp = head;
	int count = 0 ;
	while(temp != NULL){
		cout << "Traversal " << count ++ <<" : " << temp->info << endl;
		temp = temp->next;
	}
}

void quickSort(int * array , int begin , int end){
	if(begin >= end) return;
	int first = begin , last = end , key = array[begin];
	while(first < last){
		while(first < last && array[last] >= key) last--;
		array[first] = array[last];
		while(first < last && array[first] <= key) first++;
		array[last] = array[first];
	}
	array[first] = key;
	quickSort(array , begin , first - 1);
	quickSort(array , first + 1 , end);
}

template<class T>
linear<T> * show(){
	string accept;
	cout << "Input the number you wanna show : " << endl;
	accept = "";
	getline(cin , accept);
	int * expression = new int[accept.length()];
	for(int i = 0 ;i < accept.length() ;i++)	expression[i] = 0;
	int count = 0 , length = accept.length();
	char ch;
	for(int i  = 0 ; i < length ; i++){
		ch = accept[i];
		if(ch >= '0' && ch <= '9'){
			expression[count] = expression[count] * 10 + ch-'0';
			if(i+1 == length || accept[i+1] < '0' || accept[i+1] > '9'){
				count++;
			}
		}
	}
	int * temp = new int[count];
	for(int i = 0; i < count ; i++){
		temp[i] = expression[i];
	}
	delete expression;
	quickSort(temp , 0 , count - 1);
	linear<T> * display = new linear<T>();
	node<T> * product = NULL;
	for(int i = count - 1 ; i >= 0 ; i--){
		product = new node<T>(temp[i] , product);
	}
	display -> get_head() = product;
	return display;
}

template<class T>
void linear<T> :: emerge(linear<T> * other){
	node<T> * temp = head;
	node<T> * other_temp = other -> get_head();
	if(temp == NULL) {
		this -> head = other -> head;
		return ;
	}else if(other_temp == NULL) {
		other -> head = this -> head;
		return;
	}
	T temp_begin = temp -> info , other_value = other_temp -> info;
	if(temp_begin <= other_value){
		while(other_temp != NULL){
			T temp_data = other_temp -> info;
			if(temp->next == NULL){
				if(temp->info <= temp_data) {
					temp -> next = other_temp;
					other -> head = this -> head;
					return;
				}
				cout << "Error . " << endl;
				return ;
			}
			if(temp->info <= temp_data && temp->next->info >= temp_data){
				node<T> * medium = new node<T>(temp_data , temp->next);
				temp->next = medium;
				other_temp = other_temp -> next;
			}
			temp = temp -> next;
		}
		other -> head = this -> head;
	}else{
		while(temp!= NULL){
			T temp_data = temp -> info;
			if(other_temp->next == NULL){
				if(other_temp->info <= temp_data) {
					other_temp -> next = temp;
					this -> head = other -> head;
					return;
				}
				cout << "Error . " << endl;
				return ;
			}
			if(other_temp -> info <= temp_data && other_temp->next->info >= temp_data){
				node<T> * medium = new node<T>(temp_data , other_temp -> next);
				other_temp->next = medium;
				temp = temp -> next;
			}
			other_temp = other_temp -> next;
		}
		head = other -> head;

	}
}



int main(int argc , char ** argv){
	linear<int> * temp = show<int>();
	linear<int> * temp1 = show<int>();
	temp -> emerge(temp1);
	cout << "------------------->" << endl;
	temp -> traversal();
	cout << "-------------------<" << endl;
	cout << "------------------->" << endl;
	temp1 -> traversal();
	cout << "-------------------<" << endl;
	/**linear<int> * temp = new linear<int>();
       temp -> traversal();
       linear<int> * o = new linear<int>();
       temp -> traversal();
       temp -> emerge(o);
       temp -> add(223);
       temp -> add(1);
       temp -> add(2);
       temp -> traversal();
       o -> add(1);
       o -> add(2);
       o -> add(3);
       o -> traversal();
       temp -> emerge(o);
       temp -> traversal();
       delete temp;
       delete o;*/
	return 0;
}
