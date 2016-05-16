#ifndef RECEIVER_CPP
#define RECEIVER_CPP

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <string>

using namespace std;

class Receiver{
public:
    explicit Receiver(){};

    void ps(string argv , string object){
        pid_t ps = fork();
        if(ps < 0){
            perror("Error for get the pid failed.\n");
            exit(EXIT_FAILURE);
        }else if(ps > 0){
            waitpid(ps , 0 , 0);
        }else{
            execl("/bin/ps" , "ps" , argv.length() == 0 ? NULL: argv.c_str() , object.length() == 0 ? NULL : object.c_str(), NULL);
            exit(EXIT_SUCCESS);
        }
    }

    void ls(string argv , string object){
        pid_t ls = fork();
        if(ls < 0){
            perror("Error for get the pid failed.\n");
            exit(EXIT_FAILURE);
        }else if(ls > 0){
            waitpid(ls , 0 , 0);
        }else{
            execl("/bin/ls" ,"ls" , argv.length() == 0 ? NULL: argv.c_str() , object.length() == 0 ? NULL : object.c_str(), NULL);
            exit(EXIT_SUCCESS);
        }
    }

    void lsblk(string argv , string object){
        pid_t lsblk = fork();
        if(lsblk < 0){
            perror("Error for get the pid failed.\n");
            exit(EXIT_FAILURE);
        }else if(lsblk > 0){
            waitpid(lsblk , 0 , 0);
        }else{
            execlp("/bin/" , "lsblk" , argv.length() == 0 ? NULL: argv.c_str() , object.length() == 0 ? NULL : object.c_str(), NULL);
            exit(EXIT_SUCCESS);
        }
    }


    void htop(string argv , string object){
        pid_t htop = fork();
        if(htop < 0){
            perror("Error for get the pid failed.\n");
            exit(EXIT_FAILURE);
        }else if(htop > 0){
            waitpid(htop , 0 , 0);
        }else{
            execlp("/usr/bin/htop" , "htop" , argv.length() == 0 ? NULL: argv.c_str() , object.length() == 0 ? NULL : object.c_str(), NULL);
            exit(EXIT_SUCCESS);
        }
    }


    void make(string argv , string object){
        pid_t make = fork();
        if(make < 0){
            perror("Error for get the pid failed.\n");
            exit(EXIT_FAILURE);
        }else if(make > 0){
            waitpid(make , 0 , 0);
        }else{
            execlp("/bin/make" , "make" ,argv.length() == 0 ? NULL: argv.c_str() , object.length() == 0 ? NULL : object.c_str(), NULL);
            exit(EXIT_SUCCESS);
        }
    }

    void os_3(string argv, string object){
        pid_t make = fork();
        if(make < 0){
            perror("Error for get the pid failed.\n");
            exit(EXIT_FAILURE);
        }else if(make > 0){
            waitpid(make , 0 , 0);
        }else{
            execlp("/home/elvis/work/os/experiment3/os_3" , "os_3" ,argv.length() == 0 ? NULL: argv.c_str() , object.length() == 0 ? NULL : object.c_str(), NULL);
            exit(EXIT_SUCCESS);
        }
    }
};
#endif
