/*************************************************************************
	> File Name: name.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Aug 2016 11:00:38 PM UTC
 ************************************************************************/

#include"head.h"
#include<stdio.h>
#include<string.h>
#include<malloc.h>

void mysql::init_name(char * name) 
{
    if( ( sizeof(name) + 1  ) > this->file_size ) 
    {
        printf("the length of name is too long\n");
        return ;
      
    }
    this->file_name = (char *)calloc(1,sizeof(name)+1);
    strcpy(this->file_name, name);

}

char* mysql::get_name()
{
    return this->file_name;

}
