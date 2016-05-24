#ifndef _SMO_CPP
#define _SMO_CPP

#include <stdio.h>
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

#define SIZE 1024
#define NUM 4

int  _pipe[2];

int P(int semid , int index = NUM - 1);

int V(int semid , int index = NUM - 1);

key_t get_key(char const * const address , int code){
    return ftok(address , code);
}

void show(int * address , int limit){
    for(int i = 0 ; i < limit ; i++){
        printf("Get the value %d for %d .\n" , i , address[i]);
    }
}

int main(int argc , char ** argv){
    // The grammar for creating the share memory.
    key_t key_shm = get_key("./" , 0x12);
    key_t key_sem = get_key("./" , 0x13);
    key_t key_msg = get_key("./" , 0x14);
    int shmid , semid , msgid;
    while(1){
        sleep(5);
        shmid = shmget(key_shm , 0 , IPC_CREAT );
        if(shmid < 0){
            perror("The shm not found . \n");
            //return EXIT_FAILURE;
        }
        semid = semget(key_sem , 0 , IPC_CREAT);
        if(semid < 0){
            perror("The sem not found . \n .");
            //return EXIT_FAILURE;
        }
        msgid = msgget(key_msg , IPC_CREAT);
        if(msgid < 0){
            perror("Error for msgget .");
            //return EXIT_FAILURE;
        }
        if(shmid > 0 && semid > 0 && msgid > 0) {
            break;
        }
    }

    pid_t T = fork();
    if(T < 0){
        perror("create the t fork() error.");
        return EXIT_FAILURE;
    }else if(T == 0){
        // code for T
        bool flag = true;
        while(1){
            sleep(10);
            P(semid , 0);
            {
                printf("process the smoker T . \n");
                int * address = (int *)shmat(shmid, NULL, 0);
                if((int)(address) == -1){
                    perror("Error for shmat.");
                    return EXIT_FAILURE;
                }
                if(address[0] <= 0){
                    //send msg to mqueue
                    printf("unable found the it. send message from T.\n");
                    if(flag){
                        msgbuf buf;
                        buf.mtext[0] = 'T';
                        if(msgsnd(msgid, &buf, sizeof(char), IPC_NOWAIT)){
                            perror("Error for msgsnd .");
                            return EXIT_FAILURE;
                        }
                        flag = !flag;
                    }else{
                        printf("The smoker is waiting .\n");
                        sleep(3);
                    }
                }else{
                    address[0] --;
                    flag = true;
                }
                show(address , 3);
                if(shmdt(address)){
                    perror("Error for shmdt .");
                    return EXIT_FAILURE;
                }
            }
            printf("over the smoker T . \n");
            V(semid , 0);
        }
    }else{
        pid_t G = fork();
        if(G < 0){
            perror("create the G fork() error.");
            return EXIT_FAILURE;
        }else if(G == 0){
            // code for G
            bool flag = true;
            while(1){
                sleep(15);
                P(semid , 2);
                {
                    printf("process the G .\n");
                    int * address = (int *)shmat(shmid, NULL, 0);
                    if((int)(address) == -1){
                        perror("Error for shmat.");
                        return EXIT_FAILURE;
                    }
                    if(address[2] <= 0){
                        //send msg to mqueue
                        printf("unable found the it. send message from G.\n");
                        if(flag){
                            msgbuf buf;
                            buf.mtext[0] = 'G';
                            if(msgsnd(msgid, &buf, sizeof(char), IPC_NOWAIT)){
                                perror("Error for msgsnd .");
                                return EXIT_FAILURE;
                            }
                            flag = !flag;
                        }else{
                            printf("The smoker is waiting .\n");
                            sleep(3);
                        }
                    }else{
                        address[2] --;
                        flag = true;
                    }
                    show(address , 3);
                    if(shmdt(address)){
                        perror("Error for shmdt .");
                        return EXIT_FAILURE;
                    }
                }
                printf("over the G .\n");
                V(semid , 2);
            }
        }else{
            // code for P
            bool flag = true;
            while(1){
                sleep(5);
                P(semid , 1);
                {
                    printf("process the P .\n");
                    int * address = (int *)shmat(shmid, NULL, 0);
                    if((int)(address) == -1){
                        perror("Error for shmat.");
                        return EXIT_FAILURE;
                    }
                    if(address[1] <= 0){
                        //send msg to mqueue
                        printf("unable found the it. send message from P.\n");
                        if(flag){
                            msgbuf buf;
                            buf.mtext[0] = 'P';
                            if(msgsnd(msgid, &buf, sizeof(char), IPC_NOWAIT)){
                                perror("Error for msgsnd .");
                                return EXIT_FAILURE;
                            }
                            flag = !flag;
                        }else{
                            printf("The smoker is waiting .\n");
                            sleep(3);
                        }
                    }else{
                        address[1] --;
                        flag = true;
                    }
                    show(address , 3);
                    if(shmdt(address)){
                        perror("Error for shmdt .");
                        return EXIT_FAILURE;
                    }
                }
                printf("over the P .\n");
                V(semid , 1);
            }
        }
    }
    return EXIT_SUCCESS;
}

int P(int semid , int index){
    sembuf buf = {index , -1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation P .");
        return EXIT_FAILURE;
    }
    printf("Get the info for smoker coming. \n");
    return EXIT_SUCCESS;
}

int V(int semid , int index){
    sembuf buf = {index , 1 , SEM_UNDO};
    printf("Get the info for smoker quiet. \n");
    if(semop(semid , &buf , 1)){
        perror("Error for operation V .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif
