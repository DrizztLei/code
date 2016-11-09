#ifndef TIME_CPP
#define TIME_CPP
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

string get_format_time()
{
    time_t timel;
    time(&timel);
    string time = (asctime(gmtime(&timel)));
    return time.substr(0 , time.length() - 1) ;
}
#endif
