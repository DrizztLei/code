#include <iostream>
#include <cstring>
#include <exception>
#include <cstdlib>
using namespace std;

template<class T>
class Heap
{
private:
	T * hlist;
	int inArray;
	int maxheapsize;
	int heapsize;
	void error(char errmsg[]);
	void FilterDown(int i);
	void FilterUp(int i);
public:
	Heap(int maxsize);
	Heap(T arr[] , int n);
	Heap(Heap<T> & H);
	~Heap();
	Heap<T> & operator= (const Heap<T> & rhs);
	const T& operator[](int i);
	int ListSize() const;
	int ListEmpty() const;
	int ListFull() const;
	void Insert(const T & item);
	void ClearList();
	T Delete();
	void show();
};

template<class T>
void Heap<T> :: show(){
	for(int i = 0 ; i < heapsize ; i++)
		cout << hlist[i] << "\t" ;
	cout << endl;
}

template<class T>
void Heap<T> :: error(char errmsg[]){
	cerr << errmsg << endl;
	exit(0);
}

template<class T>
void Heap<T> :: FilterDown(int i){
	int currentpos , childpos;
	T target;
	currentpos = i;
	target = hlist[i];
	childpos = 2 * i + 1;
	while(childpos < heapsize){
		if((childpos + 1 < heapsize) &&
		   (hlist[childpos+1] <= hlist[childpos]))
			childpos ++;
		if(target <= hlist[childpos]){
			break;
		}else{
			hlist[currentpos] = hlist[childpos];
			currentpos = childpos;
			childpos = 2 * currentpos + 1;
		}
	}
	hlist[currentpos] = target;
}

template<class T>
void Heap<T> :: FilterUp(int i){
	int currentpos , parentpos;
	T target;
	currentpos = i;
	parentpos = (i - 1) / 2;
	target = hlist[i];
	while(currentpos != 0){
		if(hlist[parentpos] <= target)
			break;
		else {
			hlist[currentpos] = hlist[parentpos];
			currentpos = parentpos;
			parentpos = (currentpos - 1) / 2;

		}
	}
	hlist[currentpos] = target;
}

template<class T>
Heap<T> :: Heap(int size){
	if(size <= 0)
		error("Bad list size . ");
	hlist = new T[size];
	if(hlist == 0){
		error("Memory allocation failure . ");
	}
	maxheapsize = size;
	heapsize = 0;
	inArray = 0;
}

template<class T>
Heap<T> :: Heap(T arr[] , int n){
	int currentpos;
	if(n <= 0)
		error("Bad list size.");
	maxheapsize = n;
	heapsize = n;
	hlist = new T[n];
	memcpy(hlist , arr , sizeof(T) * n);
	currentpos = (heapsize - 2)/2;
	while(currentpos >= 0){
		FilterDown(currentpos);
		currentpos --;
	}
	inArray = 1;
}

template<class T>
Heap<T> :: ~Heap(){
	if(!inArray) delete[] hlist;
}

template<class T>
Heap<T> & Heap<T> :: operator=(const Heap<T> & rhs){
	int n = rhs.heapsize;
	heapsize = n;
	if(maxheapsize != rhs.maxheapsize || inArray){
		maxheapsize = rhs.maxheapsize;
		if(!inArray) delete hlist;
		hlist = new T[maxheapsize];
		if(hlist == NULL)
			error("Memory allocation failure .");
	}
	while(n--)
		hlist[n] = rhs.hlist[n];
	inArray = 0;
	return * this;
}

template<class T>
int Heap<T> :: ListSize() const
{
	return heapsize;
}

template<class T>
int Heap<T> :: ListEmpty()const
{
	return heapsize == 0;
}

template<class T>
int Heap<T> :: ListFull()const
{
	return heapsize == maxheapsize;
}

template<class T>
const T& Heap<T> :: operator[](int i){
	if(i < 0 || i >= heapsize)
		error("Heap index out of range : ");
	return hlist[i];
}

template<class T>
void Heap<T> :: Insert(const T& item){
	if(heapsize == maxheapsize)
		error("Heap full");
	hlist[heapsize] = item;
	FilterUp(heapsize);
	heapsize ++ ;
}

template<class T>
T Heap<T> :: Delete(){
	T tempitem;
	if(heapsize == 0)
		error("Heap empty");
	tempitem = hlist[0];
	hlist[0] = hlist[heapsize-1];
	heapsize--;
	FilterDown(0);
	return tempitem;
}

template<class T>
void Heap<T> :: ClearList()
{
	heapsize = 0;
}


int main(int argc, char ** argv){
	int x[] = {23 , 21 , 4 , 5 , 6 , 7};
	Heap<int> h (x , 6);
	h.show();

	return 0;
}
