#ifndef CLIENT_CPP
#define CLIENT_CPP

#include "Invoker.cpp"
#include "Receiver.cpp"
#include "Command.cpp"
#include "CommandSet.cpp"
#include <iostream>

class Client{
public:
    explicit Client(){};
    void Test(){
        Receiver * rece = new Receiver();

        Command * order_ls = new ls(rece);
        Command * order_ps = new ps(rece);
        Command * order_lsblk = new lsblk(rece);
        Command * order_make = new make(rece);
        Command * order_ls_al = new ls(rece , "-al" , "../");
        Command * order_ps_ef = new ps(rece , "-ef");
        Command * order_os3 = new os_3(rece);
        Command * order_htop = new htop(rece);

        Invoker * invoker = new Invoker();

        invoker -> setCommand(order_ls);
        invoker -> setCommand(order_ps);
        invoker -> setCommand(order_lsblk);
        invoker -> setCommand(order_make);

        if(condition_1){
            invoker -> undo(order_make);
        }

        invoker -> runCommand();

        getchar();

        invoker -> setCommand(order_ls_al);
        invoker -> setCommand(order_ps_ef);

        invoker -> runCommand();

        getchar();

        invoker -> setCommand(order_htop);
        invoker -> setCommand(order_make);
        if(condition_2){
            invoker -> redo(order_make , order_os3);
            invoker -> runCommand();
        }

        delete invoker;
        delete order_ls;
        delete order_ps;
        delete order_lsblk;
        delete order_ps_ef;
        delete order_ls_al;
        delete order_htop;
        delete rece;

    };
    virtual ~Client(){};
private:
    bool condition_1 = true ,  condition_2 = true;
};

#endif
