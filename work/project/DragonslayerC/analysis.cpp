#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::istream;

const int cutoff = 6000;
const float rate1 = 0.3;
const float rate2 = 0.6;

class Replace{
private:
    bool is_comment;
    bool is_string;

public:
    string replace_string();
};


void Write(){
    ofstream file("TEST.txt" , std::ios::out|std::ios::ate);
    if(!file){
        cout << "Error in unable to open the file " << endl;
        return;
    }
    char ch;
    while(cin.get(ch))
    {
        if(ch=='\n')
            break;
        file.put(ch);
    }
    file.close();
}

void Read(){
    ifstream read("TEST.txt" , std::ios::in);
    if(!read){
        cout << "Unable to opent the file " << endl;
        return;
    }
    string temp;
    while()
    //char ch;
    /*    while(read.get(ch)){
        cout << "once " << endl;
        cout.put(ch);
        }*/
    cout << endl;
    cout << "DONE " << endl;
    read.close();
}

void get_content(){
    ifstream infile;
    ofstream outfile;
    int income , tax ;
    infile.open("income.in");
    outfile.open("tax.out");
    while(infile >> income){
        tax = income < cutoff ? rate1 * income : rate2 * income ;
        outfile << "Tax = " << tax << endl;
    }
}

 int main(int argc , char ** argv){
     //Read();
    //Write();
    //get_content();
    return 0;
}
