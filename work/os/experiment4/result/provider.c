#ifndef _PRO_C
#define _PRO_C

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

int  _pipe[2];

int P(int semid );
int V(int semid );

struct msgbuf{
    long type;
    char mtext[1];
    int id;
};

int get_random(){
    return random() % 3;
}
int main(int argc , char ** argv){
    srand((time(0)));
    if(pipe(_pipe)){
        perror("Error for create the pipe.\n");
        return EXIT_FAILURE;
    }
    key_t key = ftok("." , 0x12);
    int shmid = shmget(key, 1024, IPC_CREAT | IPC_EXCL);
    if(shmid < 0){
        perror("Error for shmget failed . ");
        return EXIT_FAILURE;
    }
    int * temp = (int *)shmat(shmid , NULL , 0);
    if((int)(temp) == -1){
        perror("Error for shmat.");
        return EXIT_FAILURE;
    }
    int semid = semget(key, 1 , IPC_CREAT | IPC_EXCL);
    if(semid < 0){
        perror("Error for semid failed . ");
        return EXIT_FAILURE;
    }
    int msgid = msgget(key, IPC_CREAT | IPC_EXCL);
    if(msgid < 0){
        perror("Error for msgid failed . ");
        return EXIT_FAILURE;
    }
    pid_t son = fork();
    if(son == 0){
        int x = 0;
        write(_pipe[1] , &x , sizeof(int));
        struct msgbuf buf;
        buf.mtext[0] = 'U';
        while(1){
            sleep(2);
            P(semid);
            {
                if(msgrcv(msgid, &buf, sizeof(char)+sizeof(int), 0, IPC_NOWAIT)){
                    if(strcmp(buf.mtext , "U") == 0){
                        x = get_random();
                        int * result = (int *)shmat(shmid, NULL, 0);
                        if((int)(result) == -1){
                            perror("Error for shmat .");
                            return EXIT_FAILURE;
                        }
                        result[x] ++;
                        if(shmdt(result)){
                            perror("Error for shmdt.");
                            return EXIT_FAILURE;
                        }
                    }else{
                        switch (buf.mtext[0]){
                        case 'T':{
                            int * result = (int *)shmat(shmid, NULL, 0);
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            result[0] ++;
                            if(shmdt(result)){
                                perror("Error for shmdt in T.");
                                return EXIT_FAILURE;
                            }
                            break;
                        }
                        case 'P':{
                            int * result = (int *)shmat(shmid, NULL, 0);
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            result[1] ++;
                            if(shmdt(result)){
                                perror("Error for shmdt in P.");
                                return EXIT_FAILURE;
                            }
                            break;
                        }
                        case 'G':{
                            int * result = (int *)shmat(shmid, NULL, 0);
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            result[2] ++;
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
    }else if(son > 0){
        int x = 0;
        read(_pipe[0] , &x , sizeof(int));
        struct msgbuf buf ;
        buf.mtext[0] = 'U';
        while(1){
            x = get_random();
            sleep(2);
            P(semid);
            {
                if(msgrcv(msgid, &buf, sizeof(char)+sizeof(int), 0, IPC_NOWAIT)){
                    if(strcmp(buf.mtext , "U") == 0){
                        x = get_random();
                        int * result = (int *)shmat(shmid, NULL, 0);
                        if((int)(result) == -1){
                            perror("Error for shmat .");
                            return EXIT_FAILURE;
                        }
                        result[x] ++;
                        if(shmdt(result)){
                            perror("Error for shmdt.");
                            return EXIT_FAILURE;
                        }
                    }else{
                        switch (buf.mtext[0]){
                        case 'T':{
                            int * result = (int *)shmat(shmid, NULL, 0);
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            result[0] ++;
                            if(shmdt(result)){
                                perror("Error for shmdt in T.");
                                return EXIT_FAILURE;
                            }
                            break;
                        }
                        case 'P':{
                            int * result = (int *)shmat(shmid, NULL, 0);
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            result[1] ++;
                            if(shmdt(result)){
                                perror("Error for shmdt in P.");
                                return EXIT_FAILURE;
                            }
                            break;
                        }
                        case 'G':{
                            int * result = (int *)shmat(shmid, NULL, 0);
                            if((int)(result) == -1){
                                perror("Error for shmat .");
                                return EXIT_FAILURE;
                            }
                            result[2] ++;
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

int P(int semid){
    struct sembuf buf = {0 , -1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation P .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int V(int semid){
    struct sembuf buf = {0 , 1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation V .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif
