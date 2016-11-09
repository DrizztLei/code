#ifndef COMMANDSET_CPP
#define COMMANDSET_CPP

#include "Command.cpp"
#include <stdio.h>

class ps:public Command
{
public:
    explicit ps(Receiver * rece , string _argv = "" , string _object = ""):Command(rece , _argv , _object){}
    virtual ~ps(){if(receiver != NULL) delete receiver;}
    void execute(){
        receiver->ps(argv , object);
    }
private:
};

class ls:public Command
{
public:
    explicit ls(Receiver * rece , string _argv = "" , string _object = "" ):Command(rece , _argv, _object){};
    virtual ~ls(){
        if(receiver != NULL) delete receiver;
    };
    void execute(){
        receiver->ls(argv , object);
    };
private:
};

class lsblk:public Command{

public:
    explicit lsblk(Receiver * rece , string _argv = "" , string _object = ""):Command(rece , _argv , _object){};
    virtual ~lsblk(){if(receiver != NULL) delete receiver;};
    void execute(){
        receiver->lsblk(argv , object);
    };
};

class make:public Command{

public:
    explicit make(Receiver * rece , string _argv = "" , string _object = ""):Command(rece , _argv , _object ){};
    virtual ~make(){if(receiver != NULL) delete receiver;};
    void execute(){
        receiver->make(argv , object);
    };
};


class os_3:public Command{

public:
    explicit os_3(Receiver * rece , string _argv = "" , string _object = ""):Command(rece , _argv , _object ){};
    virtual ~os_3(){if(receiver != NULL) delete receiver;};
    void execute(){
        receiver->os_3(argv , object);
    };
};

class htop:public Command{

public:
    explicit htop(Receiver * rece , string _argv = "" , string _object = ""):Command(rece , _argv , _object ){};
    virtual ~htop(){if(receiver != NULL) delete receiver;};
    void execute(){
        receiver->htop(argv , object);
    };
};

#endif
