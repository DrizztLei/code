#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <malloc.h>

using std :: cout;
using std :: endl;
using std :: cin;
using std :: string;

int const static LIMIT = 19;

template <typename T>
class Ann
{
public:
    Ann(int input , int argc , int * detailed , int output , double rate , double lambda);
    virtual ~Ann();
    void load(string filename);
    void save();
    void print_weight();
    int train(double * input , double * output);
    void train(T ** set , int number , int times);
    bool adjust_output(double * target);
    bool adjust_hidden();
    void calculator();
    int get_argc_input();
    int get_argc_output();
    void set_input(double * argc);
    bool get_result(double goal);
    void write_file(string filename);
private:
    double * input , ** level , * output , *** weight , ***best_weight, * target , * err , ** offset ;
    double rate , lambda;
    int argc_input , argc_level , argc_output , * info;
    //vector<double *> list;
    double ** list , ** medium , ** origin;
    double *** record;
    int point , size;
    bool init(int input , int argc , int * detailed , int end);
    void init_level();
    double sigmod(double value);
    void free(double * array);
    void free(int argc , double ** matrix);
    void free(int argc , int * argv , double *** matrix);
    void free(int * array);
    void copy(int * info , int * detailed , int argc);
    double sum(int level , int input , int output);
    double get_random();
    void print_output();
    void print_input();
    void print_level();
    double calculator_err(int i);
    double get_err(int i);
    void pre_process();
    double offset_sum(int target);
    double get_regular();
    void softmax(T ** set);
    void dot(double ** x , double ** y, int m , int n , int p , bool flag);
    void compute_gradient();
    void copy_level(int i);
    void copy_input(int i);
};

template <typename T>
void Ann<T> :: copy_level(int position){
    for (int i = 0; i < argc_level; ++i)
    {
        for (int j = 0 ; j < info[i]; ++j)
        {
            record[position][i][j] = level[i][j];
            /*
            cout << record[position][i][j] << endl;
            cout << "position : " << position << endl;
            cout << "i : " << i << endl;
            cout << "j : " << j << endl;
            */
        }
    }

}

template <typename T>
void Ann<T> :: copy_input(int position){
    for (int i = 0; i < argc_input; ++i)
    {
        origin[position][i] = input[i];
    }
}

template <typename T>
void Ann<T> :: dot(double ** x ,double ** y , int m , int n , int p , bool flag){
    if(flag){
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < p; ++j)
            {
                double sum = 0;
                for (int k = 0; k < n; ++k)
                {
                    sum += x[i][k] * y[k][j];
                }
                medium[i][j] = sum;
            }
        }
    }else{
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < p; ++j)
            {
                double sum = 0;
                for (int k = 0; k < n; ++k)
                {
                    sum += x[i][k] * y[k][j];
                }
                list[i][j] = sum;
            }
        }
    }
}

