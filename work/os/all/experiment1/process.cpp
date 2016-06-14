#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int pipe_ls[2] , pipe_ps[2];

void handler(int signo)
{
    return;
}

int main(int argc , char ** argv){
    if(pipe(pipe_ls) < 0){
        perror("Error for create the pipe failed.\n");
        return EXIT_FAILURE;
    }
    if(pipe(pipe_ps) < 0){
        perror("Error for create the pipe failed.\n");
        return EXIT_FAILURE;
    }
    pid_t ls = fork();
    if(ls < 0) {
        printf("Error in fork\n");
        return EXIT_FAILURE;
    }else if(ls == 0){
        int x = 0;
        write(pipe_ls[1] , &x , sizeof(x));
        signal(SIGCONT, handler);
        pause();
        char * argv[] = {"ls",NULL,NULL,NULL};
        char * envp[] = {"PATH=/bin",NULL};
        execve("/bin/ls" , argv , envp);
    }else{
        pid_t ps = fork();
        if(ps < 0){
            printf("Error in fork\n");
            return EXIT_FAILURE;
        }else if(ps == 0){
            int x = 0;
            write(pipe_ps[1] , &x , sizeof(x));
            char * argv[] = {"ps",NULL,NULL,NULL};
            char * envp[] = {"PATH=/bin",NULL};
            execve("/bin/ps" , argv , envp);
        }else{
            int x;
            read(pipe_ps[0] , &x , sizeof(x));
            waitpid(ps,0,0);
            read(pipe_ls[0] , &x , sizeof(x));
            kill(ls, SIGCONT);
            waitpid(ls,0,0);
            for (int i = 0; i < 2; i++) {
                close(pipe_ls[i]);
                close(pipe_ps[i]);
            }
        }
    }
    return EXIT_SUCCESS;
}
