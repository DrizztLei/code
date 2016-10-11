/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Aug 2016 11:01:24 PM UTC
 ************************************************************************/

#include"head.h"
#include<iostream>
using namespace std;
int main()
{
        mysql *my = new mysql();
        my->init_num(4);
        int num = my->get_num();
        cout << "num is " << num << endl;
        my->init_size(100);
        u_int size = my->get_size();
        cout << "file_size is " << size << endl;
        my->init_name( (char*)("MYSQL")  );
        cout << my->get_name() << endl;
        return 0; 

}
