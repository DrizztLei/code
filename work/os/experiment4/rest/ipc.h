#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

#define BUFSZ 256

typedef void(*sighandler_t)(int);

void sigcat(void);

int get_ipc_id(char *proc_file , key_t key);

char * set_shm(key_t shm_key , int shm_num , int shm_flag);

int set_msg(key_t msq_key , int msq_flag);

int set_sem(key_t sem_key , int sem_val , int sem_flag);

int P(int sem_id);
int V(int sem_id);

typedef union semuns{
    int val;
} Sem_uns;

typedef union msgbuf{
    long mytype;
    char mtext[1];
}Msg_buf;

key_t buff_key;
int buff_num;
char *buff_ptr;

key_t pput_key;
int pput_num;
int *pput_pir;

key_t cget_key;
int cget_num;
int *cget_ptr;
key_t prod_key;

key_t pmtx_key;
int prod_sem;
int pmtx_sem;

key_t cons_key;
key_t cmtx_key;
int cons_sem;
int cmtx_sem;

int sem_val;
int sem_flg;
int shm_flg;
int reate;
