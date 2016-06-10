#ifndef _BAR_CPP
#define _BAR_CPP

#include "message.h"

int get_random(){
    return random() % 5;
}

void charge();

int move(key_t key_sofa , key_t key_wait);

key_t key_shm , key_sem , key_sofa , key_wait , key_charge , key_barber;

int shmid , semid , msg_sofa , msg_wait , msg_charge , msg_barber;

void barbe(char * string , int id , struct msgbuf * buf);

int main(int argc , char ** argv){
    // The grammar for creating the share memory.
    int const num = 8;
    key_t key_sem = get_key("./" , 0x13);
    key_t key_sofa = get_key("./" , 0x14);
    key_t key_wait = get_key("./" , 0x15);
    key_t key_charge = get_key("./" , 0x16);
    key_t key_barber = get_key("./" , 0x17);
    semid = semget(key_sem , num , IPC_CREAT);
    if(semid < 0){
        perror("The sem not found.");
    }
    msg_sofa = msgget(key_sofa , IPC_CREAT);
    if(msg_sofa < 0){
        perror("Error for msgget.");
    }
    msg_wait = msgget(key_wait , IPC_CREAT);
    if(msg_wait < 0){
        perror("Error for msgget.");
    }
    msg_charge = msgget(key_charge , IPC_CREAT);
    if(msg_charge < 0){
        perror("Error for msgget.");
    }
    msg_barber = msgget(key_barber, IPC_CREAT);
    if(msg_barber < 0){
        perror("Error for msgget.");
    }
    pid_t A = fork();
    if(A < 0){
        perror("create the A fork() error.");
        return EXIT_FAILURE;
    }else if(A == 0){
        // code for A
        while(1){
            struct msgbuf buf;
            P(semid , SOFA); // waiting the cus int sofa coming.
            P(semid , S_W_LOCK); // lock the sofa_wait_lock.
            int id = move(msg_sofa , msg_wait); // move the customer from the wait to sofa.
            V(semid , S_W_LOCK); // unlock the sofa_wait_lock.
            barbe("A" , id , &buf); // barbe the customer.
            P(semid , CHARGE); // lock the charge.
            charge(); // let the customer charge.
            V(semid , CHARGE); // unlock the charge.
        }
    }else if(A > 0){
        pid_t B = fork();
        if(B < 0){
            perror("create the B fork() error.");
            return EXIT_FAILURE;
        }else if(B == 0){
            while(1){
                struct msgbuf buf;
                P(semid , SOFA); // waiting the cus int sofa coming.
                P(semid , S_W_LOCK); // lock the sofa_wait_lock.
                int id = move(msg_sofa , msg_wait); // move the customer from the wait to sofa.
                V(semid , S_W_LOCK); // unlock the sofa_wait_lock.
                barbe("A" , id , &buf); // barbe the customer.
                P(semid , CHARGE); // lock the charge.
                charge(); // let the customer charge.
                V(semid , CHARGE); // unlock the charge.
            }
        }else if(B > 0){
            pid_t C = fork();
            if(C < 0){
                perror("create the C fork() error.");
                return EXIT_FAILURE;
            }else if(C == 0){
                while(1){
                    struct msgbuf buf;
                    P(semid , SOFA); // waiting the cus int sofa coming.
                    P(semid , S_W_LOCK); // lock the sofa_wait_lock.
                    int id = move(msg_sofa , msg_wait); // move the customer from the wait to sofa.
                    V(semid , S_W_LOCK); // unlock the sofa_wait_lock.
                    barbe("A" , id , &buf); // barbe the customer.
                    P(semid , CHARGE); // lock the charge.
                    charge(); // let the customer charge.
                    V(semid , CHARGE); // unlock the charge.
                }
            }else if(C > 0){
                waitpid(A,0,0);
                waitpid(B,0,0);
                waitpid(C,0,0);
            }
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
        if(msgrcv(msg_charge, &buf, SIZE, 0, IPC_NOWAIT) == -1){
            perror("Error for charge msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("charge %ld customer of %d barber.\n" , buf.mtype , getpid());
        V(semid , LEAVE);
    }
}

int move(key_t key_sofa , key_t key_wait){
    struct msgbuf buf;
    int id ;
    int message;
    sleep(3);
    if((message = msgrcv(key_sofa, &buf, SIZE , 0 , IPC_NOWAIT))==-1){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    /*
    printf("Get the id for %ld.\n" , buf.mtype);
    printf("Get the mytpe for %d\n" , (int)buf.mtype);
    printf("Get the mtext for %s\n" , buf.mtext);
    */
    id = buf.mtype;
    if(msgrcv(key_wait, &buf, SIZE, 0, IPC_NOWAIT)){
        //perror("Empty for wait.");
        printf("Empyt in wait.\n");
        //exit(EXIT_FAILURE);
    }
    if(buf.mtype == -1 || buf.mtype == id) {
        return id;
    }
    printf("Let the customer %ld get the queue in sofa.\n" , buf.mtype);
    buf.mtext[0] = 'W';
    if(msgsnd(key_sofa, &buf, SIZE, IPC_NOWAIT)){
        perror("Error for moving of msgsnd .");
        exit(EXIT_FAILURE);
    }
    V(semid , IN_SOFA);
    return id;
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
    buf -> mtype = id;
    buf -> mtext[0] = 'C';
    if(msgsnd(msg_charge, buf, SIZE, IPC_NOWAIT)){
        perror("Error for msgsnd in barbe .\n");
        exit(EXIT_FAILURE);
    }
}
#endif
