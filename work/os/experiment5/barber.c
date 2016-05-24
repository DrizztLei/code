#ifndef _BAR_CPP
#define _BAR_CPP

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
#include <string.h>

#define NUM 4

enum type{
    SOFA,
    WAIT,
    PEOPLE,
    S_W_LOCK,
    BARBE,
    CHARGE,
    IN_SOFA,
    LEAVE,
};

int  _pipe[2];

int get_random(){
    return random() % 5;
}

int P(int semid , int index);

int V(int semid , int index);

void charge();

void rest(int msg_barber);

void move(key_t key_sofa , key_t key_wait);

int msg_length(key_t msgid);

key_t get_key(char const * const address , int code){
    return ftok(address , code);
}

struct msgbuf{
    long type;
    char mtext[1];
    int id;
};

int const SIZE = sizeof(char) + sizeof(int);

key_t key_shm , key_sem , key_sofa , key_wait , key_charge , key_barber;

int shmid , semid , msg_sofa , msg_wait , msg_charge , msg_barber;

void barbe(char * string , int id , struct msgbuf * buf);

int main(int argc , char ** argv){
    // The grammar for creating the share memory.

    key_t key_shm = get_key("./" , 0x12);
    key_t key_sem = get_key("./" , 0x13);
    key_t key_sofa = get_key("./" , 0x14);
    key_t key_wait = get_key("./" , 0x15);
    key_t key_charge = get_key("./" , 0x16);
    key_t key_barber = get_key("./" , 0x17);

    while(1){
        shmid = shmget(key_shm , 0 , IPC_CREAT);
        if(shmid < 0){
            perror("The shm not found .");
        }
        semid = semget(key_sem , 0 , IPC_CREAT);
        if(semid < 0){
            perror("The sem not found .");
        }
        msg_sofa = msgget(key_sofa , IPC_CREAT);
        if(msg_sofa < 0){
            perror("Error for msgget .");
        }
        msg_wait = msgget(key_wait , IPC_CREAT);
        if(msg_wait < 0){
            perror("Error for msgget .");
        }
        msg_charge = msgget(key_charge , IPC_CREAT);
        if(msg_charge < 0){
            perror("Error for msgget .");
        }
        msg_barber = msgget(key_barber, IPC_CREAT);
        if(shmid > 0 && semid > 0 && msg_sofa > 0 && msg_wait > 0 && msg_charge > 0 && msg_barber > 0) {
            break;
        }
    }
    pid_t A = fork();
    if(A < 0){
        perror("create the t fork() error.");
        return EXIT_FAILURE;
    }else if(A == 0){
        // code for A
        while(1){
            struct msgbuf buf;
            P(semid , SOFA); // waiting the cus int sofa coming.
            P(semid , S_W_LOCK); // lock the sofa_wait_lock.
            move(msg_sofa , msg_wait); // move the customer from the wait to sofa.
            V(semid , S_W_LOCK); // unlock the sofa_wait_lock.
            barbe("A" , 3 , &buf); // barbe the customer.
            P(semid , CHARGE); // lock the charge.
            charge(); // let the customer charge.
            V(semid , CHARGE); // unlock the charge.
        }
    }
    return EXIT_SUCCESS;
}

int P(int semid , int index){
    struct sembuf buf = {index , -1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation P .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int V(int semid , int index){
    struct sembuf buf = {index , 1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation V .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void charge(){
    struct msgbuf buf;
    while(msg_length(msg_charge) > 0){
        if(msgrcv(msg_charge, &buf, SIZE, 0, IPC_NOWAIT)){
            perror("Error for charge msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("charge %d customer of %d barber.\n" , buf.id , getpid());
        V(semid , LEAVE);
    }
}

void rest(int msg_barber){
    struct msgbuf buf;
    buf.id = getpid();
    msgsnd(msg_barber, &buf, IPC_STAT, IPC_NOWAIT);
    return ;
}

void move(key_t key_sofa , key_t key_wait){
    struct msgbuf buf;
    buf.id = -1;
    if(msgrcv(key_wait, &buf, SIZE, 0, IPC_NOWAIT)){
        perror("Error for moving of msgrcv .");
        exit(EXIT_FAILURE);
    }
    if(buf.id == -1) {
        return ;
    }
    if(msgsnd(key_sofa, &buf, SIZE, IPC_NOWAIT)){
        perror("Error for moving of msgsnd .");
        exit(EXIT_FAILURE);
    }
    V(semid , IN_SOFA);
}

int msg_length(key_t msgid){
    struct msqid_ds buf;
    if(msgctl(msgid, IPC_STAT, &buf)){
        perror("Error for msgctl in msg_length.");
        return EXIT_FAILURE;
    }
    return buf.msg_qnum;
}

void barbe(char * string , int id , struct msgbuf * buf){
    printf("%s is barbe for %d .\n" , string , id);
    sleep(get_random());
    V(semid , BARBE);
    if(msgsnd(msg_charge, buf, SIZE, IPC_NOWAIT)){
        perror("Error for msgsnd in barbe .\n");
        exit(EXIT_FAILURE);
    }
}
#endif
