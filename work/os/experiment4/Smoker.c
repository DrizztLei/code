/*
 * File: Smoker.c
 * Author: Caspar Zhang
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include "PV.h"

int main(int argc, char *argv[])
{
    /*
     * 0 - Tobacco Smoker
     * 1 - Paper Smoker
     * 2 - Matches Smoker
     */
    char *ingredient[3] = {"Tobacco", "Paper", "Matches"};
    int smoker = argv[1][0] - '0';
    int semid;

    /* Puts out the Smoker's information */
    fprintf(stdout, "I'm a smoker. I have %s\n", ingredient[smoker]);

    /* Get the existed semaphore set */
    /* TODO How to create semaphores if smoker process executed first? */
    if ((semid = semget(SEM_KEY, 0, 0)) < 0)
        ERR_AND_EXIT("semget");
    if (semctl(semid, smoker, GETVAL, 0) < 0)
        ERR_AND_EXIT("semctl");

    /*
     * The procedures are shown in below:
     * 1. P(Smoker_i)
     * 2. Get Ingredients, Roll and Smoke
     * 3. V(Agent)
     * 4. Go to 1 and repeat
     */
    while (1)
    {
        /* Wait for the Agent*/
        fprintf(stdout, "%s: I'm waiting for the agent.n", ingredient[smoker]);

        sleep(5);

        if (P(semid, smoker) < 0) ERR_AND_EXIT("P failed");

        /* Roll and smoke */
        fprintf(stdout, "%s: I get the ingredients, I'm rolling and smoking now.n",
                ingredient[smoker]);
        sleep(5);

        /* Wake up Agent */
        if (V(semid, 3) < 0) ERR_AND_EXIT("V failed");
    }

    return 0;
}