template <typename T>
void Ann<T> :: compute_gradient(){
    // true for list , flase for medium
    for (int i = argc_level - 1 ; i >= 0; --i)
    {
        if(i == argc_level - 1){
            //double temp[info[i]][point];
            double ** temp;
            temp = new double * [info[i]];
            //cout << record[0][1][16] << endl;

            cout << "info[i] : " << info[i] << endl;
            cout << "point : " << point << endl;
            cout << "flag " << endl;

            //temp[16] = new double[point];

            for (int j = 0; j < info[i]; ++j)
            {

                cout << "\t " << j << endl;
                temp[j] = new double[point];
                //temp[j] = (double*)malloc(sizeof(double)*point);

                for (int k = 0 ; k < point; ++k)
                {
                //cout << "record : " << record[k][i][j] << endl;
                //cout << "k : " << k << "\t i : " << i << "\t j: " << j << endl;
                //cout << temp[j][k] << endl;
                temp[j][k] = record[k][i][j];
                //cout << temp[j][k] << endl;
                }
                //cout << "Adjusting .." << endl;
            }
            cout << "passing. "  << endl;
            dot(temp , list , info[i] , point , argc_output ,  false);
            cout << "dot error " << endl;
            for (int j = 0; j < info[i]; ++j)
            {
                delete [] temp[j];
            }
            delete[] temp;
            for (int j = 0; j < argc_output; ++j)
            {
                offset[i+1][j] += -rate * offset_sum(j) ;
            }
            //double replace[argc_output][info[i]];
            double ** replace = new double*[argc_output];
            for (int j = 0; j < argc_output; ++j)
            {
                replace[j] = new double[info[i]];
                for (int k = 0; k < info[i]; ++k)
                {
                    replace[j][k] = weight[argc_level][k][j];
                }
            }
            dot(list, replace , point , argc_output ,info[i] , true);
            for (int j = 0; j < argc_output; ++j)
            {
                delete []replace[j];
            }
            delete[]replace;
            cout << "Error " << endl;
            // question here for you need to change it .
            for (int j = 0; j < point; ++j)
            {
                for (int k = 0; k < info[i]; ++k)
                {
                    if(record[j][i][k] <= 0){
                        list[j][k] = 0;
                    }
                }
            }
            for (int j = 0; j < info[argc_level-1]; ++j)
            {
                for (int k = 0; k < argc_output; ++k)
                {
                    weight[argc_level][j][k] += - rate * medium[j][k] * lambda * weight[argc_level][j][k];
                }
            }
        }else {
            //double temp[info[i]][point];
            double ** temp = new double*[info[i]];
            for (int j = 0; j < info[i]; ++j)
            {
                temp[j] = new double[point];
                for (int k = 0 ; k < point; ++k)
                {
                    temp[j][k] = record[k][i][j];
                }
            }
            dot(temp , list , info[i] , point , info[i+1] , false); // asming we've finished it
            for (int j = 0; j < info[i]; ++j)
            {
                delete[] temp[j];
            }
            delete[] temp;
            for (int j = 0; j < info[i]; ++j)
            {
                offset[i][j] += -rate * offset_sum(j);
            }
            // question here .
            //double replace[info[i+1]][info[i]];
            double ** replace = new double* [info[i+1]];
            for (int j = 0; j < info[i+1]; ++j)
            {
                replace[j] = new double[info[i]];
                for (int k = 0; k < info[i]; ++k)
                {
                    replace[j][k] = weight[i+1][k][j];
                }
            }
            dot(list, replace , point , info[i+1] ,info[i] , true); // weight need T
            for (int j = 0; j < info[i+1]; ++j)
            {
                delete[] replace[j];
            }
            delete[] replace;
            // add the rest here .
            for (int j = 0; j < point; ++j)
            {
                for (int k = 0; k < info[i]; ++k)
                {
                    if(record[j][i][k] <= 0){
                        list[j][k] = 0;
                    }
                }
            }
            for (int j = 0; j < info[i]; ++j)
            {
                for (int k = 0; k < info[i+1]; ++k)
                {
                    weight[i+1][j][k] += - rate * medium[j][k] * lambda * weight[i+1][j][k];
                }
            }
        }
        //double temp[argc_input][point];
        double ** temp = new double*[argc_input];
        for (int j = 0; j < argc_input; ++j)
        {
            temp[j] = new double[point];
            for (int k = 0; k < point; ++k)
            {
                temp[j][k] = origin[k][j];
            }
        }
        dot(temp , list , argc_input , point , info[0] , false);
        for (int j = 0; j < argc_input; ++j)
        {
            delete[] temp[j];
        }
        delete[] temp;
        for (int j = 0; j < argc_output; ++j)
        {
            offset[0][j] += -rate * offset_sum(j);
        }
        for (int j = 0; j < info[argc_level-1]; ++j)
        {
            for (int k = 0; k < argc_output; ++k)
            {
                weight[0][j][k] += - rate * medium[j][k] * lambda * weight[0][j][k];
            }
        }
    }
}

template <typename T>
double Ann<T> :: get_regular(){
    int regular = 0;
    for (int i = 0; i < argc_level ; ++i)
    {
        if(i == 0){
            for (int j = 0; j < argc_input; ++j)
            {
                for (int k = 0 ; k < info[0]; ++k)
                {
                    regular += pow(weight[0][j][k] , 2);
                }
            }
        }else{
            for (int j = 0; j < info[i-1]; ++j)
            {
                for (int k = 0 ; k < info[i]; ++k)
                {
                    regular += pow(weight[i][j][k], 2);
                }
            }
        }
    }
    for (int i = 0; i < info[argc_level-1]; ++i)
    {
        for (int j = 0 ; j < argc_output; ++j)
        {
            regular += pow(weight[argc_level][i][j], 2);
        }
    }
    return regular;
}

