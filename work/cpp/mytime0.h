#ifndef MYTIME_H_
#define MYTIME_H_

class Time
{
 private:
	int hours , minutes;
 public:
	Time();
	TIme(int h , int m = 0;);
	void AddMin(int m);
	void AddHr(int m);
	void Reset(int h = 0 , int m = 0);
	Time Sum (const Time & t) const;
	void Show() const;
	Time operation+ (const Time & t) const;
};
#endif
