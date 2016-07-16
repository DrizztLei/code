#include <iostream>
#include "stack.h"

Stack :: Stack(){
	top = 0;
}

bool Stack :: isempty() const{
	return !top;
}

bool Stack :: isfull() cout{
	return top == MAX ;
}

bool Stack :: push (const Item & item){
	if(top < MAX ){
		items[top++] = item;
		return true;
	}
	else {
		return false;
	}
}

bool Stack :: pop (Item & item){
	if (top > 0){
		item = item[--top];
		return true;
	}
	return false;
}
