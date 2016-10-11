#include "Client.cpp"

int main(int argc , char ** argv){
    Client * client = new Client();
    client -> Test();
    delete client;
    return EXIT_SUCCESS;
}
