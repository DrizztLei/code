#include "ipc.h"

int get_ipc_id(char * proc_file , key_t key){

    FILE *pf;
    int i , j;
    char line[BUFSZ] , colum[BUFSZ];

    if((pf=fopen(proc_file, "r")) == NULL){
        perror("Error for prof file not found.");
        exit(EXIT_FAILURE);
    }
    fgets(line,BUFSZ,pf);
    while(!feof(pf)){
        i = j = 0;
        fgets(line , BUFSZ , pf);
        while(line[i] == ' ') i++;
        while(line[i] != ' ') colum[j++] = line[i++];
        colum[j] = '\0';
        if(atoi(colum) != key) continue;
        j = 0;
        while(line[i] == ' ') i++;
        while(line[i] != ' ') colum[j++] = line[i++];
        colum[j] = '\0';
        i = atoi(colum);
        fclose(pf);
        return i;;
    }
    fclose(pf);
    return -1;
}

int P(int sem_id)
{
    struct sembuf buf;
    buf.sem_op = -1;
    buf.sem_num = 0;
    buf.sem_flg = SEM_UNDO;
    if((semop(sem_id,&buf,1)) < 0){
        perror("down error\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int V(int sem_id){
    struct sembuf buf;
    buf.sem_op = 1;
    buf.sem_num = 0;
    buf.sem_flg = SEM_UNDO;
    if((semop(sem_id , &buf , 1)) < 0){
        perror("up error\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int set_sem(key_t shm_key , int shm_num , int shm_flg){
    /*
      int i , shm_id;
      char *shm_buf;
      if((shm_id = get_ipc_id("/proc/sysvipc/shm" , shm_key)) < 0){
      if((shm_id = shmget(shm_key,shm_num,shm_flg)) < 0){
      perror("shareMemory set error\n");
      exit(EXIT_FAILURE);
      }
      if((shm_buf = (char *) shmat(shm_id , 0 , 0)) < (char *) 0){
      perror("get shareMemory error\n");
      exit(EXIT_FAILURE);
      for (i = 0; i < shm_num; i++) {
      shm_buf[i] = 0;
      }
      }else if((shm_buf = (char*) shmat(shm_id , 0 , 0)) < (char*)0){
      perror("get shareMemory error\n");
      exit(EXIT_FAILURE);
      }
      }
      return *shm_buf;
    */
    int sem_id;
    Sem_uns sem_arg;
    if((sem_id = get_ipc_id("/proc/sysvipc/sem" , sem_key)) < 0){
        perror("Error for semaphore.\n");
        exit(EXIT_FAILURE);
    }
    sem_arg.val = sem_val;
    if(semctl(sem_id,0,SETVAL,sem_arg) < 0){
        perror("Error for semaphore.\n");
        exit(EXIT_FAILURE);
    }
    return sem_id;
}

char * set_shm(key_t shm_key , int shm_num , int shm_flag){
    int i , shm_id;
    char * shm_buf;
    if((shm_id = get_ipc_id("/proc/sysvipc/shm" , shm_key)) < 0){
        if((shm_id = shmget(shm_key, shm_num, shm_flg)) < 0){
            perror("Error for semaphore.\n");
            exit(EXIT_FAILURE);
        }
        if((shm_buf = (char *) shmat(shm_id,0,0)) < (char*)0){
            perror("get shareMemory error\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < shm_num; i++) {
            shm_buf[i] = 0;
        }
    }else if((shm_buf = (char *)shmat(shm_id,0,0)) < (char*)0){
        perror("get shareMemory error \n");
        exit(EXIT_FAILURE);
    }
    return shm_buf;
}

int set_msq(key_t msq_key , int msq_flg){
    int msq_id;
    /*
    if(((msq_id = get_ipc_id("/proc/sysvipc/msg" , msq_key)) < 0){
            /*
            if(((msg_id = messget(msq_key , msq_flg)) < 0){
                    perror("messageQueue set error\n");
                    exit(EXIT_FAILURE);
                }
        }
        }
*/
    if((msq_id = get_ipc_id("/proc/sysvipc/msg" , msq_key)) < 0){
        if((msq_id = msgget(msq_key , msq_flg)) < 0){
            perror("messageQueue Error for get the memory error\n");
            exit(EXIT_FAILURE);
        }
    }
    return msq_id;
}

void sigcat(){
    semctl(prod_sem , 0 , IPC_RMID);
    semctl(cons_sem , 0 , IPC_RMID);
    semctl(pmtx_sem , 0 , IPC_RMID);
    semctl(cmtx_sem , 0 , IPC_RMID);

    shmdt(cget_ptr);
    shmdt(pput_ptr);
    shmdt(buff_ptr);
    exit(EXIT_SUCCESS);
}

void ipc_init(){
    buff_key = 101;
    buff_num = 8;
    pput_key = 102;
    cget_key = 103;
    pput_num = 1;
    cget_num = 1;
    shm_flg = IPC_CREAT | 0644;

    prod_key = 201;
    pmtx_key = 202;
    cons_key = 301;
    cmtx_key = 302;
    sem_flg = IPC_CREAT | 0644;

    sem_val = buff_num;
    prod_sem = set_sem(prod_key , sem_val , sem_flg);

    sem_val = 0;
    cons_sem = set_sem(cons_key , sem_val , sem_flg);

    sem_val = 1;
    pmtx_sem = set_sem(pmtx_key , sem_val , sem_flg);

    sem_val = 1;

    cmtx_sem = set_sem(cmtx_key , sem_val , sem_flg);

}

int main(int argc , char ** argv){

    return EXIT_SUCCESS;
}
