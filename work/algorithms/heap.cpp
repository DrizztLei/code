#include <iostream>
#include <exception>
#include <vector>

using std::vector;
using std::cin;
using std::endl;
using std::exception;
using std::cout;

template<class T>
struct Node{
	
};

template<class T>
class heap{
private:
public:
	heap();
	~heap();
	T bin_search();
	void insert();
	void remove();
	void avl_init();
	
};

template<class T>
heap<T> :: heap(){
	
}

template<class T>
heap<T> :: ~heap(){
	
}

template<class T>
T heap<T> :: bin_search(){
	
	return NULL;
}

template<class T>
void heap<T> :: insert(){
	
}

template<class T>
void heap<T> :: remove(){
	
}

template<class T>
void heap<T> :: avl_init(){
	
}

int main(int argc , char ** argv){
	vector<int> *temp = new vector<int>();
	temp -> push_back(222);
	//cout << temp[0] << endl;
	return 0;
}
