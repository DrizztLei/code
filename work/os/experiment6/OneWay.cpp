#ifndef _EXP_H
#define _EXP_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <error.h>
#include <cstring>
#include <iostream>

union semun
{
    int val;
    struct semid_ds * buf;
    unsigned short * array;
};

int get_current_number();
void set_current_number(int value);
int get_current_direction();
void set_current_direction(int value);
int get_flag();
void set_flag(int value);
class Sem;
class Lock;
void adjust(int north , int sourth , int direct , Sem * queue_north, Sem * queue_sourth , Lock * private_lock , int max);
void adjust_less_max(int north , int sourth , int direct ,Sem * queue , Sem * queue_sourth , Lock * private_lock , int max);
void setlimit(int value);
bool islimit();
void addlimit(int value = 1);

int limit;

using namespace std;

enum DIRECTION
    {
        NORTH,
        SOURTH
    };
class Sem
{
public:
    Sem(int semid_key , int index = 0)
    {
        this -> index = index;
        id = semget(semid_key , 1 , IPC_CREAT | IPC_EXCL);
    }
    ~Sem()
    {
        if(semctl(id, 1 , IPC_RMID , NULL))
        {
            perror("Error semctl of rmid");
            exit(EXIT_FAILURE);
        }
    }
    int P()
    {
        struct sembuf buf = {index , -1 , SEM_UNDO};
        if(semop(id , &buf , 1))
        {
            perror("Error for operation P");
            exit(EXIT_FAILURE);
        }
        return EXIT_SUCCESS;
    }
    int V()
    {
        struct sembuf buf = {index , 1 , SEM_UNDO};
        if(semop(id , &buf , 1))
        {
            perror("Error for operation V");
            exit(EXIT_FAILURE);
        }
        return EXIT_SUCCESS;
    }
    void setValue(int value)
    {
        union semun sem;
        sem.val = value;
        if(semctl(id , index , SETVAL , sem) == -1)
        {
            perror("Error for set the value");
            exit(EXIT_FAILURE);
        }
    }
    int getValue()
    {
        union semun sem;
        int temp;
        if((temp = semctl(id, index, GETVAL , &sem)) == -1)
        {
            perror("Error for get the value");
            exit(EXIT_FAILURE);
        }
        return temp;
    }
private:
    int id , index;
};

class Lock
{
public:
    Lock(Sem * sem)
    {
        this->sem = sem;
    }
    ~Lock()
    {

    }
    void lock()
    {
        this->sem->P();
    }
    void unlock()
    {
        this->sem->V();
    }
private:
    Sem * sem;
};

