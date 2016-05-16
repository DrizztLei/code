#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void *thread(void *ptr)
{
    for(int i = 0;i < 3;i++) {
        sleep(1);
        cout << "This is a pthread." << endl;
    }
    return 0;
}

int main() {
    pthread_t id;

    int ret = pthread_create(&id, NULL, thread, NULL);

    if(ret) {
        cout << "Create pthread error!" << endl;
        return 1;
    }

    for(int i = 0;i < 3;i++) {
        cout <<  "This is the main process." << endl;
        sleep(1);
    }

    pthread_join(id, NULL);

    return 0;
}
