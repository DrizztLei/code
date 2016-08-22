/*************************************************************************
	> File Name: num.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Aug 2016 10:59:13 PM UTC
 ************************************************************************/

#include"head.h"
#include<iostream>
using namespace std;

void mysql::init_num(int n)
{
    this->num = n;

}

int mysql::get_num()
{
    return this->num;

}