class Condition
{
public:
    Condition(Sem * sem_sourth , Sem * sem_north , int max)
    {
        this->queue_sourth = sem_sourth;
        this->queue_north = sem_north;
        this->max = max;
        current_num = 0;
        current_direction = -1;
    }
    ~Condition()
    {

    }
    void Wait(Lock* lock , int direct)
    {
        private_lock = lock;
        current_num = get_current_number();
        current_direction = get_current_direction();
        if(current_num == 0)
        {
            int flag = get_flag();
            if(flag == -1)
            {
                set_flag(direct);
                set_current_number(1);
                set_current_direction(direct);
                addlimit();
                if(islimit())
                {
                    set_flag(direct == NORTH ? SOURTH : NORTH);
                }
                lock->unlock();
            }
            else if(flag == direct)
            {
                set_flag(direct);
                set_current_number(1);
                set_current_direction(direct);
                addlimit();
                if(islimit())
                {
                    set_flag(direct == NORTH ? SOURTH : NORTH);
                }
                lock->unlock();
            }
            else
            {
                lock->unlock();
                if(direct == NORTH)
                {
                    queue_north->P();
                    lock->lock();
                }
                else
                {

                }
            }
        }
        else if(current_num < max)
        {
            if(current_direction != direct)
            {
                lock->unlock();
                if(direct == NORTH)
                {
                    queue_north->P();
                    lock->lock();
                    set_current_number(get_current_number()+1);
                    set_current_direction(direct);
                    lock->unlock();
                }
                else
                {
                    queue_sourth->P();
                    lock->lock();
                    set_current_number(get_current_number()+1);
                    set_current_direction(direct);
                    lock->unlock();
                }
            }
            else
            {
                if(direct == NORTH)
                {
                    int flag = get_flag();
                    if(flag == direct)
                    {
                        set_current_number(get_current_number()+1);
                        set_current_direction(direct);
                        lock->unlock();
                    }
                    else
                    {
                        lock->unlock();
                        queue_north->P();
                        lock->lock();
                        set_current_number(get_current_number()+1);
                        set_current_direction(direct);
                        lock->unlock();
                    }
                }
                else
                {
                    int flag = get_flag();
                    if(flag == direct)
                    {
                        set_current_number(get_current_number()+1);
                        set_current_direction(direct);
                        lock->unlock();
                    }
                    else
                    {
                        lock->unlock();
                        queue_sourth->P();
                        lock->lock();
                        set_current_number(get_current_number()+1);
                        set_current_direction(direct);
                        lock->unlock();
                    }
                }
            }
        }
        else if(current_num == max)
        {
            if(direct == NORTH)
            {
                lock->unlock();
                queue_north->P();
                lock->lock();
                set_current_number(get_current_number()+1);
                set_current_direction(direct);
                lock->unlock();
            }
            else
            {
                lock->unlock();
                queue_sourth->P();
                lock->lock();
                set_current_number(get_current_number()+1);
                set_current_direction(direct);
                lock->unlock();
            }
        }
        else
        {
            cout << "Error for unexception value of car number." << endl;
        }
    }
    void Signal(int direct)
    {
        int number = get_current_number();
        cout << "current number is : " << number << endl;
        set_current_number(number-1);
        int north = queue_north->getValue();
        int sourth = queue_sourth->getValue();
        if(direct != get_current_direction())
        {
            cout << "Error for direction error ." << endl;
            exit(EXIT_FAILURE);
        }
        if(number == 1)
        {
            adjust(north , sourth , direct , queue_north , queue_sourth ,private_lock ,  max);
        }
        else if(number < max)
        {
            adjust_less_max(north , sourth , direct , queue_north , queue_sourth , private_lock ,  max);
        }
        else if(number == max)
        {
            if(north > 0 || sourth > 0)
            {
                cout << "Error for value > 0" << endl;
                exit(EXIT_FAILURE);
            }
            if(direct == NORTH)
            {
                if(north < 0 && sourth == 0)
                {
                    queue_north->V();
                }
                else
                {
                    set_flag(SOURTH);
                }
            }
            else if(direct == SOURTH)
            {
                if(sourth < 0 && north == 0)
                {
                    queue_sourth->V();
                }
                else
                {
                    set_flag(NORTH);
                }
            }
            else
            {
                cout << "Error for dirction unknow . " << endl;
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            cout << "Error for check the number ." << endl;
        }
        private_lock->unlock();
    }
private:
    Sem * queue_sourth;
    Sem * queue_north;
    int current_num , current_direction , max;
    Lock * private_lock;
};

class OneWay{
public:
    OneWay(int rate , int max)
    {
        this->rate = rate;
        this->maxCars = max;
        key_t key_north = ftok("./" , 0x10);
        key_t key_sourth = ftok("./" , 0x12);
        Sem * sem_north = new Sem(key_north);
        sem_north->setValue(0);
        Sem * sem_sourth = new Sem(key_sourth);
        sem_sourth->setValue(0);
        condition = new Condition(sem_north , sem_sourth , max);
        key_t key_lock = ftok("./" , 0x14);
        Sem * sem_lock = new Sem(key_lock);
        sem_lock->setValue(max);
        lock = new Lock(sem_lock);
    }
    ~OneWay()
    {

    }
    void Arrive(int direct)
    {
        lock->lock();
        condition->Wait(lock , direct);
    }
    void Cross(int direct)
    {
        cout << getpid() << " run from the " << direct << " and now there are " << get_current_number() << " cars and the current direction is " << get_current_direction() << endl;;
        sleep(rate);
    }
    void Quit(int direct)
    {
        lock->lock();
        cout << getpid() << " car quits form " << direct << endl;
        condition->Signal(direct);
    }
private:
    int rate;
    int maxCars;
    Condition * condition;
    Lock * lock;
};

int shm_id;

int get_current_number()
{
    int * address = (int *)shmat(shm_id, NULL, 0);
    if((int)(address) == -1)
    {
        cout << "Error for address in shmat ." << endl;
        exit(EXIT_FAILURE);
    }
    int result = address[0];
    shmdt(address);
    return result;
}

void set_current_number(int value)
{
    int * address = (int *)shmat(shm_id, NULL, 0);
    if((int)(address) == -1)
    {
        cout << "Error for address in shmat ." << endl;
        exit(EXIT_FAILURE);
    }
    address[0] = value;
    shmdt(address);
}

int get_current_direction()
{
    int * address = (int *)shmat(shm_id, NULL, 0);
    if((int)(address) == -1)
    {
        cout << "Error for address in shmat ." << endl;
        exit(EXIT_FAILURE);
    }
    int result = address[1];
    shmdt(address);
    return result;
}

void set_current_direction(int value)
{
    int * address = (int *)shmat(shm_id, NULL, 0);
    if((int)(address) == -1)
    {
        cout << "Error for address in shmat ." << endl;
        exit(EXIT_FAILURE);
    }
    address[1] = value;
    shmdt(address);
}

int get_flag()
{
    int * address = (int *)shmat(shm_id, NULL, 0);
    if((int)(address) == -1)
    {
        cout << "Error for address in shmat ." << endl;
        exit(EXIT_FAILURE);
    }
    int result = address[2];
    shmdt(address);
    return result;
}

void set_flag(int value = 0)
{
    int * address = (int *)shmat(shm_id, NULL, 0);
    if((int)(address) == -1)
    {
        cout << "Error for address in shmat ." << endl;
        exit(EXIT_FAILURE);
    }
    address[2] = value;
    shmdt(address);
}

void adjust(int north , int sourth , int direct , Sem * queue_north , Sem * queue_sourth , Lock * private_lock , int max)
{
    int flag = get_flag();
    if(north > 0 || sourth > 0 || (flag != NORTH && flag != SOURTH))
    {
        cout << "Error for value or direction ." << endl;
        cout << north << endl << sourth << flag << endl;
        exit(EXIT_FAILURE);

    }
    if(direct == NORTH)
    {
        if(north == 0 && sourth == 0)
        {
            set_flag(-1);
            return;
        }
        else if(north < 0 && sourth == 0)
        {
            set_flag(NORTH);
            for(int i = 0 ; i < - north && i < max ; i++)
            {
                queue_north->V();
            }
        }
        else if(north == 0 && sourth < 0)
        {
            set_flag(SOURTH);
            for(int i = 0 ; i < -sourth && i < max ; i++)
            {
                queue_sourth->V();
            }
        }
        else
        {
            //block for the cars from all aspects.
            if(direct == flag)
            {
                for(int i = 0 ; i < -north && i < max ; i++)
                {
                    queue_north->V();
                }
            }
            else
            {
                for(int i = 0 ; i < -sourth && i < max ; i++)
                {
                    queue_sourth->V();
                }
            }
        }
    }
    else
    {
        //code for direction is sourth.
        if(north == 0 && sourth == 0)
        {
            set_flag(-1);
            return;
        }
        else if(sourth < 0 && north == 0)
        {
            set_flag(sourth);
            for(int i = 0 ; i < -sourth && i < max ; i++)
            {
                queue_sourth->V();
            }
        }
        else if(sourth == 0 && north < 0)
        {
            set_flag(NORTH);
            for(int i = 0 ; i < -north && i < max ; i++)
            {
                queue_north->V();
            }
        }
        else
        {
            //block for the cars from all aspects.I think that it should depend on the flag.
            if(direct == flag)
            {
                for(int i = 0 ; i < -sourth && i < max ; i++)
                {
                    queue_sourth->V();
                }
            }
            else
            {
                for(int i = 0 ; i < - north && i < max ; i++)
                {
                    queue_north->V();
                }
            }
        }
    }
    private_lock->unlock();
}

void adjust_less_max(int north , int sourth , int direct ,Sem * queue_north , Sem * queue_sourth , Lock * private_lock , int max)
{
    int flag = get_flag();
    if(north > 0 || sourth > 0 || (flag != NORTH && flag != SOURTH) )
    {
        cout << "Error for value or flag ." << endl;
        cout << north << endl << sourth << flag << endl;
        exit(EXIT_FAILURE);
    }

    if(flag == direct)
    {
        //before the limit
        if(direct == NORTH)
        {
            if(north < 0 && sourth == 0)
            {
                for(int i = get_current_number() , j = 0 ; i < max && j < -north  ; i++ , j++)
                {
                    queue_north->V();
                }
            }
            else if(north < 0 && sourth < 0)
            {
                for(int i = get_current_number() , j = 0 ; i < max && j < -north ; i++ , j++)
                {
                    queue_north->V();
                }
            }
            else if(north == 0 && sourth <= 0)
            {
                //do nothing here.
            }
        }
        else
        {
            if(sourth < 0 && north == 0)
            {
                for(int i = get_current_number() , j = 0 ; i < max && j < -sourth  ; i++ , j++)
                {
                    queue_sourth->V();
                }
            }
            else if(north < 0 && sourth < 0)
            {
                for(int i = get_current_number() , j = 0 ; i < max && j < -sourth ; i++ , j++)
                {
                    queue_sourth->V();
                }
            }
            else if(north == 0 && sourth <= 0)
            {
                //do nothing here.
            }
        }
    }
    else
    {
        //when the flag != direct it means that another aspect needed here,
        //so we should ignore the request of this aspect.
    }
    private_lock->unlock();
}

bool islimit()
{
    int * address = (int *)shmat(shm_id, NULL, 0);
    if((int)(address) == -1)
    {
        cout << "Error for address in shmat ." << endl;
        exit(EXIT_FAILURE);
    }
    bool flag = address[3] < limit ? false : true;
    shmdt(address);
    return flag;
}

void setlimit(int value)
{
    limit = value;
    int * address = (int *)shmat(shm_id, NULL, 0);
    if((int)(address) == -1)
    {
        cout << "Error for address in shmat ." << endl;
        exit(EXIT_FAILURE);
    }
    address[3] = 0;
    shmdt(address);
}

void addlimit(int value = 1){
    int * address = (int *)shmat(shm_id, NULL, 0);
    if((int)(address) == -1)
    {
        cout << "Error for address in shmat ." << endl;
        exit(EXIT_FAILURE);
    }
    address[3] += value;
    shmdt(address);
}


int main(int argc , char ** argv)
{
    srand((unsigned)(time(NULL)));
    set_flag(-1);
    key_t key_id = ftok("./" , 0x20);
    shm_id = shmget(key_id, 2048, IPC_CREAT);
    OneWay * way;
    int number = 6;
    int rate , max;
    rate = (argc > 1) ? atoi(argv[1]) : 1;
    max = (argc > 2) ? atoi(argv[2]) : 1;
    setlimit(max <= 1 ? 1 : max / 2);
    cout << "Rate for " << rate << " and max for " << max << endl;
    way = new OneWay(rate , max);
    int i = 0;
    while(i < number)
    {
        sleep(rate);
        pid_t son = fork();
        if(son < 0)
        {
            perror("Error in frok()");
        }
        else if(son == 0)
        {
            {
                while(1)
                {
                    int aspect = random()%2 == 0 ? NORTH : SOURTH;
                    way->Arrive(aspect);
                    way->Cross(aspect);
                    way->Quit(aspect);
                }
            }
            break;
        }
        else if(son > 0)
        {
            i++;
        }
    }
    wait(NULL);
    return EXIT_SUCCESS;
}
#endif
