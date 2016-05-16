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
        for (int i = 1; i < count ; i++) {
            if(count % i == 0) cout << "The possibility is " << i << endl;
        }
        cout << "Sample is broken ! " << endl;
        exit(0);
    }
    return count;
}
void getData(double ** & set , int & number , int & size , string filename , int input){
    double var;
    std :: ifstream in;
    cout << "open the file : " << filename << endl;
    in.open(filename.c_str());
    if(!in.is_open()){
        cout << "Error for file busy or not found . " << endl;
        throw "Resources busy . ";
        exit(EXIT_FAILURE);
    }
    int count = getNumber(filename , input);
    size = input+1;
    number = count / (size);
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

template<typename T>
void generate_svm(T ** set , string filename , int number , int size){
    std::ofstream out;
    out.open(filename.c_str());
    if(out.is_open()){
        for(int i = 0 ; i < number ; i++){
            if(set[i][size] >= 3){
                out << set[i][size] - 3 << " ";
                for(int j = 0 ; j < size ; j++){
                    out << j+1 << ":" << set[i][j] << " " ;
                }
                out << "\n";
            }else{

            }
        }
    }
    cout << "generate over . " << endl;
}

int main(int argc , char ** argv){
    int array[2] = {256};
    int input = 256;
    int output = 4;
    int level = 1;
    Ann<double> * ann = new Ann<double>(input , level , array , output);
    double ** set;
    int number , size;
    getData(set , number , size , "file" , input);
    cout << "Number for : " << number << endl;
    //getchar();
    if(true){
        // train_set , train_size , train_times , learn_rate , regular , limit_error , probality , decay , addition , extract.
        ann -> train(set , number , 10000000 , 9e-2 , 4e-3 , 0.1 , 1e-1 , 1e-4 , 1 , 0);
        cout << "Train done ." << endl;
        for (int i = 0; i < number; ++i){
            delete[] set[i];
        }
        delete[] set;
    }else{
        generate_svm(set , "sample.data" , number , input);
    }
    return 0;
}
