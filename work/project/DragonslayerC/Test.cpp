#include<iostream>
#include<istream>
#include<ostream>
#include<cstring>
#include<vector>
#include <stdio.h>
using namespace std;
#define TAB
#define SWAP(X,Y) cout << X+Y << endl;

#define A ABC

int  get(){
    return 99;
}

#define D cout << "HELLO WORLD > " << endl;
int main(int argc, char ** argv){
    /*vector<int> temp = vector<int>();
      temp.push_back(2);
      temp.push_back(2333);
      temp.erase(temp.begin() + 1);
      cout << temp[0] << endl;*/
    //string temp = "ddddab";
    //cout << temp.substr(1,temp.length()) << endl;
    //cout << 'A' - 'z' << endl;
    //D;
    string temp = "abcdefg";
    cout << temp.substr(2,4) << endl;
    return 0;
}
