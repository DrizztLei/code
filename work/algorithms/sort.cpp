#include <cstring>
#include <iostream>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class sort{
private:
	struct node{
		int info;
		node * next;
		node (){next = NULL;}
	};
	void emergeSort(int * array , int beging , int end);
	void merge(int * array , int begin , int mid , int end);
	static void kernelQuick(int * array , int begin , int end);
	//int _get_mid(int * array , int begin , int end);
public:
	//static void kernelQuick(int * array , int begin , int end);
	void bubbleSort(int * array , int length);
	void selectSort(int * array , int length);
	void insertSort(int * array , int length);
	void shellSort (int * array , int length);
	static void quickSort (int * array , int length);
	void mergetSort(int * array , int length);
	void bucketSort(int * array , int length);
	void show(int * a, int length);
	//int _get_array(int * array);
	//int _get_length(int * array);
	int deal(int number , int max);
	void _show_for_user();
};

void sort::_show_for_user(){
	int select;
	string accept;
	while(true){
		cout << "Input the expression you wanna sort : " << endl;
		accept = "";
		//getline(cin , accept);
		//cin.clear();
		//cout << "Accept : " << accept << endl << "Accept length : " << accept.length() << endl;
		/**if(accept.length() == 0) {
		   cin.get();
		   }
           if(accept.length() == 0){
           getline(cin , accept);
           }*/
		do{
			getline(cin , accept);
		}
		while(accept.length() == 0);
        int * expression = new int[accept.length()];
		for(int i = 0 ;i < accept.length() ;i++){
			expression[i] = 0;
		}
		int count = 0 , length = accept.length();
		char ch = accept[0];
		for(int i  = 0 ; i < length ; i++){
			ch = accept[i];
			if(ch >= '0' && ch <= '9'){
				expression[count] = expression[count] * 10 + ch-'0';
				if(i+1 == length || accept[i+1] < '0' || accept[i+1] > '9'){
					count++;
				}
			}
		}
		int * temp = new int[count];
		for(int i = 0; i < count ; i++){
			temp[i] = expression[i] ;
		}
		delete expression;
		cout << "Input the way you wanna sort (1 for bubbleSort , 2 for selectSort , 3 for insertSort , 4 for quickSort , 5 for mergeSort , 6 for bucketSort , other for exit .):" << endl;
		cin >> select;
		//cout << "Select : " << select << endl;
		switch(select){
		case 1: bubbleSort(temp ,count); break;
		case 2: selectSort(temp , count); break;
		case 3: insertSort(temp , count); break;
		case 4: quickSort(temp , count); break;
		case 5: mergetSort(temp , count); break;
		case 6: bucketSort(temp , count); break;
		default : return;
		}
		show(temp , count);
		delete temp;
	}
}

int sort::deal(int number , int max){
	for(int i = 0 ; i < max ; i++){
		if(number == 0) return 0;
		number /= 10;
	}
	//cout << "Number % 10 after " << max << " /10 is : " << number % 10 << endl;
	return number%10;
}

/**int sort::_get_length(int * array){
   for(int i = 0;;i++){
   if(array[i] == '\0') return i;
   }
   }

   int sort::_get_array(int * temp){
   cout << "Input the expression you wanna sort : " << endl;
   string accept = "";
   getline(cin , accept);
   int * expression = new int[accept.length()];
   for(int i = 0 ;i < accept.length() ;i++){
   expression[i] = 0;
   }
   int count = 0 , length = accept.length();
   char ch = accept[0];
   for(int i  = 0 ; i < length ; i++){
   ch = accept[i];
   if(ch >= '0' && ch <= '9'){
   expression[count] = expression[count] * 10 + ch-'0';
   if(i+1 == length || accept[i+1] < '0' || accept[i+1] > '9'){
   count++;
   }
   }
   }
   temp = new int[count];

   for(int i = 0; i < count ; i++){
   temp[i] = expression[i] ;
   cout << temp[i] << "\t";
   }
   cout << endl;
   return count;
   }*/

void sort::bubbleSort(int * array , int length){
	bool flag;
	int temp;
	for(int i = 0 ; i < length ; i++){
		flag = false;
		for(int j = 0  ; j < length - i - 1  ; j++){
			if(array[j] > array[j+1]) {
				flag = true;
				/**temp = array[j];
				   array[j] = array[j+1];
				   array[j+1] = temp;*/
				array[j] ^= array[j+1];
				array[j+1] ^= array[j];
				array[j] ^= array[j+1];
				//cout << "Change it . " << endl;
			}
		}
		if(!flag) return;
	}
}

