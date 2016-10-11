#ifndef _CUS_C
#define _CUS_C

#include "message.h"

#define NUM 4

union semun{
    int val;
    struct semid_ds * buf;
    unsigned short * array;
};

int P(int semid , int index);

int V(int semid , int index);

void show(int * address , int limit){
    for(int i = 0 ; i < limit ; i++){
        printf("Get the value %d for %d .\n" , i , address[i]);
    }
}

void handler();

void handler(){
    return;
}

int main(int argc , char ** argv){
    //and(time(NULL));
    srand(0);
    //key_t key_shm = get_key("./" , 0x12);
    key_t key_sem = get_key("./" , 0x13);
    key_t key_sofa = get_key("./" , 0x14);
    key_t key_wait = get_key("./" , 0x15);
    key_t key_charge = get_key("./" , 0x16);
    key_t key_barber = get_key("./" , 0x17);
    //int shmid , semid , msg_sofa , msg_wait , msg_charge , msg_barber;
    int semid , msg_sofa , msg_wait , msg_charge , msg_barber;
    /*
      shmid = shmget(key_shm , num , IPC_CREAT | IPC_EXCL);
      if(shmid < 0){
      perror("The shm not found.");
      }
    */
    semid = semget(key_sem , 8 , IPC_CREAT);
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
    union semun sender;
    sender.val = 0;
    /*
      SOFA,
      WAIT,
      PEOPLE,
      S_W_LOCK,
      BARBE,
      CHARGE,
      IN_SOFA,
      LEAVE,
    */
    int array[8] = {0 ,0 ,20 ,1 ,0 ,1 ,0};
    for(int i = 0 ; i < 8; i++){
        sender.val = array[i];
        if(semctl(semid , i , SETVAL , sender)){
            printf("catch the info for %d.\n" , i);
            perror("Error for set the value .");
            return EXIT_FAILURE;
        }
    }
    signal(SIGCONT , handler);
    pid_t son = fork();
    if(son < 0){
        perror("Error for fork.");
        return EXIT_FAILURE;
    }else if(son == 0){
        //code for son.
        /*
          int number = 4;
          pid_t key[number];
          for(int i = 0 ; i < number ; i++){
          key[i] = fork();
          printf("The id %d is %d.\n" , i , getpid());
          }
        */
        int i = 0 , number = 7;
        while(i < number){
            sleep(2);
            pid_t son = fork();
            if(son < 0){
                perror("Error in frok()");
            }else if(son == 0){
                printf("Get the order %d and id %d.\n" , i , getpid());
                {
                    while(1){
                        P(semid , PEOPLE); // waiting the people which < 20.
                        P(semid , S_W_LOCK); // lock the sofa_wait lock.
                        if(msg_length(msg_sofa) < 4){
                            struct msgbuf buf;
                            buf.mtype = getpid();
                            buf.mtext[0] = 'S';
                            if(msgsnd(msg_sofa, &buf, SIZE , IPC_NOWAIT)){
                                perror("Error for msgsnd in sofa .");
                                return EXIT_FAILURE;
                            }
                            printf("message's length %d .\n" , msg_length(msg_sofa));
                            V(semid , SOFA); // add the number in sofa.
                            V(semid , S_W_LOCK); // unlock the sofa_wait lock.
                            P(semid , BARBE); // in queue to get barbed.
                            P(semid , LEAVE); // in queue to charge and leave.
                            printf("Over the customer %d who was luck.\n" , getpid());
                            V(semid , PEOPLE);
                        }else if(msg_length(msg_wait) < 13){
                            struct msgbuf buf;
                            buf.mtype = getpid();
                            buf.mtext[0] = 'W';
                            if(msgsnd(msg_wait, &buf, SIZE, IPC_NOWAIT)){
                                perror("Error for msgsnd in wait .");
                                return EXIT_FAILURE;
                            }
                            V(semid , WAIT); // add the number in wait.
                            V(semid , S_W_LOCK); // unlock the sofa_wait lock.
                            P(semid , IN_SOFA); // in queue to get the sofa.
                            P(semid , S_W_LOCK);// imatate the value of before.
                            V(semid , SOFA); // add the number in sofa.
                            V(semid , S_W_LOCK);// imagetate the vlaue of before.
                            P(semid , BARBE); // in queue to get the barbed.
                            P(semid , LEAVE); // in queue to charge and leave.
                            printf("Over the customer %d who was not luck.\n" , getpid());
                            V(semid , PEOPLE);
                        }else{
                            perror("Error for process the logic.\n");
                            exit(EXIT_FAILURE);
                        }
                        printf("Run over here.\n");
                    }
                }
                break;
            }else if(son > 0){
                printf("Deamon process here for order %d.\n" , i);
                i++;
            }
        }
        exit(EXIT_SUCCESS);
        return EXIT_FAILURE;
    }else if(son > 0){
        waitpid(son , 0 , 0);
    }
    return EXIT_SUCCESS;
}

int P(int semid , int index){
    struct sembuf buf = {index , -1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation P .\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int V(int semid , int index){
    struct sembuf buf = {index , 1 , SEM_UNDO};
    if(semop(semid , &buf , 1)){
        perror("Error for operation V .\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int msg_length(key_t msgid){
    struct msqid_ds buf;
    if(msgctl(msgid, IPC_STAT, &buf)){
        perror("Error for msgctl in msg_length.");
        return EXIT_FAILURE;
    }
    return buf.msg_qnum;
}

#endif
