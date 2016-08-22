/*************************************************************************
	> File Name: size.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Aug 2016 11:00:13 PM UTC
 ************************************************************************/

#include"head.h"

void mysql::init_size(u_int size) 
{
    this->file_size = size;

}

u_int mysql::get_size()
{
    return this->file_size;

}
