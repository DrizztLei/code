#include <iostream>
#include <string.h>
#include <cstring>
#include <exception>
#include <cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::exception;


void swap(int * a , int * b){
	int * temp = b;
	b = a;
	a = temp;
}

void _show_permutation_reccurse(int * matrix , int k , int length){
	if(k == 0) {
		for (int i = 0 ; i < length; i++){
			cout << matrix[i] << "\t";
		}
		cout << endl;
		return ;
	}else{
		for(int i = k ; i >=0 ; i-- ){ 
			int temp = matrix[k];
			matrix[k] = matrix[i];
			matrix[i] = temp;
			_show_permutation_reccurse(matrix , k - 1 , length);
			temp = matrix[k];
			matrix[k] = matrix[i];
			matrix[i] = temp;
		}
	}
}

void _get_permutation(){
	cout << "Input the number of int * : " << endl;
	int length ;
	cin >> length;
	int * matrix = new int[length];
	for ( int i = 0 ; i < length ; i++){
		cout << "Input the " << i+1 << " number : " << endl;
		cin >> matrix[i];
	}
	_show_permutation_reccurse(matrix , length-1 , length);
	delete[] matrix;
}

void _show_matrix(int * matrix , int length){
	for ( int i = 0 ; i < length ; i ++){
		cout << matrix[i] << "\t" ;
	}
	cout << endl;
}


void qsort(int * matrix , int begin , int length){
	int min;
	for(int i = begin ; i < length ; i++){
		min = i;
		for(int j = i ; j < length ;j++){
			if(matrix[j] < matrix[min]) min = j;
		}
		/**matrix[i] ^= matrix[min];
		matrix[min] ^= matrix[i];
		matrix[i] ^= matrix[min];*/
		int temp = matrix[i];
		matrix[i] = matrix[min];
		matrix[min] = temp;
	}
}


void _get_permutation_without(){
	cout << "Input the number of int * : " << endl;
	int length ;
	cin >> length;
	int * matrix = new int[length];
	for ( int i = 0 ; i < length ; i++){
		cout << "Input the " << i+1 << " number : " << endl;
		cin >> matrix[i];
	}

	int position_i , position_j  ;
	_show_matrix(matrix , length);
	for(int i = length - 1; i > 0 ; i--){
		if(matrix[i-1] < matrix[i]) {
			position_i = i-1;
			position_j = i;
			for(int j = length-1 ; j >= i ; j--){
				if(matrix[j] > matrix[position_i] && matrix[j] < matrix[position_j]) position_j = j;
			}
			/**matrix[position_i] ^= matrix[position_j];
			matrix[position_j] ^= matrix[position_i];
			matrix[position_i] ^= matrix[position_j];*/
			int temp = matrix[position_i] ;
			matrix[position_i] = matrix[position_j];
			matrix[position_j] = temp;
			
			qsort(matrix , i , length);
			i = length;

			_show_matrix(matrix , length);
		}
	}
	delete matrix;
}
int main(int argc , char ** argv){
	_get_permutation();
	/**	int a = 2 , b = 346;
	a ^= b;
	b ^= a;
	a ^= b;
	//	cout << "A : " << a << endl << "B : " << b << endl;
	int * temp = new int[2];
	temp[0] = 234567;
	temp[1] = 3;
	temp[0] ^= temp[1];
	temp[1] ^= temp[0];
	temp[0] ^= temp[1];
	//seperator here . 	
	temp[0] ^= temp[1];
	temp[1] ^= temp[0];
	temp[0] ^= temp[1];
	//	cout << "TEMP[0] : " << temp[0] << endl << "TEMP[1] : " << temp[1] << endl;
	delete[] temp;*/
	//	_get_permutation_without();
	//	_show_permutation_reccurse();
	return 0;
}
