#include <iostream>
using namespace std;

void Symmetric_Matrix(int n , int ** input){
	int k = (1 + n) * n / 2;
	int * matrix = new int[k];
	k = 0;
	int count = 0;
	while(count ++ < n){
		for(int i = 0 ; i < count ;i ++){
			for(int j = 0 ; j < i ; j++){
				matrix[i*(i+1)/2 + j] = input[i][j];
			}
		}
	}
	for(int i = 0 ; i < k ; i++){
		cout << matrix[i] << "\t" ;
	}
	cout << "DONE > "<< endl;
}

void Triangle_Matrix(int n , int ** input){

	/**What made me strang is the when
	   i >= j k = i*(i+1)/2 + j
	   i < j k = n*(n+1)/2
	*/
	int k = (1 + n) * n / 2;
	int * matrix = new int[k];
	k = 0;
	int count = 0;
	while(count ++ < n){
		for(int i = 0 ; i < count ;i ++){
			for(int j = 0 ; j < i ; j++){
				matrix[i*(i+1)/2 + j] = input[i][j];
			}
		}
	}
	for(int i = 0 ; i < k ; i++){
		cout << matrix[i] << "\t" ;
	}
	cout << "DONE > "<< endl;
}
int main(int argc , char ** argv){
	
	Symmetric_Matrix(3 , temp);
	return 0;
}
