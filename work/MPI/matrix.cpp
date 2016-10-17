/*************************************************************************
	> File Name: matrix.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 15 Oct 2016 03:08:42 PM CST
 ************************************************************************/


#include "mpi.h"
#include <iostream>

int main(int argc,  char* argv[])
{
	int rank;
	int size;
	MPI_Init(0,0);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	std::cout<<"Hello world from process "<<rank<<" of "<<size<<std::endl;

	MPI_Finalize();

	return 0;
}
