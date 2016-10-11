# include <iostream>
# include <cstring>
# include <string.h>
using namespace std;

void test(int a[]){
    int ** temp ;
    temp = & a;
    (*temp) = NULL;
    cout << "DONE " << endl;
    a = new int[22];
    a[2] = 2345;
}


int main(){
	/*
      const int Size = 15;
      char name1[Size] , name2[Size];
      cout<<"Waiting for inpu " <<endl;
      cin >> name1;
      cout<< "We know the name is " << name1 << "\t and the length is : " << strlen(name1);
      cout << "This array of size of is " << sizeof (name1)<< " bytes .\n" <<endl;
      name1[2] = '\0';
      cout<<"If name1[2] = '\\n' " << name1<<endl;
      cout<< "The test is over now " <<endl;
    */
    int a[10] = {1,2,3,4,5,6,7};
    test(a);
    return 0;
}
