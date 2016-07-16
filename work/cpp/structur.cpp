# include <iostream>
struct test{
	char name[20];
	float volume;
	double price;
};

int main(){
	using namespace std;
	test form ={
		"leichaoF",
		2.234,
		3423.42345
	};
	cout<<"Call the number of price of test->form " << form.price<<endl;
	return 0;
}
