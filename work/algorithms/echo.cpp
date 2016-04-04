#include <iostream>
using namespace std;
template <typename T>
struct Node
{
    Node * prev , * next;
    T info;
    Node(T info = NULL , Node<T> * & pre = NULL , Node<T> * & nex = NULL){this -> info = info ; prev = pre ; nex = next;}
};


template <typename T>
class Linear
{
public:
    Linear();
    void insert(Node<T> * & in );
    void remove(Node<T> * & out);
    int find(T info);
    void add(T info);
    virtual ~Linear();
};
