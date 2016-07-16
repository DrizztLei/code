#include <iostream>
#include <exception>
using namespace std;
struct node {
	int info;
	node * next;
};

struct _link_queue{
	node * front , * rear;
};


void init(_link_queue & queue){
	queue.front = queue.rear = NULL;
}

void _get_answer(){
	//cout<<"Input the condition of number : " << endl;
	int * expression = new int[9];
	int temp , count = 0;
	cin >> temp;
	int response = 1;
	for(int i = 8 ; i >= 0 ; i--){
		expression[i] = temp % 10;
		temp /= 10;
		cout << expression[i] << " is " << i<< endl;
	}

	_link_queue * set = new _link_queue[9];
	int count_set = 0 , count_array = 8 , min = 10 , backup;
	while(response != 10){
		for(int i = 0 ; i < count_set ; i++) {
			if(set[i].front != NULL) cout << "Traverl the min is :" << set[i].front->info << " of  " << i << endl;
			if(set[i].front != NULL && min > set[i].front->info) {
				min = set[i].front -> info;
				backup = i;
			}
		}
		cout << "Min : " << min << ". Expression[count_array] : " << expression[count_array] << " .\n";
		if(count_array >= 0 && min > expression[count_array]){
			//cout << expression[count_array] << " is expression[count_array]" << endl << "Response :" <<response << endl;
			if(expression[count_array] == response){
				//cout << "Move " << expression[count_array] << " in expression to response . " << endl;
				response ++;
				count_array--;
			}else{
				//cout << "Testing " <<endl;
				while(count_set > 0  && set[count_set-1].front == NULL){
					count_set--;
				}
				//cout << "Done " << endl;
				if(count_set != 0 && set[count_set-1].rear->info < expression[count_array] ){
					cout << expression[count_array];
					cout << "new node to add the sub . " << endl;
					set[count_set-1].rear -> next = new node;
					set[count_set-1].rear = set[count_set-1].rear->next;
					set[count_set-1].rear -> info = expression[count_array--];
					set[count_set-1].rear -> next = NULL;
				}else{
					cout << expression[count_array] << endl;
					++count_set;
					//cout << "Run in new node ." <<endl;
					set[count_set-1].front = set[count_set-1].rear =  new node;
					set[count_set-1].front -> info = set[count_set-1].rear -> info = expression[count_array--];
					//cout <<"Testing result is : " << set[count_set-1].front->info << endl; 
					//cout << "Move expression " << expression[count_array+1] << " to set " << count_set -1 << " ." <<endl;
				}
			}
		}else{
			if(min == response){
				node * temp = set[backup].front;
				//cout << set[backup].front->info << " : is info ." << endl;
				set[backup].front = set[backup].front -> next;
				//cout << (set[backup].front == NULL) << " is set[backup].front == NULL" <<  endl;
				delete temp;
				//cout << "Move " << min << " from "<< backup << " to response ." << endl;
				min = 10;
				response ++;
			}else{
				while(count_set > 0  && set[count_set-1].front == NULL){
					count_set--;
				}
				//cout << "Done " << endl;
				if(count_set != 0 && set[count_set-1].rear->info < expression[count_array] ){
					//cout << expression[count_array];
					//cout << "new node to add the sub . " << endl;
					set[count_set-1].rear -> next = new node;
					set[count_set-1].rear = set[count_set-1].rear->next;
					set[count_set-1].rear -> info = expression[count_array--];
					set[count_set-1].rear -> next = NULL;
				}else{
					cout << expression[count_array] << endl;
					++count_set;
					//cout << "Run in new node ." <<endl;
					set[count_set-1].front = set[count_set-1].rear =  new node;
					set[count_set-1].front -> info = set[count_set-1].rear -> info = expression[count_array--];
					//cout <<"Testing result is : " << set[count_set-1].front->info << endl; 
					//cout << "Move expression " << expression[count_array+1] << " to set " << count_set -1 << " ." <<endl;
				}
				//cout << "Response is : " << response << ". and the min is : " << min << " ." << endl;
				//	throw exception();
			}
		}
	}
	delete[] set;
}

int main(int argc , char ** argv){
	try{
		_get_answer();
	}catch(exception & e){
		cout << "Exception " << endl;
		cout << e.what() << endl;
	}
	return 0;
}
