#ifndef WORKERMI_H_
#define WORKERMI_H_
#include <string>

class Worker
{
 private:
	std::string fullname;
	long id;
 protected:
	virtual void Data()const;
	virtual void Get();
 public:
 Worker() : fullname("No one") , id(0L){}
 Worker(const std::string & s , long n ) :fullname (s) , id(n){}
	virtual ~Worker() = 0;
	virtual void Set () = 0;
	virtual void Show() const  = 0;
};

class Waiter : public Worker
{
 private:
	int panche;
 protected:
	void Data()const;
	void Get();
 public:
 Waiter():Worker() , panche(0){}
 Waiter(const std::string & s, long n , int p = 0):Worker(s , n) ,panche(p){}
 Waiter(const Worker & wk , int p=0 ):Worker(wk) , panche(p){}
	void Set();
	void Show() const ;
};

class Singer:virtual public Worker
{
 protected:
	enum{other , alto , contralto , soprano , bass , baritone , tenor};
	enum{Vtype = 0};
	void Data() const;
	void Get();
 private:
	static char * pv[Vtype];
	int voice;
 public:
 Singer():Worker() , voice (other){}
 Singer(const std::string & s , long n , int v = other):Worker(s , n) , voice(v){}
 Singer(const Worker & wk , int v = other ) :Worker(wk) , voice(v){}
	void Set();
	void Show()const;
};

class SingerWaiter : public Waiter , public Singer
{
 protected:
	void Data() const;
	void Get();
 public:
	SingerWaiter (){}
 SingerWaiter(const std :: string & s , long n , int p = 0 , int v = other):Worker(s  , n) , Waiter(s , n ,p) , Singer(s , n , v){}
 SingerWaiter(const Worker & wk , int p = 0 , int v = other ):Worker(wk) , Waiter(wk , p) , Singer(wk , v){}
 SingerWaiter(const Waiter & wt , int p = 0 ) : Worker(wt) , Waiter(wt ,p) , Singer(wt){}
	void Set();
	void Show() const;
};
#endif
