#include <iostream>
#include <exception>
#include <ostream>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::exception;
using std::ostream;
using std::swap;
/**
   We discuss the max heap here .
   We insert an element in heap and change the heap struct .
   We hardly use the heap the sort but in call the thread .
   void MaxHeapify(int i) ;
   void BuildMaxHeap();
   T Maximum();
   T ExtracMaximum();
   void IncreaseKey(int i , T key);
   void HeapInsert(T key);
   void HeapSort();
*/

template <typename T>
class MaxHeap{
public :
	MaxHeap(int max_size , int cur_size , T data[]) : cur_size_(cur_size) , max_size_(max_size){
		if(max_size_ < cur_size_) throw exception();
		heap_ = new T[max_size_ + 1];
		copy(data , data + cur_size_ , heap_ + 1);
	}
	inline ~MaxHeap(){delete [] heap_;}
	void MaxHeapify(int i){
		int l = left(i);
		int r = right(i);
		int largest = i;
		if(l <= cur_size_ && heap_[i] > heap_[largest])
			largest = l;
		if(r <= cur_size_ && heap_[r] > heap_[largest])
			largest = r;
		if(largest != i){
			swap(heap_[largest] , heap_[i]);
			MaxHeapify(largest);
		}
	}

	void BuildMaxHeap(){
		for(int i = cur_size_ / 2 ; i >= 1 ; i--) {
			MaxHeapify(i);
		}
	}

	inline T Maximum(){ return heap_[1];}

	T ExtracMaximum(){
		if(cur_size_ <= 1) throw exception("No element in max heap ! ");
		T max = heap_[1];
		heap_[1] = heap_[cur_size_];
		cur_size_ --;
		MaxHeap(1);
		return max;
	}

	void IncreaseKey(int i , T key){
		if(key < heap_[i]) throw exception("The new key is smaller than current key ! ");
		heap_[i] = key;
		while(i > 1 && heap_[parent(i) < heap_[i]]){
			swap(heap_[parent(i)] , heap_[i]);
			i = parent(i);
		}
	}

	void HeapInsert(T key){
		if(max_size_ <= cur_size_)
			throw exception("The heap is out of size , can't insert ! ");
		cur_size_++;
		heap_[cur_size_] = T(-0xFFFF);
		IncreaseKey(cur_size_ , key);
	}

	void HeapSort()
	{
		int temp_size = cur_size_;
		for(int i = temp_size ; i > 1 ; i--){
			swap(heap_[1] , heap_[i]);
			cur_size_--;
			MaxHeapify(1);
		}
		cur_size_ = temp_size;
	}

	ostream & print(ostream & out){
		using namespace std;
		copy(heap_ + 1 , heap_ + cur_size_ + 1 , ostream_iterator<T>(out , " "));
		return out;
	}
private:
	int parent(int i){return i / 2;}
	int left(int i ) { return i * 2;}
	int right(int i){return i * 2 + 1;}
private:
	int cur_size_;
	int max_size_;
	T * heap_;
};

template<typename T>
ostream & operator << (ostream & out , MaxHeap<T> & mh){
	return mh.print(out);
}

int main()
{
	using namespace std;
    int data[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int count = sizeof(data) / sizeof(int);
    MaxHeap<int> mh(2 * count, count, data);
    cout << "Before build: " << mh << endl;
    mh.BuildMaxHeap();
    cout << "After build: " << mh << endl;
    mh.HeapSort();
    cout << "After sort: " << mh << endl;
    return getchar();
}
