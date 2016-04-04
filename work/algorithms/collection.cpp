#include <iostream>
using std::cout;
using std::endl;
using std::cin;
template<class T>
struct node {
    T data;
    node * next;
};

template<class T>
class stack{
private:
    node<T> * head;
public:
    bool isEmpty();
    void insert(T);
    void he();
};
int main(int argc , char ** argv){
   return 0;
}
