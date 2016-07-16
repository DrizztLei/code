#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char ** argv){
    for(int i = 0 ; i < 100 ; i++)
        cout << rand() / (double)RAND_MAX << endl;
    return 0;
}