template <typename T>
double Ann<T> :: offset_sum(int position){
    double sum = 0;
    for (int i = 0; i < point; ++i)
    {
        //sum += set[i];
        sum += list[i][position];
    }
    return sum;
}

template <typename T>
void Ann<T> :: train(T ** set , int number , int times){
    list = new double*[number];
    origin = new double *[number];
    for (int i = 0; i < number; ++i)
    {
        list[i] = new double[argc_output];
        origin[i] = new double[argc_input];
    }
    record = new double**[number];
    for (int i = 0; i < number; ++i)
    {
        record[i] = new  double * [argc_level];
        for (int j = 0; j < argc_level; ++j)
        {
            record[i][j] = new double[info[j]];
        }
    }
    int max = argc_input > argc_output ? argc_input : argc_output;
    for (int i = 0; i < argc_level; ++i)
    {
        if(info[i] > max) max = info[i];
    }

    if(max < number){
        max = number;
    }
    // cout << "Check for max " << max << endl;

    medium = new double*[max];

    for (int i = 0; i < max; ++i)
    {
        medium[i] = new double[max];
    }
    for (int i = 0; i < times; ++i)
    {
        point = 0;
        for (int j = 0; j < number; ++j)
        {
            set_input(set[j]);
            calculator();
            copy_level(j);
            copy_input(j);
            ++ point;
        }
        softmax(set);
    }
    for (int i = 0; i < number; ++i)
    {
        delete[] list[i];
        delete[] origin[i];
    }
    delete[] list;
    delete[] origin;
    for (int i = 0; i < max; ++i)
    {
        delete[] medium[i];
    }
    delete[] medium;
    for (int i = 0; i < number; ++i)
    {
        for (int j = 0; j < argc_level; ++j)
        {
            delete[] record[i][j];
        }
        delete[] record[i];
    }
    delete[] record;
}

template <typename T>
void Ann<T> :: softmax(T ** set){
    double * sum = new double[argc_output];
    for (int i = 0; i < point; ++i)
    {
        for (int j = 0; j < argc_output; ++j)
        {
            list[i][j] = exp(list[i][j]);
            sum[i] += list[i][j];
        }
    }
    double loss = 0;
    for(int i = 0 ; i < point; ++i){
        for (int j = 0; j < argc_output; ++j)
        {
            list[i][j] /= sum[i];
        }
    }
    for (int i = 0; i < point; ++i)
    {
        loss += -log(list[i][int(round(set[i][argc_input]))]);
    }
    loss /= point;
    double regular = get_regular();
    regular *= 1/2 * lambda;
    loss += regular;
    cout << "loss for ; " << loss << endl;
    for (int i = 0; i < point; ++i)
    {
        for (int j = 0; j < argc_output; ++j)
        {
            if(j == int(round(set[i][argc_input]))){
                list[i][j] -= 1;
            }
            list[i][j] /= point;
        }
    }
    compute_gradient();
    //update_weight();
    /*
      for (int i = 0; i < list.size(); ++i)
      {
      list[i][int(round(set[i][argc_input]))] -= 1;
      for (int j = 0; j < argc_output; ++j)
      {
      list[i][j] /= list.size();
      }
      }

      // this step is to update the weight value
      */
    //list.clear();
    point = 0;
    delete[] sum;
}

template <typename T>
void Ann<T> :: pre_process(){

}

template <typename T>
int Ann<T> :: get_argc_input(){
    return argc_input;
}

template <typename T>
bool Ann<T> :: adjust_output(double * target){
    for (int j = 0; j < argc_output; ++j)
    {
        for (int i = 0; i < info[argc_level-1]; ++i)
        {
            double y = -rate * (target[j] - output[j]) * output[j]*(1 - output[j]) * level[argc_level-1][i];
            weight[argc_level][i][j] += y;
        }
    }
    for (int i = 0; i < info[argc_level-1]; ++i)
    {
        calculator_err(i);
    }
    adjust_hidden();
    return true;
}

