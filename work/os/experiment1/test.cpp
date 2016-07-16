#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signo)
{
    printf("recv the signal from parent process\n");
}

int main()
{
    pid_t pid;

    pid = fork();

    switch(pid)
    {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        printf("in the child\n");
        signal(SIGCONT, handler);
        pause();
        printf("child weakup\n");
        break;
    default:
        printf("in the parent\n");
        sleep(5);
        kill(pid, SIGCONT);
        sleep(5);
        printf("parent weakup\n");
        break;
    }
    printf("bye..\n");

    exit(0);
}
