#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>


void handler(int signal){
    return;
}

void set_father(int signal){
    printf("TESTING \n");
    return;
}

void receive_son(int signal){
    if(signal == SIGTSTP){
        printf("get the signal : SIGTSTP \n");
        printf("get the pid for son : %d\n" , getpid());
        setpriority(PRIO_PROCESS , getpid() , getpriority(PRIO_PROCESS,getpid())-1);
    }else if(signal == SIGINT){
        /*
        printf("get the signal : SIGINT \n");
        printf("get the pid for father : %d\n" , getpid());
        */
        printf("I'm the son , ignore the signal.\n");
    }else{
        perror("Error for signal not found.\n");
    }
    return;
}

void receive_father(int signal){
    if(signal == SIGTSTP){
        //printf("get the signal : SIGTSTP \n");
        //printf("get the pid for son : %d\n" , getpid());
        printf("I'm the father . ignore the signal.\n");
    }else if(signal == SIGINT){
        printf("get the signal : SIGINT \n");
        printf("get the pid for father : %d\n" , getpid());
        setpriority(PRIO_PROCESS , getpid() , getpriority(PRIO_PROCESS,getpid())+1);
    }else{
        perror("Error for signal not found.\n");
    }
    return;
}

int pipeline[2];

int main(int argc , char ** argv){
    //struct sched_param p[3];
    if(pipe(pipeline) < 0){
        perror ("Error for create the pipe");
        return EXIT_FAILURE;
    }
    pid_t son = fork();
    if(son < 0){
        perror ("Error for create the pid failed.\n");
        return EXIT_FAILURE;
    }
    else if(son == 0){
        //The code for the son
        int x = 0;
        write(pipeline[1] , &x , sizeof(x));
        signal(SIGCONT,handler);
        pause();
        /*
        printf("Get the son sched : %d\n" , sched_getscheduler(getpid()));
        printf("Get the priority : %d\n" , getpriority(PRIO_PROCESS, getpid()));
        setpriority(PRIO_PROCESS,getpid() , 5);
        printf("Adjust the priority %d \n", getpriority(PRIO_PROCESS,getpid()));
        */
        signal(SIGTSTP, receive_son);
        signal(SIGINT, receive_son);
        while(true){
            sleep(1);
            //printf("information from son . \n");
            printf("%d for the pid , %d for the priority , %d for the schedmode.\n" , getpid() , getpriority(PRIO_PROCESS, getpid()) ,sched_getscheduler(getpid()));
        }
    }else{
        //The code for the father.
        int x;
        read(pipeline[0] , &x , sizeof(x));
        kill(son,SIGCONT);
        close(pipeline[0]);
        close(pipeline[1]);
        /*
        printf("Get the father sched : %d\n" , sched_getscheduler(getpid()));
        printf("Get the priority : %d\n" , getpriority(PRIO_PROCESS, getpid()));
        */
        signal(SIGINT , receive_father);
        signal(SIGTSTP , receive_father);
        while(true){
            sleep(1);
            //printf("information from father . \n");
            printf("%d for the pid , %d for the priority , %d for the schedmode.\n" , getpid() , getpriority(PRIO_PROCESS, getpid()) ,sched_getscheduler(getpid()));
        }
        waitpid(son,0,0);
    }
    return EXIT_SUCCESS;
}