template <typename T>
double Ann<T> :: calculator_err(int input){
    double sum = 0;
    for (int i = 0; i < argc_output; ++i)
    {
        sum += weight[argc_level][input][i] * weight[argc_level][input][i];
    }
    sum *= level[argc_level-1][input];
    err[input] = sum;
    return sum;
}

template <typename T>
double Ann<T> :: get_err(int i){
    return err[i];
}

template <typename T>
bool Ann<T> :: adjust_hidden(){
    for (int i = argc_level-1; i >= 0; --i)
    {
        if(i == 0){
            for (int j = 0 ; j < info[0]; ++j)
            {
                for (int k = 0; k < argc_input; ++k)
                {
                    double x = -rate * input[k] * level[i][j] * (1-level[i][j])  * sum(i,k,j);
                    weight[0][k][j] += x;
                }
            }
        }else if(i != argc_level - 1){
            for (int j = 0 ; j < info[i]; ++j)
            {
                for (int k = 0; k < info[i-1]; ++k)
                {
                    double x = -rate * level[i-1][k] * level[i][j] * (1-level[i][j]) * sum(i,k,j);
                    weight[i][k][j] += x;
                }
            }
        }else{
            for (int j = 0 ; j < argc_output; ++j)
            {
                for (int k = 0; k < info[i-1]; ++k)
                {
                    double x = -rate * level[argc_level-1][k] * output[j] * (1-output[j]) * sum(i,k,j);
                    weight[i][k][j] += x;
                }
            }
        }
    }
    return true;
}

template <typename T>
double Ann<T> :: sum(int position , int input , int output){
    double sum = 0;
    if(position == argc_level - 1){
        if(argc_level > 1){
            /*
              for (int i = 0; i < argc_output; ++i)
              {
              sum += -weight[position+1][output][i] * (target[i]- this->output[i]) * this -> output[i] * (1-this->output[i]);
              }
            */
            sum = -rate * level[position-1][input] * get_err(output);
            double Oi = level[position][output];
            sum *= (Oi * (1-Oi));
            return sum;
        }else {
            /*
              for (int i = 0; i < argc_output; ++i)
              {
              sum += -weight[position+1][output][i] * (target[i]- this->output[i]) * this -> output[i] * (1-this->output[i]);
              }
            */
            sum = -rate * this -> input[input] * get_err(output);
            double Oi = level[position][output];
            sum *= (Oi * (1-Oi));
        }
        return sum;
    }else if(position != 0){
        for (int i = 0; i < info[position+1]; ++i)
        {
            sum += -weight[position+1][output][i] * this -> sum(position+1,output,i);
        }
        sum *= (level[position][output]*(1-level[position][output]));
        return sum;
    }else {
        if(argc_level > 1){
            for (int i = 0; i < info[1]; ++i)
            {
                sum += -weight[position+1][output][i] * this -> sum(position+1,output,i);
            }
            double Oi = level[position][output];
            sum *= (Oi * (1-Oi));
            return sum;
        }else{
            for (int i = 0; i < info[1]; ++i)
            {
                sum += -weight[position+1][output][i] * this -> sum(position+1,output,i);
            }
            double Oi = level[position][output];
            sum *= (Oi * (1-Oi));
            return sum;
        }
    }
    return sum;
}

template <typename T>
Ann<T> :: Ann(int input , int argc , int * detailed , int output , double rate , double lambda){
    this -> rate = rate;
    this -> lambda = lambda;
    init(input , argc , detailed , output);
    //calculator();
    //print_input();
    //print_output();
}

/*

template <typename T>
int Ann<T> :: train(double * input , double * output){
    cout << std :: fixed << std :: setprecision(LIMIT);
    for (int i = 0; i < argc_input; ++i)
    {
        this -> input[i] = input[i];
    }
    calculator();
    //print_output();
    double sum = 0;
    for (int i = 0; i < argc_output; ++i)
    {
        target[i] = output[i];
        double temp = (target[i] - this -> output[i]);
        sum += temp * temp;
    }

    int max = 0;
    for (int i = 1; i < argc_output; ++i)
    {
        if(this -> output[i] > this -> output[max]) max = i;
    }

    //cout << "Max for : " << max << endl;
    return max;
}

*/

template <typename T>
void Ann<T> :: calculator(){
    cout << std :: fixed << std :: setprecision(LIMIT);
    //cout << "level -> : " << endl;
    for (int i = 0; i < info[0]; ++i)
    {
        double sum = 0;
        for (int j = 0 ; j < argc_input ; ++j)
        {
            sum += input[j] * weight[0][j][i];
        }
        level[0][i] = sigmod(sum + offset[0][i]);
        //cout << level[0][i] << "\t" ;
    }
    //cout << endl;
    for (int i = 1; i < argc_level; ++i)
    {
        for (int j = 0; j < info[i]; ++j)
        {
            double sum = 0;
            for (int k = 0 ; k < info[i-1]; ++k)
            {
                sum += level[i-1][k] * weight[i][k][j];
            }
            level[i][j] = sigmod(sum + offset[i][j]);
            //cout << level[i][j] << "\t";
        }
        //cout << endl;
    }
    for (int i = 0; i < argc_output; ++i)
    {
        double sum = 0;
        for (int j = 0; j < info[argc_level-1]; ++j)
        {
            sum += level[argc_level-1][j] * weight[argc_level][j][i];
        }
        output[i] = (sum + offset[argc_level][i]);
        //cout << output[i] << "\t";
    }
    //cout << endl;
    //cout << "level done -< ." << endl;

    for (int i = 0; i < argc_output; ++i)
    {
        list[point][i] = output[i];
    }

    //list.push_back(output);
}

template <typename T>
bool Ann<T> :: init(int input , int argc , int * detailed , int output){
    cout << std :: fixed << std :: setprecision(LIMIT);
    argc_input = input;
    argc_level = argc;
    argc_output = output;
    level = new  double * [argc];
    for (int i = 0; i < argc; ++i)
    {
        level[i] = new double[detailed[i]];
    }
    info = new int [argc];
    offset = new double*[argc+1];
    for (int i = 0; i < argc; ++i)
    {
        offset[i] = new double[detailed[i]];
        for (int j = 0; j < detailed[i]; ++j)
        {
            offset[i][j] = rand() % 10 > 5 ? rand()/double(RAND_MAX) : -rand()/double(RAND_MAX);
        }
    }
    offset[argc] = new double[output];
    for (int i = 0; i < output; ++i)
    {
        offset[argc][i] = rand() % 10 > 5 ? rand()/double(RAND_MAX) : -rand()/double(RAND_MAX);
    }
    copy(info , detailed , argc);
    //init_level();
    this -> target = new double[output];
    this -> input = new double[input];
    this -> output = new double[output];
    weight = new double **[argc_level+1];
    best_weight = new double **[argc_level+1];
    srand((unsigned)time(NULL));
    for (int i = 0; i < argc_level ; ++i)
    {
        if(i == 0){
            weight[0] = new double *[argc_input];
            best_weight[0] = new double *[argc_input];
            for (int j = 0; j < argc_input; ++j)
            {
                weight[0][j] = new double[info[0]];
                best_weight[0][j] = new double[info[0]];
                for (int k = 0 ; k < info[0]; ++k)
                {
                    weight[0][j][k] = rand() % 10 > 5 ? (double)(rand()%100) / 200 : -(double)(rand()%100)/200;
                }
            }
        }else{
            weight[i] = new double *[info[i-1]];
            best_weight[i] = new double *[info[i-1]];
            for (int j = 0; j < info[i-1]; ++j)
            {
                weight[i][j] = new double[info[i]];
                best_weight[i][j] = new double[info[i]];
                for (int k = 0 ; k < info[i]; ++k)
                {
                    weight[i][j][k] = rand() % 10 > 5 ? (double)(rand()%100) / 200 : -(double)(rand()%100)/200;
                }
            }
        }
    }
    weight[argc_level] = new double *[info[argc_level-1]];
    best_weight[argc_level] = new double *[info[argc_level-1]];
    for (int i = 0; i < info[argc_level - 1]; ++i)
    {
        weight[argc_level][i] = new double[argc_output];
        best_weight[argc_level][i] = new double[argc_output];
        for (int j = 0 ; j < argc_output; ++j)
        {
            weight[argc_level][i][j] = rand() % 10 > 5 ? (double)(rand()%100) / 200 : -(double)(rand()%100)/200;
        }
    }
    err = new double[info[argc_level-1]];
    return true;
}

