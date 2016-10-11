#ifndef _SMO_C
#define _SMO_C

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
#include <stdbool.h>

int  _pipe[2];
int P(int semid );
int V(int semid );


struct msgbuf{
    long mtype;
    char mtext[1];
    int id;
};

int main(int argc , char ** argv){
    key_t key = ftok("." , 0x12);
    int shmid , semid , msgid;
//    while(1){
        sleep(2);
        shmid = shmget(key , 2 , IPC_CREAT );
        if(shmid < 0){
            perror("Error for shmget .");
        }
        semid = semget(key , 2 , IPC_CREAT);
        if(semid < 0){
            perror("Error for semget .");
        }
        msgid = msgget(key , IPC_CREAT);
        if(msgid < 0){
            perror("Error for msgget .");
        }
        if(shmid > 0 && semid > 0 && msgid > 0) {
//            break;
        }
//    }
    pid_t T = fork();
    if(T < 0){
        perror("create the t fork() error.");
        return EXIT_FAILURE;
    }else if(T == 0){
        printf("son .\n");
        struct msgbuf buf;
        buf.id = 21345;
        buf.mtext[0] = 'f';
        buf.mtype = 0;
        if(msgsnd(msgid, &buf, sizeof(int), IPC_NOWAIT)){
            perror("Error for msgsnd failed.\n");
        }
        if(msgsnd(msgid, &buf, sizeof(int)+sizeof(char), IPC_NOWAIT)){
            perror("Error for msgsnd failed.\n");
        }
        if(msgrcv(msgid, &buf, sizeof(int), 0, IPC_NOWAIT)){
            perror("Error for smgrcv.");
        }
        printf("get the value for %d.\n" , buf.id);
        printf("done.\n");
        bool flag = true;
        while(1){
            sleep(2);
            //P(semid);
            {
                int * address = (int *)shmat(shmid, NULL, 0);
                if((int)(address) == -1){
                    perror("Error for shmat.");
                    return EXIT_FAILURE;
                }
                if(address[0] <= 0){
                    if(flag){
                        struct msgbuf buf;
                        buf.mtext[0] = 'T';
                        if(msgsnd(msgid, &buf, sizeof(char)+sizeof(int), IPC_NOWAIT)){
                            perror("Error for msgsnd .");
                            return EXIT_FAILURE;
                        }
                        flag = !flag;
                    }else{
                        sleep(1);
                    }
                }else{
                    address[0] --;
                    flag = true;
                }
                if(shmdt(address)){
                    perror("Error for shmdt .");
                    return EXIT_FAILURE;
                }
            }
            V(semid);
        }
    }else{
        pid_t G = fork();
        if(G < 0){
            perror("create the G fork() error.\n");
            return EXIT_FAILURE;
        }else if(G == 0){
            bool flag = true;
            while(1){
                sleep(2);
                P(semid);
                {
                    int * address = (int *)shmat(shmid, NULL, 0);
                    if((int)(address) == -1){
                        perror("Error for shmat.");
                        return EXIT_FAILURE;
                    }
                    if(address[2] <= 0){
                        if(flag){
                            struct msgbuf buf;
                            buf.mtext[0] = 'G';
                            if(msgsnd(msgid, &buf, sizeof(char)+sizeof(int), IPC_NOWAIT)){
                                perror("Error for msgsnd .");
                                return EXIT_FAILURE;
                            }
                            flag = !flag;
                        }else{
                            sleep(1);
                        }
                    }else{
                        address[0] --;
                        flag = true;
                    }
                    if(shmdt(address)){
                        perror("Error for shmdt .");
                        return EXIT_FAILURE;
                    }
                }
                V(semid);
            }
        }else{
            bool flag = true;
            while(1){
                sleep(2);
                P(semid);
                {
                    int * address = (int *)shmat(shmid, NULL, 0);
                    if((int)(address) == -1){
                        perror("Error for shmat.");
                        return EXIT_FAILURE;
                    }
                    if(address[1] <= 0){
                        if(flag){
                            struct msgbuf buf;
                            buf.mtext[0] = 'P';
                            if(msgsnd(msgid, &buf, sizeof(char), IPC_NOWAIT)){
                                perror("Error for msgsnd .");
                                return EXIT_FAILURE;
                            }
                            flag = !flag;
                        }else{
                            sleep(1);
                        }
                    }else{
                        address[1] --;
                        flag = true;
                    }
                    if(shmdt(address)){
                        perror("Error for shmdt .");
                        return EXIT_FAILURE;
                    }
                }
                V(semid);
            }
        }
    }
    return EXIT_SUCCESS;
}
int P(int semid ){
    struct sembuf buf = {0 , -1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation P .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int V(int semid ){
    struct sembuf buf = {0 , 1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation V .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif
