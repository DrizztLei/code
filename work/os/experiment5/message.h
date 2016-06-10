#ifndef _MESSAGE_H
#define _MESSAGE_H

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

struct msgbuf{
    long mtype;
    char mtext[1];
};

#define NUM 4
int  _pipe[2];

int P(int semid , int index);

int V(int semid , int index);
int msg_length(key_t msgid);

key_t get_key(char const * const address , int code){
    return ftok(address , code);
}

int const SIZE = sizeof(char);


#endif
