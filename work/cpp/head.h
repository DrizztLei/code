#ifndef _MY_HEAD_H
#define _MY_HEAD_H

#define u_int unsigned int
#include<malloc.h>
class mysql
{

	public :
		char *file_name;
		u_int file_size;
		int num; 
	public :
		void init_size(u_int size);
		u_int get_size();
		char *get_name();
		void init_name(char* name);
		void init_num(int n);
		int get_num();	
		void add(int n);
		void del(int n);
		~mysql()
		{
			free(file_name);
		}
};
#endif
