#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// about the pipe , we should pay attention to writing the data in filed[1].
int pipeline_x[2] , pipeline_y[2];

int calculator_x(int order){
    int x;
    if(order == 1){
        x = 1;
        return x;
    }else{
        x = calculator_x(order-1) * (order);
        //printf("%d for the x \n" , x);
        return x;
    }
}

int calculator_y(int order){
    int y;
    if(order == 1 || order == 2) {
        y = 1;
        return 1;
    }else{
        y = calculator_y(order-1) + calculator_y(order-2);
        //printf("cal y : %d\n" , y);
        return y;
    }
}

void fun_x(int order){
    int result = calculator_x(order);
    write(pipeline_x[1] , &result , sizeof(int));
    pthread_exit(EXIT_SUCCESS);
}


void fun_y(int order){
    int result = calculator_y(order);
    write(pipeline_y[1] , &result , sizeof(int));
    pthread_exit(EXIT_SUCCESS);
}

void* calculator(int * info){

    pthread_t function_x , function_y;
    if(pipe(pipeline_x) < 0){
        perror("Error for disable to create the pipe\n");
        return EXIT_FAILURE;
    }
    if(pipe(pipeline_y) < 0){
        perror("Error for disable to create the pipe\n");
        return EXIT_FAILURE;
    }
    //printf("%d for info[0] and %d for info[1]\n" , info[0] , info[1]);
    if(pthread_create(&function_x , NULL , fun_x , info[0]) != 0){
        perror("Error for create the thread .\n");
        return EXIT_FAILURE;
    }
    if(pthread_create(&function_y , NULL , fun_y , info[1]) != 0){
        perror("Error for create the thread .\n");
        return EXIT_FAILURE;
    }

    if(function_x != 0) pthread_join(function_x ,NULL);
    if(function_y != 0) pthread_join(function_y ,NULL);
    int x , y;

    read(pipeline_x[0] , &x , sizeof(int));
    read(pipeline_y[0] , &y , sizeof(int));

    //printf("for the function(x): %d\n" , x);
    //printf("for the function(y): %d\n" , y);

    for (int i = 0; i < 2; i++) {
        close(pipeline_x[i]);
        close(pipeline_y[i]);
    }
    printf("input x : %d \ninput y : %d\n" , info[0] , info[1]);
    printf("The result is : %d\n" , x+y);
    return EXIT_SUCCESS;
}

int main(int argc , char ** argv){
    pthread_t main;
    int info[2] = {4,5};
    if(pthread_create(&main , NULL , calculator , info) != 0){
        perror("Error for create the thread . \n");
        return EXIT_FAILURE;
    }
    if(main != 0) pthread_join(main , NULL);
    return EXIT_SUCCESS;
}
