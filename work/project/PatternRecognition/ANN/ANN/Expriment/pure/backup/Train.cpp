#include "Ann.cpp"

double const static THRESHOLD = 0.8;
bool start = false;

int temp_err_train = 0, temp_err_check = 0, best_err_train = 1000, best_err_check = 1000;
template <typename T>
bool check(Ann<T> *& ann , double ** set , int number , int size){
    int limit = number * THRESHOLD;
    temp_err_train = temp_err_check = 0;
    for (int i = 0; i < limit; ++i)
    {
        ann -> set_input(set[i]);
        ann -> calculator();
        if(!ann -> get_result(set[i][size-1])){
            temp_err_train++;
        }
    }
    for (int i = limit; i < number; ++i)
    {
        ann -> set_input(set[i]);
        ann -> calculator();
        if(!ann -> get_result(set[i][size-1])){
            temp_err_check++;
        }
    }
    cout << "Get the temp_err_train for : " << temp_err_train << endl;
    cout << "Get the temp_err_check for : " << temp_err_check << endl;
    cout << "Get the best_err_train for : " << best_err_train << endl;
    cout << "Get the best_err_check for : " << best_err_check << endl;
    if (temp_err_train * THRESHOLD + temp_err_check * (1-THRESHOLD) < best_err_train * THRESHOLD + best_err_check * (1-THRESHOLD)){
        best_err_train = temp_err_train;
        best_err_check = temp_err_check;
        return true;
    }
    return false;
}
int getNumber(string filename , int input ){
    std :: ifstream in;
    in.open(filename.c_str());
    long count = 0;
    double var;
    double temp = 1 ;
    while(!in.eof()){
        in >> var;
        temp = var;
        count ++;
    }
    in.close();
    count -= 1;
    if(count % (input + 1) == 0) {
        cout << "Sample confirm ." << endl;
    }else{
        cout << "Sample is broken ! " << endl;
        exit(0);
    }
    return count;
}
void getData(double ** & set , int & number , int & size , string filename , int input){
    double var;
    std :: ifstream in;
    in.open(filename.c_str());
    if(!in.is_open()){
        cout << "Error for file busy . " << endl;
        throw "Resources busy . ";
        return;
    }
    int count = getNumber(filename , input);
    number = count / (input+1);
    size = input+1;
    set = new double*[count];
    for (int i = 0; i < count; ++i)
    {
        set[i] = new double[size];
    }
    for(int k = 0 ; k < count ;){
        for (int i = 0; i < number; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                in >> var;
                if(j == size - 1){
                    set[i][j] = var;
                }else{
                    set[i][j] = var;
                }
                ++k;
            }
            /*
            int limit = input;
            for (int j = 0; j < limit; ++j)
            {
                set[i][j] = set[i][100 - limit / 2 + j];
            }
            set[i][limit] = set[i][size-1];
            */
        }
    }
}

int main(int argc , char ** argv){
    int array[] = {64 , 32 };
    int input = 128;
    Ann<double> * ann = new Ann<double>(input , 2 , array , 2);
    double ** set;
    int number , size;
    getData(set , number , size , "train.txt" , input);
    cout << "Number for : " << number << endl;
    //getchar();
    ann -> train(set , number , 10000000 , 3e-1 , 4e-3 , 0.1 , 0.3, 1e-4);
    //ann -> train(set , number , 10000000 , 3e-1 , 0, 0.1 , 0 , 1e-4);
    cout << "Train done ." << endl;
    for (int i = 0; i < number; ++i)
        delete set[i];
    delete set;
    return 0;
}
