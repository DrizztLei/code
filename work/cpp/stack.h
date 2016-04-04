#ifndef STACK_H_
#define STACK_H_

typedef unsigned long Item;


class stack{

 private :
	enum {MAX = 100};
	Item item[MAX];
	int top;
 public :
	Stack();
	bool isempty() const;
	bool isfull() const;
	bool push (const Item & item);
	bool pop (Item & item);
	
};
#endif
