#include <iostream>
#include <string>
namespace elementary{
	using namespace std;
	using std::cout;
	using std::endl;
	namespace embeded{
		int haha;
		string temp = "temp";
	}
	int temp;
	void say_test(){
		cout << "The test will be printed . " << endl;
	}
}

int main(int argc ,char * argv[]){
	using namespace elementary;
	namespace refrerence = elementary :: embeded ;
	//	using namespace std;
	cout << "using namespace embedded successfully " << endl;
	say_test();
	return 0;
}
