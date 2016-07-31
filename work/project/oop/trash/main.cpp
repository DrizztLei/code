/*
#include "import.h"

int main(int argc , char ** argv){
    Receiver * rece = new Receiver();
    Command * order_ls = new ls(rece);
    Command * order_ps = new ps(rece);
    Command * order_lsblk = new lsblk(rece);
    Invoker * invoker = new Invoker();
    invoker -> setCommand(order_ls);
    invoker -> setCommand(order_ps);
    invoker -> setCommand(order_lsblk);
    invoker -> runCommand();
    delete invoker;
    delete order_ls;
    delete order_ps;
    delete order_lsblk;
    delete rece;
    return EXIT_SUCCESS;
}
*/
