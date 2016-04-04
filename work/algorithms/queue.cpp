#include <iostream>
#include <exception> 
using std::cout;
using std::endl;
using std::cin;
template <class T>
class queue{
private:
	
public:
	int front , rear;
	T data[100];
	void init();
	T getHead();
	void enQueue(T x);
	T deQueue();
	bool isEmpty();
};
template<class T>
void queue<T>::init(){
	front = rear = 0;
}

template<class T>
inline bool queue<T> :: isEmpty(){return front == rear;}

template<class T>
inline T queue<T> :: getHead(){return data[front];}

template<class T>
void queue<T> :: enQueue(T x){
	if((rear + 1) % 100 == front) throw  exception("The queue is in max. ");
	rear = (rear + 1) % 100;
	data[rear] = x;
}

template<class T>
T queue<T> :: deQueue(){
	front = (front + 1) % 100;
	return data[front];
}

int main(int argc , char ** argv){
	queue<int> * temp = new queue<int>();
	temp -> init();
	delete temp;
	return 0;
}
