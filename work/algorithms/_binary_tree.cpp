#include <iostream>
#include <vector>
#include <cstring>
#include <exception>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::exception;

template<class E>
struct node{
    E data;
    node<E> * left ;
    node<E> * right;
    node(E info = NULL , node * l = NULL , node * r = NULL){data = info ; left = l ; right = r;}
};

template<class T>
class b_tree{
private:
    node<T> * head;
    int count , hight , _test = 1;
    node<char>* get_answer(char *  mid , char * post , int length);
    node<char>* get_post_answer(char * pre , char * mid , int length);
public:
    void init(node<T> * root  , int n);
    void preOrder();
    void preOrder(node<T> * Node);
    void midOrder();
    void midOrder(node<T> * Node);
    void postOrder();
    void postOrder(node<T> * Node);
    void forward(bool flat = true);
    int calculate_node();
    int calculate_high();
    void show();
    node<T> *& get_head();
    void recycle(node<T> * temp);
    void calculate_preOrder(string mid , string post);
    void calculate_postOrder(string pre , string mid);
    b_tree(int n);
    b_tree(){};
    ~b_tree();
};

template<class T>
int b_tree<T> :: calculate_node(){
    forward(false);
    return count;
}

template<class T>
int b_tree<T> :: calculate_high(){
    forward(false);
    return hight;
}


template<class T>
void b_tree<T> :: recycle(node<T> * temp){
    if(temp == NULL) return;
    recycle(temp -> left);
    recycle(temp -> right);
    delete temp;
}

template<class T>
b_tree<T> :: ~b_tree(){
    recycle(head);
}

template<class T>
b_tree<T> :: b_tree(int n){
    head = new node<T>();
    init(head ,  n-1);
}

template<class T>
void b_tree<T> :: forward(bool flag){
    //vector<int> * temp;
    hight = count = 0;
    vector<node<T>*> left;
    left.push_back(head);
    //cout << left.size() << endl;
    vector<node<T>*> right;
    while(left.size() != 0 || right.size() != 0){
        if(left.size() != 0){
            int size = left.size();
            count += size;
            for(int i = 0 ; i < size ; i++){
                if(flag) cout << "Get info : " << left[i] -> data << endl;
                if(left[i] -> left != NULL)
                    right.push_back(left[i] -> left);
                if(left[i] -> right != NULL)
                    right.push_back(left[i] -> right);
            }
            left.clear();
            hight ++;
        }else{
            int size = right.size();
            count += size;
            for(int i = 0 ; i < size ; i++){
                if(flag) cout << "Get another info : " << right[i] -> data << endl;
                if(right[i] -> left != NULL)
                    left.push_back(right[i] -> left);
                if(right[i] -> right != NULL)
                    left.push_back(right[i] -> right);
            }
            right.clear();
            hight ++;
        }
    }
    left.clear();
    right.clear();
}

template<class T>
void b_tree<T> :: init(node<T> * root , int n){
    if(n == 0) {
        return ;
    }
    root -> left = new node<T>();
    root -> left -> data = _test++;
    cout << "Create the node info for left: " << _test - 1 << endl;
    root -> right = new node<T>();
    root -> right -> data = _test++;
    cout << "Create the node info for right : " << _test - 1 << endl;

    init(root -> left , n - 1);
    init(root -> right , n - 1);
}


template<class T>
void b_tree<T> :: preOrder(){
    preOrder(head);
}

template<class T>
void b_tree<T> :: preOrder(node<T> * temp){
    if(temp == NULL) return;
    cout << "The info is : " << temp -> data << endl;
    preOrder(temp -> left);
    preOrder(temp -> right);
}

template<class T>
void b_tree<T> :: midOrder(){
    midOrder(head);
}

template<class T>
void b_tree<T> :: midOrder(node<T> * temp){
    if(temp == NULL) return;
    midOrder(temp -> left);
    cout << "The info is : " << temp -> data << endl;
    midOrder(temp -> right);
}

template<class T>
void b_tree<T> :: postOrder(){
    postOrder(head);
}

template<class T>
void b_tree<T> :: postOrder(node<T> * temp){
    if(temp == NULL) return;
    postOrder(temp -> left);
    postOrder(temp -> right);
    cout << "The info is : " << temp -> data << endl;
}