template <typename T>
void Ann<T> :: init_level(){
    cout << std :: fixed << std :: setprecision(LIMIT);
    srand((unsigned)time(NULL));
    for (int i = 0; i < argc_level; ++i)
    {
        for (int j = 0; j < info[i]; ++j)
        {
            level[i][j] = rand() % 10 > 5 ? (double)(rand()%100) / 200 : -(double) (rand()%100) / 200;
        }
    }
}

template <typename T>
double Ann<T> :: get_random(){
    cout << std :: fixed << std :: setprecision(LIMIT);
    srand((unsigned)time(NULL));
    return rand() % 10 > 5 ? (double)(rand()%100) / 200 : -(double)(rand()%100)/200;
}

template <typename T>
Ann<T> :: ~Ann(){
    // and why I use the index .
    int index[argc_level + 1];
    index[0] = argc_input;
    for (int i = 1; i < argc_level + 1; ++i)
    {
        index[i] = info[i-1];
    }
    free(argc_level + 1 , index , weight);
    free(argc_level + 1 , index , best_weight);
    free(argc_level , level);
    free(input);
    free(output);
    free(info);
    free(target);
    free(err);
    //free(offset , argc_level);
    for (int i = 0; i < argc_level; ++i)
    {
        delete[] offset[i];
    }
    delete[] offset;
}

template <typename T>
void Ann<T> :: free(double * array){
    delete[] array;
}

template <typename T>
void Ann<T> :: free(int * array){
    delete[] array;
}

