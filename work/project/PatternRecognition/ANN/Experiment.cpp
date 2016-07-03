#include <iostream>
#include <cmath>
#include <malloc.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <sstream>

using namespace std;

void Experiment(double * temp){
    //cout << ++xy<< endl;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            //cout << (temp + i * 4 + j) << "\t";
            cout << *(temp + i * 4 + j) << "\t" ;
        }
        cout << endl;
    }
}
double gaussrand(){
    static double V1, V2, S;
    static int phase = 0;
    double X;

    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;

            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);

        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);

    phase = 1 - phase;
    return X;
}
void test(){
    std :: ifstream in;
    string file = "train.txt";
    in.open(file.c_str());
    long count = 0;
    double var;
    double temp = 1 ;
    double sum = 0;
    while(!in.eof()){
        in >> var;
        temp = var;
        sum += temp;
        count ++;
    }
    cout << sum << endl;
    in.close();
//cout << count << endl;
    count -= 1;
    cout << count << endl;
//cout << "Number for : " << count << endl;
    if(count % 202 == 0) {
//cout << "%202 done " << endl;
//cout << "congratulation . " << endl;
        cout << "Sample confirm ." << endl;
    }else{
//cout << "GG" << endl;
        cout << "Sample is broken ! " << endl;
        exit(0);
    }
}

void Experiment(){
    double ** set;
    int number , size;
    /*
      int a = 4;
      int b = 4;
      double temp[a][b];
      double (*c)[b];

      for (int i = 0; i < 4; ++i)
      {
      for (int j = 0 ; j < 4; ++j)
      {

      temp[i][j] = i * j + 1;
      cout << temp[i][j] << "\t";
      cout << &temp[i][j] << "\t";
      cout << *((*temp+i) + j) << "\t";

      temp[i][j] = rand() % 100;
      cout << *(*(temp+i)+j) << "\t" ;
      //cout << (temp + i * 4  + j) << "\t";
      }
      cout << endl;
      }
      //cout << temp << endl;
      //cout << (double*) temp << endl;
      //Experiment((double*)temp);
      double dd[2][2];
      Experiment((double*)(temp));
      //Experiment((double*)dd);
      */
    /*
      for (int i = 0; i < 10; ++i)
      {
      for (int i = 0; i < 20; ++i)
      {
      cout << i << endl;
      }
      cout << "Target for : " << i << endl;
      }
    */
    /*
      for (int i = -10; i < 10; ++i)
      {
      cout << exp(i) << endl;
      }
      cout << log(0) << endl;
      for (int i = 0; i < 100; ++i)
      {
      cout << gaussrand() << endl;
      }
      cout << exp(1600) << endl;
    */
    //cout << -log(1.0/6) << endl;
    //cout << (2 * 10 ^ (-2)) << endl;
}


void test2(){
    //test();
    /*
      string temp ;
      temp = '2';
      temp += "\t";
      temp += "dkfjdsla";
      int a = 545465;
      string inter = "dkslf";

      cout << inter << endl;
      cout << temp << endl;
    */
    stringstream s;
    s << 234567;
    string a = s.str();
    s.str("");
    s << 1234567890;
    cout << s.str() << endl;
    cout << a << endl;
}

int main(int argc , char ** argv){
    /*
    std::ofstream out;
    string filename = "test.test";
    out.open(filename.c_str());
    if(out.is_open()){
        out << "write in " << endl;
        out.close();
    }else {
        cout << "Error for the resources busy ." << endl;
        exit(1);
    }

    out.open(filename.c_str());
    if(out.is_open()){
        out << "hahahha" << endl;
    }else{
        cout << "exception for open file" << endl;
    }
    */
    //cout << (double)rand() / RAND_MAX << endl;
    double rate =  pow(double(201/6.0) , 1/2.0) ;
    int temp = 201;
    temp =  temp / rate;
    cout << temp << endl;
    temp = temp / rate;
    cout << temp << endl;
    temp = temp / rate;
    cout << temp << endl;
    return 0;
}