void sort::selectSort(int * array, int length){
	for(int i = 0 ; i < length ; i++){
		int min = i;
		for(int j = i ; j < length ; j++){
			if(array[min] > array[j]) min = j;
		}
		if(min != i) {
			array[min] ^= array[i];
			array[i] ^= array[min];
			array[min] ^= array[i];
		}
	}
}

void sort::insertSort(int * array ,int  length){
	for(int i = 0 ; i < length ; i++) {
		int temp = array[i];
		for(int j = i ; j > 0 ; j--){
			if(i == j && array[j] >= array[j-1]) break;
			if(array[0] >= temp) {
				for(int start = i; start > 0 ;start--){
					array[start] = array[start-1];
				}
				array[0] = temp;
				break;
			}
			if(array[j] >= temp && array[j-1] < temp) {
				for(int start = i ; start > j ; start--){
					array[start] = array[start - 1] ;
				}
				array[j] = temp;
			}
		}
	}
}

void sort::shellSort(int * array , int length){
	int step , i , j;
	int temp;
	for(step = length / 2 ; step > 0 ; step -- ){
		for(i = step ; i < length ; ++i){
			temp = array[i];
			for(j = i - step ; j >= 0 && array[j] > temp ; j -= step)
				array[j+step] = array[j];
			array[j+step] = temp;
		}
	}
}

void sort::quickSort(int * array , int length){
	kernelQuick(array , 0 , length - 1);
}

/**int sort::_get_mid(int *array , int begin , int end){
   int i = begin , j = end - 1 , key = begin;
   cout << "Done " << endl;
   while(j > i){
   while(j > i) {
   if(array[j] < array[key]) {
   array[j] ^= array[key];
   array[key] ^= array[j];
   array[j] ^= array[key];
   key = j;
   }
   j--;
   }
   while(i < j){
   if(array[i] > array[key]){
   array[i] ^= array[key];
   array[key] ^= array[i];
   array[i] ^= array[key];
   key = i;
   }
   i++;
   }
   }

   int i = begin , j = end , key = array[begin];
   while(begin < end){
   while(begin < end && array[end] >= key) --end;
   while(begin < end && array[begin] <= key) ++begin;
   }
   cout << "Done . " << endl;
   return begin;

   int i = begin , j = end - 1, position = begin;
   int key = array[position];
   cout << "Begin : " << begin << "\nend : " << end << endl;
   cout << "Key word : ( means array[position] ) " << key << endl;
   for(int k = begin ; k < end ; k++)
   cout << array[k] << "\t";
   cout << endl;
   while(i != j){
   while(i < j && array[j] >= key)  {
   cout << "array[j] : " << array[j] << endl;
   j--;
   //if(i == j) return i;
   }
   cout << "j : " << j << endl;
   cout << "ARRAY[J] : " << array[j] << endl;
   array[position] = array[j];
   cout << "ARRAY[J] = key OF array[j] : " << key;
   array[j] = key;
   position = j;
   cout << "array[j] : " << array[j] << endl;
   while(i < j && array[i] <= key){
   i++;
   //if(i == j ) return j;
   }
   cout << "after while i : " << i << endl;
   cout << "array[i] : here is : " << array[i] << endl;
   cout << "position of array is : " << array[position] << endl;
   array[position] = array[i];
   cout << "Key is : " << key  << endl;
   array[i] = key;
   cout << "position is : " << position << endl;
   position = i;
   cout << "array[i] : " << array[i] << endl;
   cout << "I : " << i << "\nJ : "  << j << endl;
   cout << "Result : " << endl;
   for(int l = begin ; l < end ; l++)
   cout << array[l] << "\t" ;
   cout << endl;
   }
   return i;
   }*/
void sort:: kernelQuick(int * array , int begin , int end){
	/**if(end - begin == 2){
	   if(array[begin] > array[end]){
	   array[begin] ^= array[end];
	   array[end] ^= array[begin];
	   array[begin] ^= array[end];
	   }
	   return ;
	   }
	   for(int i = begin ; i < end ; i++)
	   cout << array[i] << "\t";
	   cout << endl;
	   cout << "begin : " << begin << "\nend : " << end << endl;
	   int mid = _get_mid(array , begin , end);
	   cout << "MID : " << mid << endl;
	   kernelQuick(array , begin , mid);
	   kernelQuick(array , mid , end);*/
	if(begin >= end) return;
	int first = begin , last = end , key = array[begin];
	while(first < last){
		while(first < last && array[last] >= key) --last;
		array[first] = array[last];
		while(first < last && array[first] <= key) ++first;
		array[last] = array[first];
	}
	array[first] = key;
	kernelQuick(array , begin , first - 1);
	kernelQuick(array , first + 1 , end);
}

void sort::mergetSort(int * array , int length){
	emergeSort(array , 0 , length);
}