template <typename T>
void Ann<T> :: free(int argc , double ** matrix){
    for (int i = 0; i < argc; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

template <typename T>
void Ann<T> :: free(int argc , int * argv , double *** matrix){
    for (int i = 0; i < argc_level + 1; ++i)
    {
        int limit;
        if(i == 0) limit = argc_input;
        else limit = info[i-1];
        for (int j = 0 ; j < limit; ++j)
        {
            delete[] matrix[i][j];
        }
        delete[] matrix[i];
    }
    delete[] matrix;
}

template <typename T>
void Ann<T> :: load(string filename){
    std :: ifstream in;
    in.open(filename.c_str());
    if(in.is_open()){
        in >> std :: fixed >> std :: setprecision(LIMIT);
        double var;
        for (int i = 0; i < argc_level ; ++i)
        {
            if(i == 0){
                for (int j = 0; j < argc_input; ++j)
                {
                    for (int k = 0 ; k < info[0]; ++k)
                    {
                        in >> var;
                        best_weight[0][j][k] = weight[0][j][k] = var;
                    }
                }
            }else{
                for (int j = 0; j < info[i-1]; ++j)
                {
                    for (int k = 0 ; k < info[i]; ++k)
                    {
                        in >> var;
                        best_weight[i][j][k] = weight[i][j][k] = var;
                    }
                }
            }
        }
        for (int i = 0; i < info[argc_level - 1]; ++i)
        {
            for (int j = 0 ; j < argc_output; ++j)
            {
                in >> var;
                best_weight[argc_level][i][j] = weight[argc_level][i][j] = var;
            }
        }
    }
}

template <typename T>
void Ann<T> :: save(){
    cout << std :: fixed << std :: setprecision(LIMIT);
    /*
      cout << "saving the weight -> : " << endl;
      calculator();
      print_weight();
      cout << "saving done . " << endl;
    */
    for (int i = 0; i < argc_level ; ++i)
    {
        if(i == 0){
            for (int j = 0; j < argc_input; ++j)
            {
                for (int k = 0 ; k < info[0]; ++k)
                {
                    best_weight[0][j][k] = weight[0][j][k];
                }
            }
        }else{
            for (int j = 0; j < info[i-1]; ++j)
            {
                for (int k = 0 ; k < info[i]; ++k)
                {
                    best_weight[i][j][k] = weight[i][j][k];
                }
            }
        }
    }
    for (int i = 0; i < info[argc_level-1]; ++i)
    {
        for (int j = 0 ; j < argc_output; ++j)
        {
            best_weight[argc_level][i][j] = weight[argc_level][i][j];
        }
    }
}

template <typename T>
double Ann<T> :: sigmod(double value)
{
    //return (1/(1+exp(-value)));
    return log(1+exp(value));
}

template <typename T>
void Ann<T> :: copy(int * info , int * detailed , int argc){
    for (int i = 0; i < argc; ++i)
    {
        info[i] = detailed[i];
    }
}

template <typename T>
void Ann<T> :: print_input(){
    cout << std :: fixed << std :: setprecision(LIMIT);
    cout << "print input -> : " << endl;
    for (int i = 0; i < argc_input; ++i)
    {
        cout << input[i] << "\t";
    }
    cout << endl ;
    cout << "print input done -< . " << endl;
}

template <typename T>
void Ann<T> :: print_output(){
    cout << std :: fixed << std :: setprecision(LIMIT);
    cout << "print output -> : " << endl;
    for (int i = 0; i < argc_output; ++i)
    {
        cout << output[i] << "\t";
    }
    cout << endl ;
    cout << "print output done -< . " << endl;
}

template <typename T>
void Ann<T> :: print_level(){
    cout << std :: fixed << std :: setprecision(LIMIT);
    cout << "print level -> : " << endl;
    for (int i = 0; i < argc_level; ++i)
    {
        for (int j = 0 ; j < info[i]; ++j)
        {
            cout << level[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "print level done -< . " << endl;
}

template <typename T>
void Ann<T> :: print_weight(){
    cout << std :: fixed << std :: setprecision(LIMIT);
    cout << "print weight -> : " << endl;
    for (int i = 0; i < argc_level ; ++i)
    {
        if(i == 0){
            for (int j = 0; j < argc_input; ++j)
            {
                for (int k = 0 ; k < info[0]; ++k)
                {
                    cout << weight[0][j][k] << "\t";
                }
                cout << endl;
            }
        }else{
            for (int j = 0; j < info[i-1]; ++j)
            {
                for (int k = 0 ; k < info[i]; ++k)
                {
                    cout << weight[i][j][k] << "\t";
                }
                cout << endl;
            }
        }
    }
    for (int i = 0; i < info[argc_level-1]; ++i)
    {
        for (int j = 0 ; j < argc_output; ++j)
        {
            cout << weight[argc_level][i][j] << "\t";
        }
        cout << endl;
    }
    cout << "print weight done -< . " << endl;
}

template <typename T>
void Ann<T> :: set_input(double * argc){
    for (int i = 0; i < argc_input; ++i)
    {
        input[i] = argc[i];
    }
}

template <typename T>
bool Ann<T> :: get_result(double goal){
    int max = 0;
    for(int i = 0; i < argc_output; ++i)
    {
        if(output[i] > output[max]) max = i;
    }
    return max == round(goal);
}

template <typename T>
int Ann<T> :: get_argc_output(){
    return argc_output;
}

template <typename T>
void Ann<T> :: write_file(string filename){
    std::ofstream out;
    out.open(filename.c_str());
    if(out.is_open()){
        out << std :: fixed << std :: setprecision(LIMIT);
        for (int i = 0; i < argc_level ; ++i)
        {
            if(i == 0){
                for (int j = 0; j < argc_input; ++j)
                {
                    for (int k = 0 ; k < info[0]; ++k)
                    {
                        out << best_weight[0][j][k] << "\t";
                    }
                    out << "\n" ;
                }
            }else{
                for (int j = 0; j < info[i-1]; ++j)
                {
                    for (int k = 0 ; k < info[i]; ++k)
                    {
                        out << best_weight[i][j][k] << "\t";
                    }
                    out << "\n";
                }
            }
        }
        for (int i = 0; i < info[argc_level-1]; ++i)
        {
            for (int j = 0 ; j < argc_output; ++j)
            {
                out << best_weight[argc_level][i][j] << "\t";
            }
            out << "\n";
        }
        out.close();
    }else {
        //throw "Resources busy . " ;
        cout << "Error for the resources busy ." << endl;
        exit(1);
    }
}
