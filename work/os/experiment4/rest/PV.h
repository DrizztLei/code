/*
 * File: PV.h
 * Author: Caspar Zhang
 */
#ifndef _PV_H
#define _PV_H

#define SEM_KEY 0x12345678

#define ERR_AND_EXIT(arg) do { \
perror(arg); \
exit(1); \
} while(0)

int P(int semid, int sem_index);
int V(int semid, int sem_index);

#endif /* _PV_H */
