#include <iostream>
#include <vector>
#include <exception>
#include <stdio.h>
#include <cstring>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::exception;
using std::string;

struct Haffman{
	float rate;
	int info;
	Haffman * left , * right;
	Haffman(float data ,  Haffman * h_left = NULL , Haffman * h_right = NULL){
		rate = data;
		left = h_left;
		right = h_right;
	}
};

struct node {
	node * left , * right;
	int info;
	node(int data , node * n_left = NULL , node * n_right = NULL){
		info = data;
		left = n_left;
		right = n_right;
	}
};

class heap{
private:
	int size , length;
	int * array;
	node * root = NULL;
	node * BinTree = NULL;
	Haffman * haffman = NULL;
	void delete_tree(node * root);
	void delete_h(Haffman * root);
	void show_haffman(Haffman * root);
	void show_b_s_t(node * root);
public:
	void build(int n);
	void build_max(int n);
	void _heap_sort();
	void show();
	void insert(int info);
	void remove();
	void huffman();
	void t_b_s();
	void show_t_b_s();
	void _b_s_t();
	void show_b_s_t();
	//void quicksort(int * matrix_int , float * matrix , int begin , int end);
	void show_haffman();
	heap(int array [] , int n);
	virtual ~heap();
};

void heap :: show_haffman(){
	//Haffman * temp = haffman;
	//show_haffman(temp);
	vector<Haffman*> left;
	vector<Haffman*> right;
	string count = "0";
	left.push_back(haffman);
	while(left.size() != 0 || right.size() != 0){
		if(left.size() != 0){
			//cout << "LEFT " << endl;
			int size = left.size();
			for(int i = 0 ; i < size ; i++){
				if(left[i] -> left == NULL && left[i] -> right == NULL){
					cout << "Get the the " << left[i] -> info << " huffman code :  " <<  count << endl;
					if(count[count.length() - 1] != '0'){
						for(int i = count.length() - 1; i >= 0 ; i-- ){
							if(count[i] == '1'){
								count[i] = '0';
								if(i == 0) count = "1" + count;
							} else {
								count[i] = '1';
								break;
							}
						}
					}else {
						count[count.length() - 1] = '1';
					}
				}
				if(left[i] -> left != NULL)
					right.push_back(left[i] -> left);
				if(left[i] -> right != NULL)
					right.push_back(left[i] -> right);
			}
			left.clear();
		}else{
			//cout << "RIGHT " << endl;
			int size = right.size();
			for(int i = 0 ; i < size ; i++){
				if(right[i] -> left == NULL && right[i] -> right == NULL){
					cout << "Get the the " << right[i] -> info << " huffman code :  " <<  count << endl;
					if(count[count.length() - 1] != '0'){
						for(int i = count.length() - 1; i >= 0 ; i-- ){
							if(count[i] == '1'){
								count[i] = '0';
								if(i == 0) count = "1" + count;
							} else {
								count[i] = '1';
								break;
							}
						}
					}else {
						count[count.length() - 1] = '1';
					}
				}
				if(right[i] -> left != NULL)
					left.push_back(right[i] -> left);
				if(right[i] -> right != NULL)
					left.push_back(right[i] -> right);
			}
			right.clear();
		}
	}
	left.clear();
	right.clear();
}

/**void heap :: show_haffman(Haffman * root){
   if(root == NULL) return;
   cout << root -> rate << endl;
   if(root -> left == NULL && root -> right == NULL){
   cout << root -> rate << endl;
   cout << root -> info << endl;
   }
   show_haffman(root -> left);
   show_haffman(root -> right);
   }
*/

/*void heap :: quicksort(int * matrix_int , float * matrix , int begin , int end){
	if(begin >= end) return;
	int start = begin , over = end , key = matrix[begin] , key_int = matrix_int[begin];
	//cout << "Start : " << start << endl << "Over : " << over << endl;
	while(start < over){
		while(start < over && matrix[over] >= key) over --;
		matrix[start] = matrix[over];
		matrix_int[start] = matrix_int[over];
		while(start < over && matrix[begin] <= key) start ++;
		matrix[over] = matrix[start];
		matrix_int[over] = matrix_int[start];
		//cout << "Start : " << start << endl << "Over : " << over << endl;
	}
	matrix[start] = key;
	matrix_int[start] = key_int;
	quicksort(matrix_int , matrix , begin , start - 1);
	quicksort(matrix_int , matrix , start + 1 , end);
	}*/

void heap :: show_b_s_t(){
	node * temp = BinTree;
	show_b_s_t(temp);
	cout << endl;
}

void heap :: show_b_s_t(node * root){
	if(root != NULL){
		show_b_s_t(root -> left);
		cout << root -> info << '\t' ;
		show_b_s_t(root -> right);
	}
}

void heap :: _b_s_t(){
	BinTree = new node(array[1]);
	node * temp = BinTree;
	int left , right;
	for(int i = 2 ; i < length ; i++){
		while(1){
			if(temp -> left != NULL && temp -> right != NULL){
				if(array[i] >= temp -> info){
					temp = temp -> right;
				}else{
					temp = temp -> left;
				}
			}else if(temp -> left == NULL && temp -> right == NULL){
				(array[i] >= temp -> info ? temp -> right : temp -> left) = new node(array[i]);
				break;
			}else if(temp -> left == NULL){
				if(array[i] >= temp -> info)
					temp = temp -> right;
				else{
					temp -> left = new node(array[i]);
					break;
				}
			}else if(temp -> right == NULL){
				if(array[i] >= temp -> info){
					temp -> right = new node(array[i]);
					break;
				}
				else{
					temp = temp -> left;
				}
			}else {
				cout << "Bug here . " << endl;
				throw new exception();
			}
		}
		temp = BinTree;
	}
	//cout << "Show the binary search tree sort : " << endl;
	//show_b_s_t(temp);
	//cout << endl;
}


void heap :: insert(int info){
	/*size = length += 1;
	  int * matrix = new int[length];
	  for(int i = 2 ; i < length ; i++)
	  matrix[i] = array[i-1];
	  matrix[1] = info;
	  int * temp = array;
	  array = matrix;
	  delete temp;
	  build_max(length);
	*/
	int * matrix = new int[length+1];
	for(int i = 0 ; i < length ; i++)
		matrix[i] = array[i];
	matrix[length] = info;
	size = length += 1;
	int * temp = array;
	array = matrix;
	delete[] temp;
	int position = length - 1;
	//cout << array[position] << endl << array[position/2] << endl;
	while(position != 1){
		if(array[position] > array[position / 2]){
			int store = array[position];
			array[position] = array[position/2];
			array[position/2] = store;
			position /= 2;
		}else {
			break;
		}
	}
	t_b_s();
}

void heap :: remove(){
	/*int * matrix = new int[length];
	  for(int i = 1 ; i + 1 < length; i++)
	  matrix[i] = array[i+1];
	  int * temp = array;
	  array = matrix;
	  delete temp;
	  size = length -= 1;
	  build_max(length);
	*/
	array[1] = array[length-1];
	int * temp = new int[length - 1];
	for(int i = 1 ; i < length - 1; i++)
		temp[i] = array[i];
	int * del = array;
	array = temp;
	delete[] del;
	size = length -= 1;
	int position = 1;
	while( 2 * position < size){
		if(array[position] < array[2 * position]){
			int largest;
			if(2 * position + 1 < size){
				largest = array[2 * position] > array[2 * position + 1] ? 2 * position : 2 * position + 1;
			}else{
				largest = 2 * position;
			}
			int sotre = array[position];
			array[position] = array[largest];
			array[largest] = sotre;
			position = largest;
		}else if(2 * position + 1 < size && array[position] < array[2 * position + 1]){
			int temp = array[position];
			array[position] = array[2 * position + 1];
			array[2 * position + 1] = temp;
			position = position * 2 + 1;
		}else{
			break;
		}
	}
	t_b_s();
}

void heap :: huffman(){
	int * matrix_int = new int[length];
	float * matrix_fre = new float[length];
	for(int i = 0 ; i < length ; i++){
		matrix_fre[i] = 0 ; 
	}
	int count = 1;
	matrix_int[0] = array[1];
	for(int i = 1 ; i < length ; i++){
		for(int j = 0 ; j < count; j++ ){
			if(array[i] == matrix_int[j]){
				matrix_fre[j] += 1;
				break;
			}
			if(j + 1 == count){
				matrix_int[j+1] = array[i];
				matrix_fre[j+1] ++;
				count ++;
				break;
			}
		}
	}
	//quicksort(matrix_int , matrix_fre , 0 , count-1 );
	cout << "Now the huffman is : " << endl;
	for(int i = 0; i < count ; i++)
		cout << matrix_int[i] << "\t";
	cout << endl;
	for(int i = 0 ; i < count ; i++)
		matrix_fre[i] /= length-1;
	cout << "Now the frequence is : " << endl;
	for(int i = 0 ; i < count ; i++)
		cout << matrix_fre[i] << "\t";
	cout << endl;
	vector<Haffman*> set;
	for(int i = 0 ; i < count ; i++){
		set.push_back(new Haffman(matrix_fre[i]));
		set[i] -> rate = matrix_fre[i];
		set[i] -> info = matrix_int[i];
	}
	int i , j ;
	while(set.size() > 1){
		/*for(int l = 0 ; l < set.size() ; l++){
			cout << "Print the set[" << l << "] for : " << set[l] -> rate << endl;
			}*/
		i = 0 , j = 1;
		for(int k = 2 ; k < set.size() ; k++){
			if(set[i] -> rate > set[j] -> rate){
				if(set[i] -> rate > set[k] -> rate){
					i = k;
				}
			}else {
				if(set[j] -> rate > set[k] -> rate){
					j = k;
				}
			}
		}
		//cout << "I : " << i << "\tJ : " << j << endl;
		//cout << "You wanna : " << set[i] -> rate + set[j] -> rate << endl;
		set[i] = new Haffman(set[i] -> rate + set[j] -> rate , set[i] , set[j]);
		//cout << "Assign : " << set[i] -> rate << endl;
		//cout << "Assigned's Size : " << set.size() << endl;
		//cout << "Size : " << set.size() << "\nThe rease aim is : " << j << endl;
		set.erase(set.begin() + j);
		//cout << "Now the size is : " << set.size() << endl;
	}
	haffman	= set[0];
	set.clear();
	//cout << "IS NULL ? " << (haffman == NULL) << endl;
	delete matrix_int;
	delete matrix_fre;
}

void heap :: delete_h(Haffman * temp){
	if(temp == NULL) return;
	delete_h(temp -> left);
	delete_h(temp -> right);
	delete temp;
}

void heap :: t_b_s(){
	vector<node*> left;
	vector<node*> right;
	root = new node(array[1]);
	int count = 2;
	left.push_back(root);
	while(1){
		if(left.size()){
			for(int i = 0 ; i < left.size(); i++){
				left[i] -> left = new node(array[count++]);
				if(count >= length){
					left.clear();
					return;
				}
				left[i] -> right = new node(array[count++]);
				if(count >= length){
					left.clear();
					return;
				}
				right.push_back(left[i] -> left);
				right.push_back(left[i] -> right);
			}
			left.clear();
		}else if(right.size()){
			for(int i = 0 ; i < right.size(); i++){
				right[i] -> left = new node(array[count++]);
				if(count >= length){
					right.clear();
					return;
				}
				right[i] -> right = new node(array[count++]);
				if(count >= length){
					right.clear();
					return;
				}
				left.push_back(right[i] -> left);
				left.push_back(right[i] -> right);
			}
			right.clear();
		}else {
			cout << "Error . " << endl;
		}
	}
	left.clear();
	right.clear();
}

void heap :: show_t_b_s(){
	vector<node*> left;
	vector<node*> right;
	bool flag = true;
	int count = 1;
	left.push_back(root);
	while(left.size() != 0 || right.size() != 0){
		if(left.size() != 0){
			int size = left.size();
			for(int i = 0 ; i < size ; i++){
				if(flag) cout << "Get the " << count << " info : " << left[i] -> info << endl;
				if(left[i] -> left != NULL)
					right.push_back(left[i] -> left);
				if(left[i] -> right != NULL)
					right.push_back(left[i] -> right);
			}
			left.clear();
		}else{
			int size = right.size();
			for(int i = 0 ; i < size ; i++){
				if(flag) cout << "Get the " << count << " info : " << right[i] -> info << endl;
				if(right[i] -> left != NULL)
					left.push_back(right[i] -> left);
				if(right[i] -> right != NULL)
					left.push_back(right[i] -> right);
			}
			right.clear();
		}
		count ++ ;
	}
	left.clear();
	right.clear();
}

