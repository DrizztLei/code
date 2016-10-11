#ifndef _PRO_CPP
#define _PRO_CPP

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/msg.h>
#include <error.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

#define SIZE 1024
#define NUM 4

union semun{
    int val;
    struct semid_ds * buf;
    unsigned short * array;
};

int  _pipe[2];

key_t get_key( char const  * const address , int value){
    return ftok(address , value);
}

int P(int semid , int index = NUM - 1);

int V(int semid , int index = NUM - 1);

void show(int * address , int limit){
    for(int i = 0 ; i < limit ; i++){
        printf("Get the value %d for %d .\n" , i , address[i]);
    }
}

int get_random(){
    return random() % 3;
}

int main(int argc , char ** argv){
    srand(int(time(0)));
    if(pipe(_pipe)){
        perror("Error for create the pipe.\n");
        return EXIT_FAILURE;
    }
    key_t key_shm = get_key("./" , 0x12);
    int shmid = shmget(key_shm, SIZE, IPC_CREAT);
    if(shmid < 0){
        perror("Error for shmget failed . ");
        return EXIT_FAILURE;
    }
    int * temp = (int *)shmat(shmid , NULL , 0);
    if((int)(temp) == -1){
        perror("Error for shmat.");
        return EXIT_FAILURE;
    }
    key_t key_sem = get_key("./" , 0x13);
    int semid = semget(key_sem, NUM , IPC_CREAT);
    if(semid < 0){
        perror("Error for semid failed . ");
        return EXIT_FAILURE;
    }
    semun sender;
    sender.val = 1;
    for(int i = 0 ; i < NUM ; i++){
        if(semctl(semid , i , SETVAL , sender)){
            printf("catcht the info for %d.\n" , i);
            perror("Error for set the value .");
            return EXIT_FAILURE;
        }
    }
    key_t key_msg = get_key("./" , 0x14);
    int msgid = msgget(key_msg, IPC_CREAT);
    if(msgid < 0){
        perror("Error for msgid failed . ");
        return EXIT_FAILURE;
    }
    pid_t son = fork();
    if(son == 0){
        // code for the son .
        int x = 0;
        write(_pipe[1] , &x , sizeof(int));
        msgbuf buf;
        while(1){
            buf.mtext[0] = 'U';
            sleep(15);
            P(semid);
            {
                printf("son's process\n");
                if(msgrcv(msgid, &buf, sizeof(char), 0, IPC_NOWAIT)){
                    char character = buf.mtext[0];
                    x = get_random();
                    if(character == 'U'){
                        //code for generated the random product.
                        P(semid , x);
                        printf("generated the product random.\n");
                        int * result = (int *)shmat(shmid, NULL, 0);
                        if((int)(result) == -1){
                            perror("Error for shmat .");
                            return EXIT_FAILURE;
                        }
                        result[x] ++;
                        show(result , 3);
                        if(shmdt(result)){
                            perror("Error for shmdt.");
                            return EXIT_FAILURE;
                        }
                        V(semid,x);
                    }else{
                        //code for generated the specific product.
                        switch (character){
                        case 'T':{
                            P(semid , 0);
                            int * result = (int *)shmat(shmid, NULL, 0);
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            printf("generated the product T.\n");
                            result[0] ++;
                            show(result , 3);
                            if(shmdt(result)){
                                perror("Error for shmdt in T.");
                                return EXIT_FAILURE;
                            }
                            V(semid,0);
                            break;
                        }
                        case 'P':{
                            P(semid,1);
                            int * result = (int *)shmat(shmid, NULL, 0);
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            printf("generated the product P.\n");
                            result[1] ++;
                            show(result , 3);
                            if(shmdt(result)){
                                perror("Error for shmdt in P.");
                                return EXIT_FAILURE;
                            }
                            V(semid,1);
                            break;
                        }
                        case 'G':{
                            P(semid,2);
                            int * result = (int *)shmat(shmid, NULL, 0);
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            printf("generated the product G.\n");
                            result[2] ++;
                            show(result , 3);
                            if(shmdt(result)){
                                perror("Error for shmdt in G.");
                                return EXIT_FAILURE;
                            }
                            V(semid,2);
                            break;
                        }
                        default : break;
                        }
                    }
                }else{
                    perror("Error for msgrcv .");
                    return EXIT_FAILURE;
                }
            }
            V(semid);
        }
    }else if(son > 0){
        // code for the father.
        int x = 0;
        read(_pipe[0] , &x , sizeof(int));
        msgbuf buf ;
        printf("Get the info\n");
        while(1){
            buf.mtext[0] = 'U';
            x = get_random();
            sleep(15);
            P(semid);
            {
                printf("father's process\n");
                if(msgrcv(msgid, &buf, sizeof(char), 0, IPC_NOWAIT)){
                    char character = buf.mtext[0];
                    //if(strcmp(buf.mtext , "U") == 0){
                    //code for generated the random product.
                    x = get_random();
                    int * result = (int *)shmat(shmid, NULL, 0);
                    if(character == 'U'){
                        if((int)(result) == -1){
                            perror("Error for shmat .");
                            return EXIT_FAILURE;
                        }
                        printf("generated the product random.\n");
                        result[x] ++;
                        show(result , 3);
                        if(shmdt(result)){
                            perror("Error for shmdt.");
                            return EXIT_FAILURE;
                        }
                    }else{
                        //code for generated the specific product.
                        switch (character){
                        case 'T':{
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            printf("generated the product T.\n");
                            result[0] ++;
                            show(result , 3);
                            if(shmdt(result)){
                                perror("Error for shmdt in T.");
                                return EXIT_FAILURE;
                            }
                            break;
                        }
                        case 'P':{
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            printf("generated the product P.\n");
                            result[1] ++;
                            show(result , 3);
                            if(shmdt(result)){
                                perror("Error for shmdt in P.");
                                return EXIT_FAILURE;
                            }
                            break;
                        }
                        case 'G':{
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            printf("generated the product G.\n");
                            result[2] ++;
                            show(result , 3);
                            if(shmdt(result)){
                                perror("Error for shmdt in G.");
                                return EXIT_FAILURE;
                            }
                            break;
                        }
                        default : break;
                        }
                    }
                }else{
                    perror("Error for msgrcv .");
                    return EXIT_FAILURE;
                }
            }
            V(semid);
        }
        if(shmctl(shmid , IPC_RMID , 0)){
            perror("Error for delete the shm failed.");
            return EXIT_FAILURE;
        }
        if(semctl(semid , IPC_RMID , 0)){
            perror("Error for delete the sem failed.");
            return EXIT_FAILURE;
        }
        if(msgctl(msgid , IPC_RMID ,0)){
            perror("Error for delete the msg failed");
            return EXIT_FAILURE;
        }
    }else{
        perror("Error for create the pid failed.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int P(int semid , int index){
    sembuf buf = {index , -1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation P .");
        return EXIT_FAILURE;
    }
    printf("Get the info provider coming.\n");
    return EXIT_SUCCESS;
}

int V(int semid , int index){
    sembuf buf = {index , 1 , SEM_UNDO};
    printf("Get the info provider quiet.\n");
    if(semop(semid , &buf , 1)){
        perror("Error for operation V .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif
