#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;
int main(int argc , char ** argv){
    /*
      int status = 0;
      pid_t ls = fork();
      pid_t ps = fork();
      if(ls < 0){
      cout << "Error for create the process . " << endl;
      return EXIT_FAILURE;
      }else if(ps == 0 && ls == 0){
      return EXIT_SUCCESS;
      }else if(ps == 0){
      waitpid(ls,NULL,0);
      cout << "when run the commmand . the pid is : " << getpid() << endl;
      system("ps");
      cout << "now the pid is : " << getpid() << endl;
      cout << "we run the command over " << endl;
      if(status != 0){
      cout << "system error" << endl;
      return EXIT_FAILURE;
      }
      return EXIT_SUCCESS;
      }else if(ls == 0) {
      cout << "before wait the ps is : " << ps << endl;
      waitpid(ps-1,NULL,0);
      cout << "I'm waitting for you ? " << endl;
      system("ls");
      cout << "now the ls command is over" << endl;
      if(status != 0) {
      cout << "system error" << endl;
      return EXIT_FAILURE;
      }
      return EXIT_SUCCESS;
      }else {
      cout << "the father is wait for ls : " << ls << "\t ps : " << ps << endl;
      waitpid(ls,NULL,0);
      if(status != 0) {
      cout << "system error" << endl;
      return EXIT_FAILURE;
      }
      waitpid(ps,NULL,0);
      if(status != 0) {
      cout << "system error" << endl;
      return EXIT_FAILURE;
      }
      }
      return EXIT_SUCCESS;
    */
    /*
      pid_t ls = fork();
      if(ls < 0){
      cout << "Error for process " << endl;
      return EXIT_FAILURE;
      }else if(ls > 0){
      pid_t ps = fork();
      if(ps == 0){
      char * argv[] = {"ps",NULL,NULL,NULL};
      char * envp[]= {"PATH=/bin",NULL};
      //execve("/bin/ps" , argv , envp);
      system("ps");
      return EXIT_SUCCESS;
      }else {
      waitpid(ps,0,0);
      }
      }else{
      char * argv[] = {"ls",NULL,NULL,NULL};
      char * envp[] = {"PATH=/bin",NULL};
      //execve("/bin/ls" , argv , envp);
      //wait(NULL);
      system("ls");
      return EXIT_SUCCESS;
      }
    */
    /*
      else if(ls == 0) {
      //system("ls -alsh");
      char * argv[] = {"ls","-al","/etc/passwd",NULL};
      char * envp[] = {"PATH=/bin",NULL};
      execve("/bin/ls" , argv , envp);
      return EXIT_SUCCESS;
      }
    */
    /*
      pid_t ls = fork();
      if(ls < 0){
      cout << "Error for process " << endl;
      return EXIT_FAILURE;
      }else if(ls != 0){
      pid_t ps = fork();
      if(ps < 0) {
      cout << "Error for process " << endl;
      return EXIT_FAILURE;
      }else if(ps == 0){
      char * argv[] = {"ps",NULL,NULL,NULL};
      char * envp[]= {"PATH=/bin",NULL};
      //execve("/bin/ps" , argv , envp);
      system("ps");
      }else{
      waitpid(ps,0,0);
      //waitpid(ls,0,0);
      }
      }else if(ls == 0){
      char * argv[] = {"ls","-al","/etc/passwd",NULL};
      char * envp[] = {"PATH=/bin",NULL};
      execve("/bin/ls" , argv , envp);
      }
    */
    pid_t ls = fork();
    pid_t ps = fork();
    //cout << "------------" << endl << "pid : " << getpid() << "\t father's pid : " << getppid() <<"\t" << "ls : " << ls << "\t ps : " << ps << endl << "------------" << endl;
    if(ps == 0){
        //if(ls == 0){
        //}
        //else {
        //}
        if(ls == 0){
           system("ps");
            //return EXIT_FAILURE;
            return EXIT_SUCCESS;
        }else{
            //return EXIT_SUCCESS;
            return EXIT_FAILURE;
        }
    }else{
        /*
          if(ps == 0){
          //system("ps");
          }else if(ls == 0){
          waitpid(ps,0,0);
          //system("ls");
          return EXIT_SUCCESS;
          }else{
          waitpid(ls, 0, 0);
          waitpid(ps, 0, 0);
          }
        */
        if(ls == 0){
            waitpid(ps,0,0);
            system("ls");
        }else if(ps != 0 && ls != 0){
            waitpid(ps,0,0);
            waitpid(ls,0,0);
        }
    }
    /*
      if(ps == 0){
      char * argv[] = {"ps",NULL,NULL,NULL};
      char * envp[]= {"PATH=/bin",NULL};
      //execve("/bin/ps" , argv , envp);
      system("ps");
      }else if(ps > 0){
      waitpid(ps,0,0);
      }
    */
    return EXIT_SUCCESS;
}
