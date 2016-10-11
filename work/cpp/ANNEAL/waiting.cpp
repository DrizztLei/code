#include <iostream>
#include <ctime>
int main(){
	using namespace std;
	cout << "Enter the delay time , in seconds : "<< endl;
	float secs;
	cin >> secs;
	clock_t delay = secs * CLOCKS_PER_SEC;
	cout << "Starting \a \n" << endl;
	clock_t start = clock();
	while(clock() - start <= delay) ;
	cout << "Done " << endl;
	return 0;
}
