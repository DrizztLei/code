/*
 * File: Agent.c
 * Author: Caspar Zhang
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sem.h>
#include "PV.h"

int main(int argc, char *argv[])
{
    /*
     * 0 - Paper and matches
     * 1 - Matches and tobacco
     * 2 - Tobacco and paper
     */

    char *ingredient[3] = {
        "Paper and matches",
        "Matches and tobacco",
        "Tobacco and paper"};
    int ingred_type;
    int semid, i;

    srand((unsigned)time(NULL));

    /* Puts out the Agent's information */
    fprintf(stdout, "I'm the Agent.\n" );

    /*
     * Create a new semaphore set which has 4 semaphores in it.
     * The first 3 semaphores are the Smokers' state,
     * the last one is the Agent's state
     */

    if ((semid = semget(SEM_KEY, 4, IPC_CREAT|0660)) < 0)
        ERR_AND_EXIT("semget");
    for (i = 0; i < 4; ++i)
        if (semctl(semid, i, SETVAL, 0) < 0)
            ERR_AND_EXIT("semctl");

    /*
     * The procedures are shown in below:
     * 1. Offer Ingredients
     * 2. V(Smoker_i)
     * 3. P(Agent)
     * 4. Go to 1 and repeat
     */
    while (1)
    {
        /* Offer the ingredients randomly*/
        ingred_type = rand() % 3;
        fprintf(stdout, "Agent%d: I offered %s, waiting for the smoker.\n",
                ingred_type, ingredient[ingred_type]);
        sleep(5);
        /*  Wake up the specified smoker */
        if (V(semid, ingred_type) < 0) ERR_AND_EXIT("V failed");
        /* Wait for smoker to roll and smoke */
        if (P(semid, 3) < 0) ERR_AND_EXIT("P failed");
    }

    return 0;
}