heap :: ~heap(){
	delete[] array;
	delete_tree(root);
	delete_tree(BinTree);
	delete_h(haffman);
}

void heap :: delete_tree(node * root){
	if(root == NULL) return;
	delete_tree(root -> left);
	delete_tree(root -> right);
	delete root;
}

heap :: heap(int matrix [] , int n){
	size = length = n + 1;
	array = new int[length];
	for(int i = 1 ; i < length ; i++)
		array[i] = matrix[i-1];
	array[0] = 0;
	_b_s_t();
	build_max(length);
	t_b_s();
	//huffman();
	//show();
	//_heap_sort();
}

void heap :: show(){
	for ( int i = 1 ; i < length ; i++)
		cout << array[i] << '\t' ;
	cout << endl;
}

void heap :: build(int n){
	int left = n * 2 , right = n * 2 + 1 , largest = n;
	if(left < size && array[left] > array[n])
		largest = left;
	if(right < size && array[right] > array[largest])
		largest = right;
	if(largest != n){
		int temp = array[n];
		array[n] = array[largest];
		array[largest] = temp;
		build(largest);
	}
}

void heap :: build_max(int n){
	for(int i = n / 2 + 1 ; i > 0 ; i--){
		build(i);
	}
}

void heap :: _heap_sort(){
	//cout << array[1] << endl;
	//cout << "AR end : " << array[length-1] << endl;
	build_max(length);
	for(size = length ; size > 1 ;){
		int temp = array[1];
		//cout << "array[1] : " << array[1] << endl;
		//cout << "array[size-1] : " << array[size-1] << endl;
		array[1] = array[size-1];
		array[size-1] = temp;
		size -- ;
		build_max(size-1);
		//cout << "array[1] : " << array[1] << endl;
		//cout << "array[size] : " << array[size] << endl;
	}
}

int main(int argc , char ** argv){
	/**int * temp = new int[9];
	cout << "Before creating the max heap : " << endl;
	for(int i = 0 ; i < 9 ; i++){
		temp[i] = - i * i + 6 * i + 3;
		cout << temp[i] << "\t" ;
	}
	cout << endl;*/
	int * temp;
	cout << "Input the length . " << endl;
	int length ;
	cin >> length;
	temp = new int[length];
	for(int i = 0 ; i < length ; i ++){
		cout << "Input the " << i+1 << " figure . " << endl;
		cin >> temp[i];
	}
	cout << "This is what you ever inputed . " << endl;
	for(int i = 0 ;i < length ; i ++)
		cout << temp[i] << '\t';
	cout << endl;
	cout << "After creating the max heap(init . ) : " << endl;
	heap H(temp , length);
	H.show();	
	cout << "Show the tree structrue : " << endl;
	H.show_t_b_s();				 
	cout << "After inserting the heap : " << endl;
	H.insert(25);				 
	H.show();
	cout << "Show the tree structrue : " << endl;
	H.show_t_b_s();				 
	cout << "Removing . " << endl;
	H.remove();
	cout << "After removing the root element : " << endl;
	H.show();
	cout << "Show the tree structrue : " << endl;
	H.show_t_b_s();				 
	cout << "show the haffman . " << endl;
	H.huffman();
	H.show_haffman();
	cout << "Show the binary tree search : " << endl;
	H._b_s_t();
	H.show_b_s_t();
	cout << "Show the heap sort : " << endl;
	H._heap_sort();
	H.show();
	/**heap H(temp , 9);
	   H.show();
	   cout << "After heap sort : " << endl;
	   H._heap_sort();
	   H.show();
	   cout << "After initing the heap : " << endl;
	   H.show();
	   cout << "Show the tree structrue : " << endl;
	   H.show_t_b_s();
	   H.show_t_b_s();
	   cout << "Removing . " << endl;
	   H.remove();
	   cout << "After removing the root element : " << endl;
	   H.show();
	   cout << "Show the tree structrue : " << endl;
	   H.show_t_b_s();
	   H._heap_sort();*/
	/*
	  cout << "show doen . " << endl;
	  int * hah = little_test();
	  for(int i = 0 ;i <  19 ; i++){
	  cout << hah[i] << "\t";
	  }
	  cout << endl;
	*/
	return 0;
}
