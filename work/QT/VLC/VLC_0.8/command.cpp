#ifndef COMMAND_CPP
#define COMMAND_CPP

#include <stdio.h>
#include <stdlib.h>
#include "receiver.cpp"

class Command{
public:
    explicit Command(Receiver * rece , string _argv = "" , string _object = ""){
        receiver = rece;
        argv = _argv;
        object = _object;
    }
    virtual ~Command(){}
    virtual void execute() = 0;
    virtual void undo() = 0;
protected:
    Receiver * receiver;
    string argv , object;
};

#endif
