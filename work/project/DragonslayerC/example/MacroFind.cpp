#include "Scanner.h"

#include <exception>
#include <unistd.h>
using std::exception;

class Macro{
private:
    vector<string> with_argument;
    vector<string> without_form;
    vector<string> without_value;
    vector<string> with_form;
    vector<string> with_value;
    string beef ;
    string input , output;
    int get(string value , int index);
    Scanner * scan;
    void init();
    bool adjust(vector<string> accept);
    void get_macro();
    bool check_identifier(string accept , string value);
    void remove(string target);
    string replace(string& value , bool falg = false);
    bool is_valid(string content , int start , int end);
    ofstream out;
public:
    Macro(string file , string out = "a.out");
    virtual ~Macro();
};

int Macro :: get(string value , int index){
    int count = 0;
    char ch;
    int left , right;
    left = right = 0;
    for (int i = index; i < value.length() && (!left ^ (left - right)); ++index) // Magic code , please don't change it untill you know how it works
    {
        ch = value[index];
        ++count;
        switch(ch) {
        case '(' : left ++ ; break;
        case ')' : right ++; break;
        }
    }
    return count;
}
/*
  The function is to check if the content is valid .
*/

bool Macro :: is_valid(string content , int start, int end ){
    //char ch = content[start-1];
    int length = content.length();
    char ch;
    if(start == 0 || !(((ch = content[start-1]) >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' )){
        if((end == length - 1)|| !(((ch = content[end+1]) >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' )){
            bool is_quotation = false , back = false , is_sinagle_quotation = false;
            for (int i = 0; i < start ; ++i)
            {
                char ch = content[i];
                /**************************here */
                if(ch == '\\'){
                    back = !back;
                }else if(is_quotation){
                    if(ch == '"'){
                        if(!back){
                            is_quotation = false;
                        }
                    }
                    back = false;
                    /**************************end  */
                }else if(ch == '"'){
                    if(back){
                        back = false;
                    }else {
                        is_quotation = true;
                    }
                }else if(is_sinagle_quotation){
                    if(ch == '\''){
                        if(!back){
                            is_sinagle_quotation = false;
                        }
                    }
                    back = false;
                }else if(ch == '\''){
                    if(back){
                        back = false;
                    }else {
                        is_sinagle_quotation = true;
                    }
                }else {
                    if(back) back = false;
                }
            }
            //cout << "CHEKC VALUE : " << !(is_quotation | is_sinagle_quotation) << endl;
            return !(is_quotation | is_sinagle_quotation);
        }
    }
    return false;
}

string Macro :: replace(string& value , bool mark){
    int length = with_form.size();
    //cout << "When the value is : " << value << endl;
    for (int i = 0; i < length; ++i)
    {
        int position = value.find(with_form[i]);
        while(position != -1 && position < value.length()){
            //cout << "GET(position) : " << position << endl << "Form : " << with_form[i] << endl;
            int formal_length = with_form[i].length();
            /**Get the function and range here */
            if(is_valid(value , position , position + formal_length - 1)){
                vector<string> function = vector<string>();
                vector<string> range = vector<string>();
                string store = "";
                char ch;
                int left , right ;
                left = right = 0;
                //cout << "-------------------------> " << with_argument[i] << endl;
                /*
                  To add all the with_argument[i] to the function .
                */
                for (int j = 0; j < with_argument[i].length() && (!left ^ (left - right)); ++j)
                {
                    ch = with_argument[i][j];
                    if(ch == ','){
                        function.push_back(store);
                        //cout << "ARGUMENT PUSH BACK : " << store << endl;
                        store = "";
                        continue;
                    }
                    else if(ch == '('){
                        left ++;
                    }else if(ch == ')'){
                        right ++;
                    }
                    store += ch;
                }
                if(trim(store).length())function.push_back(store);
                /*
                  cout << "SHOW THE FUNCTION " << endl;
                  for (int l = 0 ; l < function.size(); ++l)
                  {
                  cout << function[l] << endl;
                  }
                  cout << "SHOW DONE > " << endl;
                */
                store = "";
                left = 1;
                right = 0;
                //cout <<"VALUE : " <<  value.substr(position , value.length()) << endl;
                //cout << "posiation : " << position << endl;
                //cout << "form_length : " << with_form[i].length() << endl;
                /*
                  To add all the with_form[i] to the range .
                */
                for (int j = position + with_form[i].length() + 1 ; j < value.length(); ++j)
                {
                    ch = value[j];
                    //cout << "STORE : " << store << endl;
                    if(ch == ','){
                        range.push_back(store);
                        //cout << "RANGE PUSH BACK : " << store << endl;
                        store = "";
                        continue;
                    }else if(ch == '('){
                        left ++;
                    }else if(ch == ')'){
                        right ++ ;
                    }
                    if(!(!left ^ (left - right))) break;
                    store += ch;
                }
                if(trim(store).length()) range.push_back(store);
                //cout << "SHOW THE ALL " << endl;
                /*
                  for (int l = 0; l < range.size(); ++l)
                  {
                  cout << range[l] << endl;
                  }
                  cout << "DNE > E " << endl;
                */
                store = "";
                /**Get the function and range done */
                /**Find and replace it */
                string result = with_value[i];
                bool flag = false , control = false;
                /*
                  Replace start here now .
                */
                for (int k = 0 ; k < function.size(); ++k)
                {
                    if(control) break;
                    int index = result.find(function[k]);
                    while(index != -1 && index < result.length()){
                        int f_length = function[k].length();
                        //cout << "RESULT : " << result << endl;
                        if(is_valid(result , index , index + f_length -1)){
                            flag = true;
                            //cout << "RANGE[k] : " << range[k] << endl;
                            //cout << "K : " << k << endl;
                            //cout << "LENGHT : " << range[k].length() << endl;
                            result.replace(index , f_length , range[k]);
                            //cout << "RESULT : " << result << endl;
                            index += range[k].length() -1;
                        }
                        index = result.find(function[k] , index + 1);
                        /*cout << "INDEX : " << index << endl;
                          cout << "RESULT : " << result.length() << endl;*/
                    }
                }
                if(flag){
                    value.replace(position , get(value , position) , result);
                    position +=result.length() - 1;
                }
            }
            position = value.find(with_form[i] , position + 1);
        }
    }
    /** TEST AREA */
    length = without_form.size();
    for (int i = 0; i < length; ++i)
    {
        //Need change here .

        int position = value.find(without_form[i]);
        while(position != -1 && position < value.length()){
            //cout << "GET(position) : " << position << endl << "without_form[i] : " << without_form[i] << endl;
            bool exit = false;
            if(mark){
                int index = with_argument[with_argument.size()-1].find(without_form[i]);
                int mark_length = with_argument[with_argument.size()-1].length();
                if(index != -1 && index < mark_length){
                    int temp_length = without_form[i].length();
                    if(index == 0) {
                        if(index + temp_length -1 == mark_length - 1){
                            exit = true;
                        }else {
                            if(with_argument[with_argument.size()-1][index+temp_length] != ','){
                                exit = true;
                            }
                        }
                    }else {
                        if(index + temp_length - 1 == mark_length - 1){
                            if(with_argument[with_argument.size()-1][index-1] != ',') {
                                exit = true;
                            }
                        }else{
                            if(with_argument[with_argument.size()-1][index-1] != ',' || with_argument[with_argument.size()-1][index+temp_length] != ','){
                                exit = true;
                            }
                        }
                    }
                }
            }
            if(exit) break;
            int form_length = without_form[i].length();
            //cout << "FORM : " << without_form[i] << endl;
            if(is_valid(value , position , position + form_length - 1)){
                //cout << "VALID ------------------------> " << endl;
                value.replace(position ,form_length , without_value[i]);
                //cout << "AFTER (value) : " << value << endl;
                position += without_value[i].length() - 1;
            }
            position = value.find(without_form[i] , position + 1);
        }
    }
    /*** TEST AREA DONE */
    return value;
}

void Macro :: remove(string target){
    //cout << "EASY TAEGET : " << target << endl;
    for(int i = 0 ; i < with_form.size() ; i++){
        if(!with_form[i].compare(target)){
            //cout << "Removing the target : " << target << endl;
            //cout << "The goal with_form[i] : " << with_form[i] << endl;
            with_form.erase(with_form.begin() + i);
            with_argument.erase(with_argument.begin() + i);
            with_value.erase(with_value.begin() + i);
        }
    }
    for (int i = 0; i < without_form.size(); ++i)
    {
        if(!without_form[i].compare(target)){
            //cout << "Removing the target : " << target << endl;
            //cout << "The goal without_form[i] : " << without_form[i] << endl;
            without_form.erase(without_form.begin() + i);
            without_value.erase(without_value.begin() + i);
        }
    }
}

bool Macro :: check_identifier(string accept , string value){
    int length = accept.length();
    string temp = "";
    for(int i = 0 ;  i < length ; i++){
        char ch = accept[i];
        if(i == 0){
            if(!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' )){
                return false;
            }
        }
        else if(!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || (ch >= '0' && ch <= '9'))){
            if(ch != '('){
                return false;
            }else{
                /*string formal = "";
                  for(; i < length && accept[i] != ')' ; i++){
                  if(accept[i])
                  formal += accept[i];
                  }*/
                with_argument.push_back(accept.substr(i+1 , length - i - 2));
                //cout << "PUSH_BACK(form) : " << temp << endl;
                //cout << "PUSH_BACK(argument) : " << accept.substr(i+1 , (length -i - 2)) << endl;
                with_form.push_back(temp);
                with_value.push_back(replace(value , true));
                //cout << "PUSH_BACK(VALUE) : " << with_value[with_value.size()-1] << endl;
                return true;
            }
        }
        temp += ch;
    }
    //cout << "PUSH_BACK(form) : " << temp << endl;
    //cout << "PUSH_BACK(VALUE) : " << value << endl;
    without_form.push_back(temp);
    without_value.push_back(replace(value));
    return true;
}

Macro :: Macro(string abpt , string out){
    //cout << abpt << endl;
    //cout << out << endl;
    output = out;
    scan = new Scanner(abpt);
    init();
}

void Macro :: init(){
    get_macro();
    //cout << "DOEN > " << endl;
}

void  Macro :: get_macro(){
    string beef = "";
    vector<string> accept;
    //cout << beef.length() << endl;
    remove(output);
    out.open(output.c_str(), std::ios::out);
    if(!out) {
        throw new exception();
    }
    while(( beef = scan -> nextLine()).length()){
        //cout << "BEEF : " << beef << endl;
        accept = scan -> next(beef);
        if(adjust(accept)){
            out << replace(beef) << endl;
            cout << beef << endl;
        }
    }
}

bool Macro :: adjust(vector<string> accept){
    for (int i = 0; i < accept.size(); ++i) //Finally delete it .
    { //Finally delete it .
        //cout << accept[i] << endl; //Finally delete it .
        if(i == 0){
            if(accept[0].compare("#define") == 0){
                if(accept.size() < 3) {
                    //cout << "I catch you . " << endl;
                    return false;
                }
                string value = "";
                for(int i = 2 ; i < accept.size() ; i++){
                    value += accept[i];
                }
                //cout << "Let's check it " << endl;
                if(!check_identifier(accept[1] , value)){
                    //cout << "Throw the exception . " << endl;
                    throw "Unable to define the unidentifire . ";
                }
                //cout << "We check done . " << endl;
                return false;
            }else if(accept[0].compare("#undef") == 0){
                string target = accept[1];
                //cout << "Remove the : " << accept[1] << endl;
                //remove(accept[1].substr(1,accept[i].length()));
                remove(accept[1]);
                return false;
            }
        }
    } //Finally delete it .
    return true;
}

Macro :: ~Macro(){
    scan -> ~Scanner();
    out.close();
    //cout << "Life is done . " << endl;
}

int main(int argc , char ** argv){
    /*
      cout << argv[1] << endl;
      cout << argv[2] << endl;
      cout << argv[3] << endl;
      cout << argv[4] << endl;
    */
    string * input  , * output;
    input = new string();
    //cout << sizeof(argv[0]) << endl;
    try{
        for (int i = 1; i < argc ;  i += 2)
        {
            if(!strcmp(argv[i] , "")){
                throw exception();
            }
            if(!strcmp(argv[i] , "-f")) {
                input = new string(argv[i+1]);
                continue;
            }
            if(!strcmp(argv[i] , "-o")){
                output = new string(argv[i+1]);
                continue;
            }
        }
        if(!(*input).length()){
            cout << "Error with out input file name ." << endl;
            return 1;
        }
        Macro temp(*input , *output);
    }catch(exception temp){
        cout << "Invalid input or file not found . " << endl;
        return 1;
    }
    return 0;
}
