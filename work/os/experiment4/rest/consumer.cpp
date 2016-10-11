#include "ipc.h"

int main(int argc , char ** argv){
    if(argv[1] != NULL) rate = atoi(argv[1]);
    else rate = 1;
    signal(SIGINT , (sighandler_t)sigcat);
    while(1){
        P(cons_sem);
        P(cmtx_sem);
        printf("%d consumer get: %c from Buffer[%d]\n" , getpid() , buff_ptr[*cget_ptr] , *cget_ptr);
        sleep(rate);
        *cget_ptr = (*cget_ptr+1) % buff_num;
        V(cmtx_sem);
    }
    return EXIT_SUCCESS;
}
