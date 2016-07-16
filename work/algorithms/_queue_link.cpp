#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::exception;
template<class T>
class _queue_link{
private:
	struct node{
		T data;
		node * next;
	};
public:
	void init();
	bool isEmpty();
	void enQueue(T x);
	T deQueue();
	T getHead();
	node * front , * rear;
};

template<class T>
void _queue_link<T> :: init(){
	front = rear = NULL;
}

template<class T>
bool _queue_link<T> :: isEmpty(){
	return front == rear;
}

template<class T>
void _queue_link<T> :: enQueue(T x){
	if(front == NULL){
		front = rear = new node;
	}else{
		rear -> next = new node;
		rear = rear -> next;
	}
	rear -> data = x;
	rear -> next = NULL;
}



template<class T>
T _queue_link<T> :: deQueue(){
	if(front == NULL) throw exception();
	node * temp = front;
	T result = front -> data;
	front = front -> next;
	rear = front==NULL?NULL:rear;
	delete temp;
	return result;
}

int main(int argc , char ** argv){
	_queue_link<int> *temp = new _queue_link<int>();
	temp -> init();
	cout << temp->isEmpty() << endl;
	temp -> enQueue(3213);
	temp -> enQueue(123);
	cout << temp->deQueue() << endl;
	cout << temp->deQueue() << endl;
	delete temp;
	return 0;
}
