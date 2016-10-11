#include <cuda_runtime.h>
#include <stdio.h>

__global__ void kernel(){

}

int main(int argc , char ** argv){
    kernel<<<1,1>>>();
    printf("Hello.\n");
    return 0;
}
