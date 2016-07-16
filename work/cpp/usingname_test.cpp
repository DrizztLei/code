#include <iostream>
#include <string>
namespace Jill{
	using namespace std;
	void simple_test(){
		cout << "Test for the using struct and initzalizaiton the funciton in struct" << endl;
	};
	int fetch = 3456;
	struct test{int temp; string hello;};
};

int fetch;

int main(int argc , char * argv[]){
	using namespace Jill;
	using namespace std;
	int fetch ;
	fetch = 0;
	test AK = {2};
	AK.hello = "I'd like a tuna fish sandwhich .";
	cout << AK.hello << endl;
	simple_test();
	test with_string = { 32456 , "with string's initizaitong . "};
	cout << "initzation with string successfully ." << endl;
	::fetch =1;
	cout << fetch << endl;
	cout << ::fetch << endl;
	cout << Jill::fetch << endl;
	return 0;
}
