#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
struct torgle_register{
    unsigned int SN : 4;
    unsigned int : 4;
    bool goodInt : 1;
    bool goodTorgle : 1;
};

union one4all
{
    int int_val;
    long long_val;
    double double_val;
};

struct test
{
    union {
        long id_name;
        short short_name;
        bool struct_temp;

    };
    torgle_register struct_define ;
};

int main(){
    one4all a;
    test bb;
    cout << bb.id_name << endl;

    torgle_register temp = { 2  , true , true};
    return 0;
}