void sort::emergeSort(int * array ,int begin , int end){
	//cout << "Run the begin : " << begin << "\t end : " << end << endl;
	if(begin == end || end - begin == 1) return ;
	int mid = (begin + end) / 2;
	emergeSort(array , begin , mid);
	emergeSort(array , mid , end);
	merge(array , begin , mid , end);
}

void sort::merge(int * array , int begin , int mid , int end){
	/**for(int i = 0 ; i < 4 ; i++)
	   cout << array[i] << "\t";
	   cout << endl;
	   cout << "Begin : " << begin << endl;
	   cout << "Mid : " << mid << endl;
	   cout << "End : " << end << endl;*/
	int i = begin , j = mid , count = 0;
	/**for(int k = begin ; k < end ; k++){
	   cout << array[k] << "\t";
	   }
	   cout << endl;*/
	int * temp = new int[end - begin];
	while(i < mid && j < end)	temp[count++] = array[i] > array[j] ? array[j++]: array[i++];
	while(i < mid) temp[count++] = array[i++];
	while(j < end) temp[count++] = array[j++];
	/**cout << "Testing . see down . " << endl;
	   for(int i = 0 ; i < count ; i++){
	   cout << temp[i] << "\t";
	   }
	   cout << endl << "Over . " << endl;*/
	/**cout << "Print the temp Now : " << endl;
	   for(int i = 0 ; i < end - begin + 1 ; i++){
	   cout << temp[i] << "\t" ;
	   }
	   cout << "\nPrint Done .";*/
	for( int start = 0 , count = begin ; count < end ; count++ , start++)
    {
        /**if(temp[start] == 0) {
           cout << "Find here .  " << endl;
           }*/
        array[count] = temp[start];
        /**cout << "array[" << count <<"] = " << array[count] << endl;*/
    }
	delete temp;
}

void sort::bucketSort(int * array , int length){
	for(int i = 0 ; i < length ;i++)
		cout << array[i] << "\t";
	cout << endl;
	node * set = new node[10];
	int count = 0 , n = 0;
	node * temp;
	int max = array[0];
	for(int i = 0 ; i < length ; i++)	if(array[i] > max) max = array[i];
	while(max != 0){
		max /= 10;
		n++;
	}
	max = n;
	n = 0;
	while(n < max){
		count = 0;
		for(int i = 0 ; i < length; i++){
			int select = deal(array[i] ,n);
			temp = set[select].next;
			if(temp == NULL){
				//cout << "Head new node . " << endl;
				set[select].next = new node();
				set[select].next -> info = array[i];
				//cout << "temp -> info : " << array[i] << endl;;
			}else{
				while(temp->next != NULL) {
					//cout << "Find and will new node ." << endl;
					temp = temp -> next;
				}
				temp -> next = new node();
				temp -> next -> info = array[i];
				//cout << "temp -> next -> info : " << temp -> next -> info << endl;
			}
		}
		for(int i = 0 ; i < 10 ; i++){
			temp = set[i].next;
			node * dele = temp;
			while(temp != NULL){
				//cout << "set value to array : " << temp -> info << endl;
				dele = temp;
				array[count++] = temp -> info;
				temp = temp -> next;
				delete dele;
			}
			set[i].next = NULL;
		}
		n++;
	}
}


void sort::show(int * array , int length){
	for(int i = 0 ; i < length ; i++){
		cout << array[i] << "\t" ;
	}
	cout << endl;
}
int main(int argc , char ** argv){
	/**sort * SORT = new sort();
	   int * temp;
	   int length = SORT -> _get_array(temp);
	   //	SORT -> bucketSort(temp ,length);
	   for(int i = 0 ; i < length ; i++)
	   cout << temp[i] << "\t";
	   cout << endl;*/
	//SORT -> show(temp,length);
	//delete SORT;
	//delete temp;
	/**	cout << "Input the expression you wanna sort : " << endl;
		string accept = "";
		getline(cin , accept);
		int * expression = new int[accept.length()];
		for(int i = 0 ;i < accept.length() ;i++){
		expression[i] = 0;
		}
		int count = 0 , length = accept.length();
		char ch = accept[0];
		for(int i  = 0 ; i < length ; i++){
		ch = accept[i];
		if(ch >= '0' && ch <= '9'){
		expression[count] = expression[count] * 10 + ch-'0';
		if(i+1 == length || accept[i+1] < '0' || accept[i+1] > '9'){
		count++;
		}
		}
		}
		int * temp = new int[count];
		for(int i = 0; i < count ; i++){
		temp[i] = expression[i] ;
		}
		sort * s = new sort();
		s -> quickSort(temp , count);
		s -> show(temp , count);
		delete s;
		delete temp;*/
	sort * test = new sort();
	test -> _show_for_user();
	delete test;
	return 0;
}
