#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int pipe_1[2] , pipe_2[2];
pthread_t thrd1 , thrd2;

void task1(int *number){
    int x = 1;
    do{
        printf("thread%d read : %d\n" , *number , x++);
        write(pipe_1[1] , &x ,  sizeof(int));
        read(pipe_2[0] ,&x , sizeof(int));
    }while(x <= 9);
    close(pipe_1[1]);
    close(pipe_2[0]);
    pthread_exit(EXIT_SUCCESS);
}

void task2(int *number){
    int x ;
    do{
        read(pipe_1[0],&x,sizeof(int));
        printf("thread%d read : %d\n" , *number , x++);
        write(pipe_2[1] , &x , sizeof(int));
    }while(x <= 9);
    close(pipe_1[0]);
    close(pipe_2[1]);
    pthread_exit(EXIT_SUCCESS);
}



int main(int argc , char ** argv){
    int ret , num1 , num2;
    if(pipe(pipe_1) < 0 || pipe(pipe_2) < 0){
        perror("pipe not created.");
        return EXIT_FAILURE;
    }
    ret = pthread_create(&thrd1, NULL, (void*)task1 , (void*)&num1);
    if(ret) {
        perror("pthread creator .");
        return EXIT_FAILURE;
    }

    num2 = 2;
    ret = pthread_create(&thrd1, NULL, (void*)task2,(void*)&num2);
    if(ret){
        perror("pthread not created");
        return EXIT_FAILURE;
    }

    printf("Unablieve\n") ;

    if(thrd1 != 0) pthread_join(thrd1 , NULL);
    if(thrd2 != 0) pthread_join(thrd2 , NULL);

    return EXIT_SUCCESS;
}
