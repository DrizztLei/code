#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <iomanip>
using namespace std;

void read_file(string filename){
    std::ifstream in;
    in.open(filename.c_str());
    if(in.is_open()){
        string var;
        while(in.good()){
            in >> var;
            cout << var ;
        }
    }
}

void write_file(string filename){
    std::ofstream out;
    out << std::fixed << std::setprecision(6);
    out.open(filename.c_str());

    for (int i = 0; i < 100; ++i)
    {
        out << "ni + 测试 + " << i/9.0 << "\t";
        out << endl;
    }
    out.close();
}

inline void print(int argc , int * array){
    for (int i = 0; i < argc; ++i)
    {
        cout << array[i] << "\t" ;
    }
    cout << endl;
}

void save(){
    std::ofstream file("archive.txt");
    std::string s = "Hello world ~\n";
}

int show(){
    int size ;
    cin >> size;
    float * temp = new float[size];
    for (int i = 0; i < size; ++i)
    {
        if(temp[i] != 0){
            cout << "Error for data . " << endl;
            delete temp;
            exit(1);
        }
    }
    cout << "DONE" << endl;
    delete temp;
}
/*
int main(int argc , char ** argv){
    //save();
    //cout << "Save done . " << endl;
    //system("echo \"hello world\"");
    //float temp = 2;
    //cout << std::fixed << setprecision(6) << temp << endl;
    //show();
    write_file("nihao.txt");
    //read_file("nihao.txt");
    return 0;
}
*/
