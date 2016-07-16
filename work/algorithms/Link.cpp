#include <iostream>
#include <exception>
using std::cout;
using std::cin;
using std::endl;
template<class T>
class Link
{
public:
  struct node{
    T info;
    node * prev , * next;
  };
  node *  Node;
public:
  ~Link();
  Link(T data , int position);
  Link(T data);
  Link();
  void add();
  bool insert(int position);
  bool remove(int position);
  int search(T target);
  bool init();
};
template<class T>
Link<T> :: Link(T data){
  if(Node == NULL){
    Node = new node;
    Node->info = data;
    Node->next = Node->prev = NULL;
    return ;
  }
  node * temp =  Node;
  while(temp -> next != NULL){
    temp = temp -> next;
  }
  temp -> next = new node;
  temp -> next -> info = data;
  temp -> next -> prev = temp;
  temp -> next -> next = NULL;
	
}

template<class T>
Link<T> :: Link(){
  Node = new node;
  Node->prev = Node->next = NULL;
}

template<class T>
Link<T> :: Link(T data , int position){
  try{
    int count = 0;
    node * temp = & Node;
    for(int i = 0 ; i < position ;i++) temp = temp -> next;
    node * result = new node;
    result -> info = data;
    result -> prev = temp;
    result -> next = temp ->next;
    temp -> next = result;
    result -> next -> prev = result;
  }catch(std::exception & e){
    cout << "Exception : " << e.what() << endl;
    throw exception(data);
  }
}

template<class T>
Link<T> :: ~Link(){
  if(Node == NULL) return;
  node * temp =  Node;
  while(Node != NULL){
    temp = Node;
    Node = Node -> next;
    delete temp;
  }
}

int main(int argc ,char ** argv)
{
  Link<int> * link = new Link<int>();
  delete link;
  return 0;
}
