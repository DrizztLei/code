#include <iostream>
using namespace std;
struct node{
    int data;
    node * next;
};

int main(int argc ,char ** argv){
    node * head , * p , * q;
    int n;
    cout<< "input :" <<endl;
    cin >> n;
    head = p = new node;
    p->data = 0;
    for(int i = 1 ; i < n;i++){
        q = new node;
        q->data=i;
        p->next=q;
        p=q;
    }
    p->next = head;
    q = head;
    while(q->next != q){
        p=q->next;
        p->next = q->next;
        cout << q->next->data;
        delete q;
        q=p->next;
    }
    cout << "The rest is :" << q->next->data <<endl;
    return 0;
}
