#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include <pthread.h>
using std :: cout;
using std :: endl;
using std :: cin;
using std :: string;
using std :: stringstream;
int const static LIMIT = 19;
template <typename T>
class Ann
{
public:
    Ann(int input , int argc , int * detailed , int output);
    virtual ~Ann();
    void load(string filename);
    void save();
    void print_weight();
    void train(T ** set , int number , int times , double rate , double lambda , double limit , double probality);
    bool adjust_output(double * target);
    bool adjust_hidden();
    void calculator();
    int get_argc_input();
    int get_argc_output();
    void set_input(double * argc);
    bool get_result(int goal);
    void write_file(string filename);
private:
    double * input , ** level , * output , *** weight , ***best_weight, * target , * err , ** offset , ** best_offset;
    T ** set , ** temp;
    double rate , lambda , limit , probality;
    int argc_input , argc_level , argc_output , * info;
    double ** list , ** medium , ** origin;
    double *** record;
    int point , max , temp_point;
    stringstream stream;
    void init(int input , int argc , int * detailed , int end);
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
    double get_err(int i);
    void pre_process(T ** set , int value);
    double offset_sum(int target);
    double get_regular();
    double softmax(T ** set , int const point , int const max , int const argc_output , int const value , bool flag = false);
    void compute_gradient(int point , int max);
    void copy_level(int i);
    void copy_input(int i);
    void copy_list(int i);
    double gaussrand();
    void test();
    bool check(T ** set , int train , int confirm);
    int best_train , best_confirm;
    string itos(int data);
    void deal_for_svm(T ** set , int value);
};
template <typename T>
string Ann<T> ::  itos(int data){
    stream << data;
    string result = stream.str();
    stream.clear();
    stream.str("");
    return result;
}
template <typename T>
bool Ann<T> :: check(T ** set ,int train , int size){
    int err_train = 0 , err_confirm = 0;
    for (int i = 0; i < train; ++i)
    {
        set_input(set[i]);
        calculator();
        if(!get_result(set[i][argc_input])){
            err_train ++;
        }
    }
    for (int i = 0; i < temp_point; ++i)
    {
        set_input(temp[i]);
        calculator();
        if(!get_result(temp[i][argc_input])){
            err_confirm ++;
        }
    }
    cout << "Error in train for : " << err_train << endl;
    cout << "Number for : " << train << endl;
    cout << "Rate for : " << 1 - (double)err_train / train << endl;
    cout << "Error in check for : " << err_confirm << endl;
    cout << "Number for : " << temp_point << endl;
    cout << "Rate for : " << 1 - (double)err_confirm / temp_point << endl;
    if(err_train * 0.2 + err_confirm * 0.8  < best_train * 0.2 + best_confirm * 0.8){
        best_train = err_train;
        best_confirm = err_confirm;
        save();
        return true;
    }
    return false;
}
template <typename T>
double Ann<T> :: gaussrand(){
    {
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
        } else{
            X = V2 * sqrt(-2 * log(S) / S);
        }
        phase = 1 - phase;
        return X;
    }
}
template <typename T>
void Ann<T> :: test(){
    for (int i = 0; i < point; ++i)
    {
        for (int j = 0; j < argc_input; ++j)
        {
            if(origin[i][j] != origin[i][j]){
                cout << "origin failed ." << endl;
                exit(1);
            }
        }
        for (int j = 0; j < argc_output; ++j)
        {
            if(list[i][j] != list[i][j]){
                cout << "list failed ." << endl;
                exit(1);
            }
        }
        for (int j = 0; j < argc_level; ++j)
        {
            for (int k = 0; k < info[j]; ++k)
            {
                if(record[i][j][k] != record[i][j][k]){
                    cout << "record failed " << endl;
                    exit(1);
                }
            }
        }
    }
}
template <typename T>
void Ann<T> :: copy_level(int position){
    for (int i = 0; i < argc_level; ++i)
    {
        for (int j = 0 ; j < info[i]; ++j)
        {
            record[position][i][j] = level[i][j];
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
void Ann<T> :: copy_list(int position){
    for (int i = 0; i < argc_output; ++i)
    {
        list[position][i] = output[i];
    }
}
template <typename T>
void Ann<T> :: compute_gradient(int point , int max){
    double list_back[point][max];
    for (int i = argc_level - 1 ; i >= 0; --i)
    {
        if(i == argc_level - 1){
            {
                int m = info[i] , n = point , p = argc_output;
                for (int j = 0; j < m; ++j)
                {
                    for (int k = 0; k < p; ++k)
                    {
                        double sum = 0;
                        for (int h = 0; h < n; ++h)
                        {
                            sum += record[h][i][j] * list[h][k];
                        }
                        medium[j][k] = sum;
                    }
                }
            }
            for (int j = 0; j < argc_output; ++j)
            {
                if(get_random() > probality){
                    offset[i+1][j] += -rate * offset_sum(j);
                }
            }
            {
                int m = point , n = argc_output , p = info[i];
                for (int j = 0; j < m; ++j)
                {
                    for (int k = 0; k < p; ++k)
                    {
                        double sum = 0;
                        for (int h = 0; h < n; ++h)
                        {
                            sum += list[j][h] * weight[i+1][k][h];
                        }
                        list_back[j][k] = record[j][i][k] <= 0 ? 0 : sum;
                    }
                }
                for (int i = 0; i < m; ++i)
                {
                    for (int j = 0; j < p; ++j)
                    {
                        list[i][j] = list_back[i][j];
                    }
                }
            }
            for (int j = 0; j < info[argc_level-1]; ++j)
            {
                for (int k = 0; k < argc_output; ++k)
                {
                    if(get_random() > probality){
                        weight[i+1][j][k] = weight[i+1][j][k] - (rate * (medium[j][k] + lambda * weight[i+1][j][k]));
                    }
                }
            }
        }else{
            {
                int m = info[i] , n = point , p = info[i+1];
                for (int j = 0; j < m; ++j)
                {
                    for (int k = 0; k < p; ++k)
                    {
                        double sum = 0;
                        for (int h = 0; h < n; ++h)
                        {
                            sum += record[h][i][j] * list[h][k];
                        }
                        medium[j][k] = sum;
                    }
                }
            }
            for (int j = 0; j < info[i]; ++j)
            {
                if(get_random() > probality){
                    offset[i+1][j] += -rate * offset_sum(j);
                }
            }
            {
                int m = point , n = info[i+1] , p = info[i];
                for (int j = 0; j < m; ++j)
                {
                    for (int k = 0; k < p; ++k)
                    {
                        double sum = 0;
                        for (int h = 0; h < n; ++h)
                        {
                            sum += list[j][h] * weight[i+1][k][h];
                        }
                        list_back[j][k] = record[j][i][k] <= 0 ? 0 : sum;
                    }
                }
                for (int i = 0; i < m; ++i)
                {
                    for (int j = 0; j < p; ++j)
                    {
                        list[i][j] = list_back[i][j];
                    }
                }
            }
            for (int j = 0; j < info[i]; ++j)
            {
                for (int k = 0; k < info[i+1]; ++k)
                {
                    if(get_random() > probality){
                        weight[i+1][j][k] = weight[i+1][j][k] + (-rate * (medium[j][k] + lambda * weight[i+1][j][k]));
                    }
                }
            }
        }
    }
    {
        for (int i = 0; i < argc_input; ++i)
        {
            for (int j = 0; j < info[0]; ++j)
            {
                double sum = 0;
                for (int k = 0; k < point; ++k)
                {
                    sum += origin[k][i] * list[k][j];
                }
                medium[i][j] = sum;
            }
        }
    }
    for (int j = 0; j < info[0]; ++j)
    {
        if(get_random() > probality){
            offset[0][j] += -rate * offset_sum(j);
        }
    }
    for (int j = 0; j < argc_input; ++j)
    {
        for (int k = 0; k < info[0]; ++k)
        {
            if(get_random() > probality){
                weight[0][j][k] = weight[0][j][k] + (-rate * (medium[j][k] + lambda * weight[0][j][k]));
            }
        }
    }
}
template <typename T>
double Ann<T> :: get_regular(){
    double regular = 0;
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
        sum += list[i][position];
    }
    return sum;
}
template <typename T>
void Ann<T> :: deal_for_svm(T ** set , int value){
    string filename = "heart_scale";
    std::ofstream out;
    out.open(filename.c_str());
    if(out.is_open()){
        for (int i = 0; i < value; ++i)
        {
            out << set[i][argc_input] << " " ;
            for (int j = 0; j < argc_input; ++j)
            {
                out << j+1 << ":" <<set[i][j] << " ";
            }
            out << endl;
        }
        out.close();
    }else {
        cout << "Error for the resources busy ." << endl;
        exit(1);
    }
}
template <typename T>
void Ann<T> :: train(T ** const set , int const value , int const times , double rate , double lambda , double limit , double probality){
    pre_process(set , value);
    this -> temp = set;
    this -> probality = probality;
    this -> limit = limit;
    this -> rate = rate;
    this -> lambda = lambda;
    int number = value;
    best_train = number;
    best_confirm = value - number;
    this -> set = set + (value - number);
    this -> temp_point = value - number;
    origin = new double *[number];
    for (int i = 0; i < number; ++i)
    {
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
    if(max < number) max = number;
    this -> max = max;
    medium = new double*[max];
    for (int i = 0; i < max; ++i)
    {
        medium[i] = new double[max];
    }
    list = new double *[number];
    for (int i = 0; i < number; ++i)
    {
        list[i] = new double[max];
    }
    double loss = value;
    double temp;
    string filename = "";
    for (int i = 0; i < times || loss > limit; ++i)
    {
        point = 0;
        for (int j = 0; j < number; ++j)
        {
            set_input(this -> set[j]);
            calculator();
            copy_input(j);
            copy_level(j);
            copy_list(j);
            ++ point;
        }
        if(i % 1000 == 0){
            cout << "----------------------------------->" << endl;
            cout << "Ietration : " << i << endl;
            temp = softmax(this -> set , point , max , argc_output , value, true);
            cout << "The distance : " << temp - loss << endl;
            loss = temp;
        }else{
            softmax(this -> set , point , max , argc_output , value , false);
        }
    }
    write_file("final.conf");
    for (int i = 0; i < number; ++i)
    {
        delete list[i];
        delete origin[i];
    }
    delete list;
    delete origin;
    for (int i = 0; i < max; ++i)
    {
        delete medium[i];
    }
    delete medium;
    for (int i = 0; i < number; ++i)
    {
        for (int j = 0; j < argc_level; ++j)
        {
            delete record[i][j];
        }
        delete record[i];
    }
    delete record;
}
template <typename T>
double Ann<T> :: softmax(T ** set , int const point , int const  max , int const  argc_output , int value, bool flag){
    double sum[point];
    for (int i = 0 ; i < point; ++i)
    {
        sum[i] = 0;
        for (int j = 0; j < argc_output; ++j)
        {
            list[i][j] = exp(list[i][j]);
            sum[i] += list[i][j];
        }
    }
    for (int i = 0; i < point; ++i)
    {
        for (int j = 0; j < argc_output; ++j)
        {
            list[i][j] /= sum[i];
        }
    }
    double loss = 0;
    for (int i = 0; i < point; ++i)
    {
        int temp = round(set[i][argc_input]);
        loss += -log(list[i][temp]);
        list[i][temp] -= 1;
        if(loss != loss){
            cout << "loss for : " << loss << endl;
            cout << "point : " << point << endl;
            cout << "max : " << max << endl;
            cout << "argc_output : " << argc_output << endl;
            cout << "i of point : " << i << endl;
            cout << "Info : " << info << endl;
            test();
        }
    }
    loss = loss / point;
    double regular = get_regular();
    regular *= 0.5 * lambda;
    if(flag){
        cout << "Data loss : " << loss << endl;
        cout << "Reg loss : " << regular << endl;
        cout << "Loss : " << loss + regular<< endl;
        cout << "Lambda : " << lambda << endl;
        string filename = "";
        int number = point;
        if(check(set , number , number)){
            filename = itos(best_train) + "-" + itos(number) + "-" + itos(best_confirm) + "-" + itos(temp_point) + ".conf";
            cout << "Write the weight in : " << filename << endl;
            write_file(filename);
        }
    }
    for (int i = 0; i < point; ++i)
    {
        for (int j = 0; j < argc_output; ++j)
        {
            list[i][j] = list[i][j] / point;
        }
    }
    compute_gradient(point , max);
    return loss;
}
template <typename T>
void Ann<T> :: pre_process(T ** set , int value){
    double sum = 0 ;
    for (int i = 0; i < value; ++i)
    {
        sum = 0;
        for (int j = 0; j < argc_input; ++j)
        {
            set[i][j] *= 100;
        }
    }
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
    adjust_hidden();
    return true;
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
            sum = -rate * level[position-1][input] * get_err(output);
            double Oi = level[position][output];
            sum *= (Oi * (1-Oi));
            return sum;
        }else {
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
Ann<T> :: Ann(int input , int argc , int * detailed , int output ){
    init(input , argc , detailed , output);
}
template <typename T>
void Ann<T> :: calculator(){
    for (int i = 0; i < info[0]; ++i)
    {
        if(get_random() > probality){
            double sum = 0;
            for (int j = 0 ; j < argc_input ; ++j)
            {
                sum += input[j] * weight[0][j][i];
            }
            level[0][i] = sigmod(sum + offset[0][i]);
        }
    }
    for (int i = 1; i < argc_level; ++i)
    {
        for (int j = 0; j < info[i]; ++j)
        {
            if(get_random() > probality){
                double sum = 0;
                for (int k = 0 ; k < info[i-1]; ++k)
                {
                    sum += level[i-1][k] * weight[i][k][j];
                }
                level[i][j] = sigmod(sum + offset[i][j]);
            }
        }
    }
    for (int i = 0; i < argc_output; ++i)
    {
        double sum = 0;
        for (int j = 0; j < info[argc_level-1]; ++j)
        {
            sum += level[argc_level-1][j] * weight[argc_level][j][i];
        }
        output[i] = (sum + offset[argc_level][i]);
    }
}
template <typename T>
void Ann<T> :: init(int input , int argc , int * detailed , int output){
    argc_input = input;
    argc_level = argc;
    argc_output = output;
    level = new  double * [argc];
    for (int i = 0; i < argc; ++i)
    {
        level[i] = new double[detailed[i]]();
    }
    info = new int [argc];
    offset = new double*[argc+1];
    best_offset = new double*[argc+1];
    for (int i = 0; i < argc; ++i)
    {
        offset[i] = new double[detailed[i]]();
        best_offset[i] = new double[detailed[i]]();
    }
    offset[argc] = new double[output]();
    best_offset[argc] = new double[output]();
    copy(info , detailed , argc);
    this -> target = new double[output]();
    this -> input = new double[input]();
    this -> output = new double[output]();
    weight = new double **[argc_level+1]();
    best_weight = new double **[argc_level+1]();
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
                    weight[0][j][k] = gaussrand() * 0.01;
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
                    weight[i][j][k] = gaussrand() * 0.01;
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
            weight[argc_level][i][j] = gaussrand() * 0.01;
        }
    }
}
template <typename T>
void Ann<T> :: init_level(){
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
    return double(rand()) / RAND_MAX;
}
template <typename T>
Ann<T> :: ~Ann(){
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
    for (int i = 0; i < argc_level; ++i)
    {
        delete offset[i];
        delete best_offset[i];
    }
    delete best_offset;
    delete offset;
}
template <typename T>
void Ann<T> :: free(double * array){
    delete array;
}
template <typename T>
void Ann<T> :: free(int * array){
    delete array;
}
template <typename T>
void Ann<T> :: free(int argc , double ** matrix){
    for (int i = 0; i < argc; ++i)
    {
        delete matrix[i];
    }
    delete matrix;
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
            delete matrix[i][j];
        }
        delete matrix[i];
    }
    delete matrix;
}
template <typename T>
void Ann<T> :: load(string filename){
    std :: ifstream in;
    in.open(filename.c_str());
    if(in.is_open()){
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
    for (int i = 0; i < argc_level; ++i)
    {
        for (int j = 0; j < info[i]; ++j)
        {
            best_offset[i][j] = offset[i][j];
        }
    }
    for (int i = 0; i < argc_output; ++i)
    {
        best_offset[argc_level][i] = offset[argc_level][i];
    }
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
    return value <= 0 ? 0 : value;
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
bool Ann<T> :: get_result(int goal){
    int max = 0;
    for(int i = 0; i < argc_output; ++i)
    {
        if(output[i] > output[max]) max = i;
    }
    return max == goal;
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
        out << argc_input << "\t";
        out << argc_level << "\t";
        out << argc_output << "\t";
        out << "\n";
        for (int i = 0; i < argc_level; ++i)
        {
            out << info[i] << "\t";
        }
        out << "\n";
        for (int i = 0; i < argc_level; ++i)
        {
            for (int j = 0; j < info[i]; ++j)
            {
                out << best_offset[i][j] << "\t";
            }
            out << "\n";
        }
        for (int i = 0; i < argc_output; ++i)
        {
            out << best_offset[argc_level][i] << "\t";
        }
        out << "\n";
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
        out << "\n";
        out.close();
    }else {
        cout << "Error for the resources busy ." << endl;
    }
}
