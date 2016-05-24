/*
 * File: PV.c
 * Author: Caspar Zhang
 */
#include "PV.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>

int P(int semid, int sem_index)
{
    struct sembuf buf;

    buf.sem_num = sem_index;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1)
        return -1;

    return 0;
}

int V(int semid, int sem_index)
{
    struct sembuf buf;

    buf.sem_num = sem_index;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1)
        return -1;

    return 0;
}