template<class T>
void b_tree<T> :: show(){
    node<T> * temp;
}

template<class T>
node<T> *&  b_tree<T> :: get_head(){
    return head;
}

template<class T>
void b_tree<T> ::  calculate_preOrder(string mid_expression , string post_expression) {
    int mid_length = mid_expression.size() , post_length = post_expression.size();
    if(mid_length != post_length) throw exception();
    char * pass_mid = new char[mid_length] , * pass_post = new char[mid_length];
    for(int i = 0 ; i < mid_length ; i ++){
        pass_mid[i] = mid_expression[i];
        pass_post[i] = post_expression[i];
    }
    b_tree<char> * example = new b_tree<char>();
    example -> get_head() = get_answer(pass_mid , pass_post , mid_length);
    example -> preOrder();
    example -> ~b_tree();
}

template<class T>
node<char>* b_tree<T> :: get_answer(char * mid_expression , char * post_expression , int length){
    if(length == 0)	return NULL;
    int root = 0;
    node<char> * temp = new node<char>();
    char temp_char = *(post_expression + length - 1);
    temp -> data = temp_char;
    for(; root < length ; root ++){
        if(mid_expression[root] == temp_char) break;
    }
    temp -> left = get_answer(mid_expression , post_expression , root);
    temp -> right = get_answer(mid_expression + root + 1 , post_expression + root , length - (root + 1));
    return temp;
}

template<class T>
void b_tree<T> :: calculate_postOrder(string pre , string mid){
    int length_pre = pre.length() , length_mid = mid.length();
    if(length_pre != length_mid) throw exception();
    char * pre_char = new char[length_pre] , * mid_char = new char[length_pre];
    for(int i = 0 ; i < length_pre ; i++){
        pre_char[i] = pre[i];
        mid_char[i] = mid[i];
    }
    b_tree<char> * temp = new b_tree<char>();
    temp -> get_head() = get_post_answer(pre_char , mid_char , length_pre);
    temp -> postOrder();
    temp -> ~b_tree();
}

template<class T>
node<char>* b_tree<T> :: get_post_answer(char * pre , char * mid , int length){
    if(length == 0)	return NULL;
    int root = 0;
    node<char> * temp = new node<char>();
    char temp_char = *(pre);
    temp -> data = temp_char;
    for(; root < length ; root ++){
        if(mid[root] == temp_char) break;
    }
    temp -> left = get_post_answer(pre + 1 , mid , root);
    temp -> right = get_post_answer(pre + root + 1, mid + root + 1 , length - (root + 1));
    return temp;
}


int main(int argc , char ** argv){
    b_tree<int> * temp = new b_tree<int>(4);
    //cout << (temp -> head -> left == NULL) << endl;
    //cout << (temp -> head -> left -> left == NULL) << endl;
    //temp -> get_head();
    //cout << temp -> head -> data << endl;
    temp -> get_head() -> left -> left -> data = 21;
    temp -> get_head() -> left -> right -> data = 12;
    cout << "PRE " << endl;
    temp -> preOrder();
    cout << "MID " << endl;
    temp -> midOrder();
    cout << "POST " << endl;
    temp -> postOrder();
    temp -> forward();
    //cout << temp -> get_count() << endl;
    //stack<int> * hah = NULL;
    //cout << "hah == null : " << (hah == NULL) << endl;
    //temp -> preOrder();
    cout << "Node is : " << temp -> calculate_node() << endl;
    cout << "High is : " << temp -> calculate_high() << endl;
    delete temp;
    /*
      string mid = "" , post = "";
      cout << "Input the mid_order's expression : " << endl;
      while(mid.length() == 0){
      //Test data : ADEFGHMZ
      getline(cin , mid);
      }
      cout << "Input the post_order's expression : " << endl;
      while(post.length() == 0){
      //Test data : AEFDHZMG
      getline(cin , post);
      }
      temp -> calculate_preOrder(mid , post);
    */
    string pre = "" , mid = "";
    cout << "Input the pre_order's expression : " << endl;
    while(pre.length() == 0){
        getline(cin , pre);
    }
    cout << "Input the mid_order's expression : " << endl;
    while(mid.length() == 0){
        getline(cin , mid);
    }
    temp -> calculate_postOrder(pre , mid);
    return 0;
}
