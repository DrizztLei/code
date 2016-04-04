#ifndef QUEUE_H_
#define QUEUE_H_

class Customer{
 public :
	long arrive;
	int processtime;
 public:
	Customer();
	void set(long when);
	long when() const{return arrive;}
	int ptime() const{return processtime;}
	~Customer();
}

typedef Customer Item; 

class Queue{
 public:
	//	class scope definitions
	struct Node {Item item ; struct Node * next ;};
	enum {Q_SIZE = 10};
	// private class members:
	Node * front , * rear;
	int items;
	const int qsize = Q_SIZE;
	Queue (const Queue & q);
	Queue & operator= (const Queue & q){return * this;}
 public:
	Queue (int qs = Q_SIZE);
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item & item);
	bool dequeue (Item & item);
};
#endif
