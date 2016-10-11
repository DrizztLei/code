#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <error.h>
#include <string.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

#define SIZE 2014
#define PROFILE 2

struct semaphores{
    unsigned short semval;
    pid_t sempid;
};

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

key_t generate_key(){

    return ftok("." , 0x12);

}

void showbuf(shmid_ds buf , pid_t son){
    //printf("shm_segsz =%d bytes\n", buf..shm_segsz ) ;
    printf("parent pid=%d, shm_cpid = %d \n", getpid(), buf.shm_cpid ) ;
    printf("chlid pid=%d, shm_lpid = %d \n", son , buf.shm_lpid ) ;

}

int main(int argc, char ** argv){
    int flag[2];
    if(pipe(flag)){
        cout << "Error for create the pipe . \n";
        return EXIT_FAILURE;
    }
    key_t key = generate_key();
    shmid_ds buf;
    int shmid = shmget(key, SIZE,IPC_CREAT | IPC_EXCL); // create the share memory here

    if(shmid < 0){
        printf("Error for the ipc_id error\n");
        return EXIT_FAILURE;
    }
    pid_t son = fork();
    if(son < 0){

        perror("Error for the the pid \n");
        return EXIT_FAILURE;

    }else if(son == 0){

        int x = 0;
        write(flag[1] , &x ,sizeof(int));

        /*
          char * address = (char*)shmat(shmid , NULL , 0);
          if(((int)address) == -1){
          cout << "Error for attach the memory ." << endl;
          return EXIT_FAILURE;
          }
          char array[40];
          strcpy(array , address);
          printf("%s\n" , array);
          shmid_ds temp;
          if(shmdt(address)){
          cout << "Error for deattach the memory from son ." << endl;
          return EXIT_FAILURE;
          }
          if(shmctl(shmid , IPC_STAT , (&temp))){
          cout << "Error for get the info from son" << endl;
          return EXIT_FAILURE;
          }
          showbuf(temp , getpid());
          cout << "get the info from the IPC_STAT." << endl;
        */

        char * address = (char * ) shmat(shmid , NULL , !SHM_RDONLY);

        if((int)(address) == -1){
            perror("Error for the address not found.\n");
            return EXIT_FAILURE;
        }

        char get[40];
        strcpy(get , address);
        cout << "I'll get the info frm the osn ." << endl;
        printf("%s" , get);
        for(int i = 0 ; i < 40 ; i++){
            get[i] = i;
        }

        strcpy(address , get);

        shmdt(address);

    }else if(son > 0){
        char * TEMP = (char *)shmat(shmid , NULL , !SHM_RDONLY);
        if((int)(TEMP) == -1){
            perror ("Error for shmat the address\n");
            return EXIT_FAILURE;
        }

        char info[40] = "Testg for the .\n";

        strcpy(TEMP , info);

        shmdt(TEMP);

        cout << "Get the error info." << endl;

        int x = 0;
        read(flag[0] , &x ,sizeof(int));
        waitpid(son , 0 , 0);

        strcpy(info , TEMP);

        printf("%s" , info);
        /*
          char * address = (char*) shmat(shmid , NULL , !SHM_RDONLY);
          if(((int)address) == -1){
          perror("Get the address failed.\n");
          return EXIT_FAILURE;
          }
          if(shmctl(shmid, IPC_STAT , &buf)){
          cout << "Error for get info from the momory in father ." << endl;
          return EXIT_FAILURE;
          }
          strcpy(address, "info from pid.");
          waitpid(son , 0 , 0);
          if(shmdt(address)){
          cout << "Error for release the memory. form father" << endl;
          return EXIT_FAILURE;
          }
          if(shmctl(shmid, IPC_RMID , NULL)){
          cout << "Error for detacth the momory from father ." << endl;
          return EXIT_FAILURE;
          }
          cout << "Run the command over." << endl;
          cout << "operation the info light" << endl;
        */
        // we crteate the new world here .

        int semid = semget(key ,1 ,IPC_CREAT | IPC_EXCL);
        printf("Get the id for %d\n" , semid);

        if(semid < 0){
            perror("Error for the ipc_sem error\n");
            return EXIT_FAILURE;
        }

        char * address = (char*)shmat(shmid, NULL , !SHM_RDONLY);

        if(shmdt(address)){
            perror("Error for the shmdt");
            return EXIT_FAILURE;
        }

        if(shmctl(shmid, IPC_RMID, NULL)){
            perror("Error for the ipc_rmid.");
            return EXIT_FAILURE;
        }

        /*
          sembuf temp;
          temp.sem_flg;
          temp.sem_num;
          temp.sem_op;
          union semun sem_args;
          unsigned short array[2]={1,1};
          sem_args.array = array;
          //SETALL代表设置信号集中所有的信号量的值。1,代表2个，
          if(semctl(semid, 1, SETALL, sem_args)){
          perror("");
          return EXIT_FAILURE;
          }
          if(semop(semid, &temp, 1)){
          perror("");
          return EXIT_FAILURE;
          }
        */

        semun test;

        if(semctl(semid , 0 , GETVAL , test.val)){
            printf("Error for control the semctl.\n");
            perror("");
            return EXIT_FAILURE;
        }

        printf("%d for the info of the sem.\n" , test.val);

        test.val = 21345;
        if(semctl(semid , 0 , SETVAL , test)){
            printf("Error for control the semctl.\n");
            perror("");
            return EXIT_FAILURE;
        }

        printf("%d for the info of the sem.\n" , test.val);

        if(semctl(semid, 1, IPC_RMID , NULL)){
            perror("Error for change the status \n");
            return EXIT_FAILURE;
        }

        int mesid = msgget(key , IPC_CREAT | IPC_EXCL);
        if(mesid < 0){
            perror("Error for create the message \n");
            return EXIT_FAILURE;
        }

        msgbuf queue;
        queue.mtype = 10;
        queue.mtext[0] = 'd';

        if(msgsnd(mesid , &queue , 1 , 0)){
            perror("Error for msgsnd \n");
            return EXIT_FAILURE;
        }

        //int check = msgrcv(mesid , &queue , 1 , 0 , 0);
        //printf("Get the info %d\n" , check);
        if(!msgrcv(mesid, &queue, 1, 0, 0)){
            perror("Error for receive the msgqueue.");
            return EXIT_FAILURE;
        }

        printf("Get the message for %c\n" , queue.mtext[0]);

        if(msgctl(mesid, IPC_RMID, NULL)){
            perror("Error for delete the msgqueue.\n");
            return EXIT_FAILURE;
        }

    }else{

        perror("error for unknow reason.\n");

    }
    return EXIT_SUCCESS;
}
