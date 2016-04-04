#include <iostream>
#include "mytime.h"
Time :: Time (int h , int m){
	hours = h;
	minutes = m;
}


Time :: operator+(const Time & t)const{
	Time sum;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes /60;
	sum.minutes %= 60;
	
	return sum;
}
