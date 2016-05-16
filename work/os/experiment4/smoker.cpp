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

/*
  struct semaphores{
  unsigned short semval;
  pid_t sempid;
  };

  union semun{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  };
*/

int  _pipe[2];

int P(int semid , int index = 0);

int V(int semid , int index = 0);

int main(int argc , char ** argv){

    //int status;
    // The grammar for creating the share memory.
    key_t key = ftok("." , 0x12);
    //int result = shmget(IPC_PRIVATE , 8 , 700);
    /*
      if(shmget(key ,   , IPC_PRIVATE | IPC_EXCL )){
      perror("Error for shmget failed.");
      return EXIT_FAILURE;
      }
    */
    /*
      char * address = (char*)shmat(result, NULL, IPC_CREAT | IPC_EXCL);
      if((int)(address) == -1){
      perror("Error for shmat error");
      return EXIT_FAILURE;
      }
    */
    //status = shmdt(address);
    /*
      int semid = semget( key , 10 , IPC_CREAT | IPC_EXCL);
      if(semid < 0){
      perror("Error for semid failed . ");
      return EXIT_FAILURE;
      }
    */
    //semeop(int semid , struct sembuf*semop , unsigned nops);
    //int temp;
    /*
      semctl(semid, 0 , GETVAL, temp);
      semctl(semid , 0 , SETVAL , 0);
    */
    /*
      if(msgget(key , IPC_CREAT | IPC_EXCL)){
      perror("Error msgget failed.");
      return EXIT_FAILURE;
      }

      msgbuf queue;

      if(msgsnd(key , &queue , 1 , 0)){
      perror("Error for msgsnd .");
      return EXIT_FAILURE;
      }

      if(msgrcv(key, &queue, 1, 0, 0)){
      perror("Error for msgrcv the msg .");
      return EXIT_FAILURE;
      }

      if(msgctl(key, IPC_RMID, NULL)){
      perror("Error for rm the msg id .");
      return EXIT_FAILURE;
      }
    */
    // The grammar fro attaching the share memory to the process
    /*
      shmat();
      shmdt();
    */
    int shmid , semid , msgid;
    while(1){
        sleep(2);
        shmid = shmget(key , 0 , IPC_CREAT);
        if(shmid < 0){
            perror("Error for shmget .");
            //return EXIT_FAILURE;
        }
        semid = semget(key , 0 , IPC_CREAT);
        if(semid < 0){
            perror("Error for semget .");
            //return EXIT_FAILURE;
        }
        msgid = msgget(key , IPC_CREAT);
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
            sleep(2);
            P(semid);
            {
                int * address = (int *)shmat(shmid, NULL, 0);
                if((int)(address) == -1){
                    perror("Error for shmat.");
                    return EXIT_FAILURE;
                }
                if(address[0] <= 0){
                    //send msg to mqueue
                    if(flag){
                        msgbuf buf;
                        buf.mtext[0] = 'T';
                        if(msgsnd(msgid, &buf, sizeof(char), IPC_NOWAIT)){
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
            // code for G
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
                        //send msg to mqueue
                        if(flag){
                            msgbuf buf;
                            buf.mtext[0] = 'G';
                            if(msgsnd(msgid, &buf, sizeof(char), IPC_NOWAIT)){
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
            // code for P
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
                        //send msg to mqueue
                        if(flag){
                            msgbuf buf;
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

int P(int semid , int index){
    sembuf buf = {index , -1 , SEM_UNDO};
    /*
      buf.sem_num = index;
      buf.sem_op = -1;
      buf.sem_flg = SEM_UNDO;
    */
    if(semop(semid , &buf , 1)){
        perror("Error for operation P .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int V(int semid , int index){
    sembuf buf = {index , 1 , SEM_UNDO};
    /*
      buf.sem_num = index;
      buf.sem_op = 1;
      buf.sem_flg = SEM_UNDO;
    */
    if(semop(semid , &buf , 1)){
        perror("Error for operation V .");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif
