#include <iostream>
#include <math.h>

using std :: cout;
using std :: cin;
using std :: endl;

template <typename T>
struct Node
{
    int number = 0;
    T * keyword = NULL;
    Node<T> ** son = NULL;
};
template <typename T>

class B_Tree
{
public:
    B_Tree(int argc , T * argv , int order);
    B_Tree(int order);
    void insert(T info);
    bool remove(T info);
    bool search(T info);
    void test();
    virtual ~B_Tree();
    Node<T> * root;
    void print(Node<T> * root);
    bool search(Node<T> * root , T  info);
    void free(Node<T> * root);
    void insert(Node<T> * root , T info);
    void insert_son(Node<T> * root , int position , Node<T> * & newer);
    bool adjust(Node<T> * root);
    void print_son(Node<T> * root);
    int get_position(Node<T> * father ,T info);
    void show(Node<T> * node);
    void inner_remove(Node<T> * root , T info);
    void next_remove(Node<T> * root ,int position);
    void delete_without(Node<T> * root , int position);
    bool delete_with(Node<T> * root , int position);
    bool rental(Node<T> * root , int position , bool flag);
    bool complete_with_children(Node<T> * root , int position);
    bool enough(Node<T> * root , int position);
    void rental_from_brother(Node<T> * root , int position);
    void rental_from_father(Node<T> * root , int position);
    void merge(Node<T> * root , int position);
    void merge(Node<T> * root , int left , int right);
    void merge(Node<T> * left , Node<T> * right);
    void merge(Node<T> * root , int position , bool lr);
    void check(T info);
    void debug(T info);
    bool satisfied(Node<T> * root);
    int order , down , up , position , back;
    bool split = false , deal = true , special = false;
    Node<T> * father;
    T embed;
};

template <typename T>
void B_Tree <T> :: print(Node<T> * root){
    cout << "ROOT INFO : " << endl;
    show(root);
    cout << "SUB INFO : " << endl;
    cout << "GET NUM : " << root -> number << endl;
    if(root -> son != NULL){
        for (int i = 0; i < root -> number + 1; ++i)
        {
            cout << "show step : " << i << endl;
            show(root -> son[i]);
        }
    }

}

template <typename T>
bool B_Tree <T> :: satisfied(Node<T> * root){
    if(root -> number >= down || (root == this -> root && root -> number > 0)) return true;
    return false;
}

template <typename T>
void B_Tree <T> :: check(T info){
    cout << "Adding " << info << endl;
    insert(info);
    cout << "ROOT INFO : " << endl;
    show(root);
    cout << "SUB INFO : " << endl;
    for (int i = 0; i < root -> number + 1; ++i)
    {
        show(root -> son[i]);
    }
}

template <typename T>
void B_Tree <T> :: debug(T info){
    cout << "Removing " << info << endl;
    remove(info);
    cout << "ROOT INFO : " << endl;
    show(root);
    cout << "SUB INFO : " << endl;
    cout << "GET NUM : " << root -> number << endl;
    if(root -> son != NULL){
        for (int i = 0; i < root -> number + 1; ++i)
        {
            show(root -> son[i]);
        }
    }
}

template <typename T>
B_Tree <T> :: B_Tree(int order){
    this -> order = order;
    up = order - 1;
    down = ceil(double(up) / 2);
    root = new Node<T>();
    root -> son = new Node<T> * [up + 1];
}

template <typename T>
void B_Tree <T> :: merge(Node<T> * left , Node<T> * right){
    //the function is to merge the son[position] and son[position+1]
    for (int i = left -> number , count = 0; count < right -> number; ++count , ++i)
    {
        left -> keyword[i] = right -> keyword[count];
    }
    if(left -> son != NULL){
        for (int i = left -> number + 1 , count = 0; count < right -> number + 1; ++count , ++i)
        {
            left -> son[i] = right -> son[count];
        }
    }
    left -> number += right -> number;
}

template <typename T>
void B_Tree <T> :: merge(Node<T> * root , int position){
    cout << "Get the root -> number : " << root -> number << endl;
    int limit = special ? root -> son[position] -> number + 1 : root -> son[position] -> number;
    for (int i = position; i < root -> number ; ++i)
    {
        root -> keyword[i] = root -> keyword[i+1];
    }
    for (int i = limit , count = 0; count < root -> son[position+1] -> number; ++i , ++count)
    {
        root -> son[position] -> keyword[i] = root -> son[position+1] -> keyword[count];
    }
    if(root -> son[position] -> son != NULL){
        show(root);
        cout << "Get code here ." << endl;
        cout << "Check ing number " << root -> son[position] -> number << endl;
        for (int i = root -> son[position] -> number + 1, count = 0; count < root -> son[position+1] -> number + 1; ++i , ++count)
        {
            root -> son[position] -> son[i] = root -> son[position+1] -> son[count];
            cout << "step : " << i << endl;
            show(root -> son[position] -> son[i]) ;
        }
        cout << "Move done " << endl;
    }

    root -> son[position] -> number += root -> son[position+1] -> number;
    cout << "Number found " << root -> son[position] -> number << endl;
    //show(root -> son[position] -> son[5]);
    for (int i = position + 1; i < root -> number + 1;  ++i)
    {
        root -> son[i] = root -> son[i+1];
    }
    -- root -> number;
}

template <typename T>
void B_Tree <T> :: merge(Node<T> * root , int position , bool lr){
    cout << "My lf work " << endl;
    int limit = special ? root -> son[position+1] -> number + 1 : root -> son[position] -> number;
    for (int i = position; i < root -> number; ++i)
    {
        root -> keyword[i] = root -> keyword[i+1];
    }
    for (int i = root -> son[position] -> number , count = 0; count < limit; ++i , ++count)
    {
        root -> son[position] -> keyword[i] = root -> son[position+1] -> keyword[count];
    }
    if(root -> son[position] -> son != NULL){
        show(root);
        cout << "Get code here ." << endl;
        cout << "Check ing number " << root -> son[position] -> number << endl;
        for (int i = root -> son[position] -> number + 1, count = 0; count < root -> son[position+1] -> number + 1; ++i , ++count)
        {
            root -> son[position] -> son[i] = root -> son[position+1] -> son[count];
            cout << "step : " << i << endl;
            show(root -> son[position] -> son[i]) ;
        }
        cout << "Move done " << endl;
    }

    root -> son[position] -> number += limit;
    cout << "Number found " << root -> son[position] -> number << endl;
    for (int i = position + 1; i < root -> number + 1;  ++i)
    {
        root -> son[i] = root -> son[i+1];
    }
    -- root -> number;
}

template <typename T>
bool B_Tree<T> :: rental(Node<T> * root ,int position , bool flag){
    int key = this -> position;
    if(flag){
        // need to get from the right brother .
        for (int i = position; i < root -> number - 1; ++i)
        {
            root -> keyword[i] = root -> keyword[i+1];
        }
        root -> keyword[root -> number - 1] = father -> keyword[key];
        father -> keyword[key] = father -> son[key+1] -> keyword[0];
        father -> son[key+1] -> keyword = father -> son[key+1] -> keyword + 1;
        --(father -> son[key+1] -> number);
    }else{
        for (int i = position; i > 0; --i)
        {
            root -> keyword[i] = root -> keyword[i-1];
        }
        root -> keyword[0] = father -> keyword[key-1];
        father -> keyword[key-1] = father -> son[key-1] -> keyword[father->son[key-1] -> number - 1];
        --(father -> son[key-1] -> number);
    }
    return true;
}

template <typename T>
bool B_Tree<T> :: complete_with_children(Node<T> * root , int position){
    int left = root -> son[position] -> number;
    int right = root -> son[position+1] -> number;
    if(left > right){
        if(left > down){
            root -> keyword[position] = root -> son[position] -> keyword[left-1];
            root -> son[position] -> number --;
            deal = true;
            return true;
        }else{
            merge(root , position);
            special = true;
            if(satisfied(root))
            {
                deal = true;
                return true;
            }
            deal = false;
            return false;
        }
    }else{
        if(right > down){
            root -> keyword[position] = root -> son[position + 1] -> keyword[0];
            for (int i = 1; i < right; ++i)
            {
                root -> son[position+1] -> keyword[i-1] = root -> son[position+1] -> keyword[i];
            }
            root -> son[position+1] -> number --;
            deal = true;
            return true;
        }else{
            cout << "situation 4" << endl;
            merge(root , position);
            show(root);
            special = true;
            if(satisfied(root))
            {
                cout << "satified true" << endl;
                deal = true;
                return true;
            }
            cout << "satified false" << endl;
            deal = false;
            return false;
        }
    }
}

// the function should to be completed for root's son needed to be connected .
template <typename T>
bool B_Tree<T> :: delete_with(Node<T> * root , int position){
    //The mark is the position of this -> position
    //father -> keywork -> son
    //The function is to delete the node without the children node .
    int mark = this -> position;
    cout << "Get mark " << mark << endl;
    // mark menas the his father's position
    if(father != NULL){
        if(mark == 0){
            cout << "MARK it" << endl;
            if(father -> son[1] -> number > down){
                deal = true;
                return rental(root , position  ,true);
            }else{
                cout << "DELETE_WITH FOR <= DONE " << endl;
                if(!special){
                    cout << "Get in the !special " << endl;
                    for (int i = position; i < root -> number ; ++i)
                    {
                        root -> keyword[i] = root -> keyword[i+1];
                    }
                    root -> keyword[root -> number - 1] = father -> keyword[mark];
                    cout << "Root -> number \t " << root -> number << endl;
                    for (int i = 1; i < father -> number; ++i)
                    {
                        father -> keyword[i-1] = father -> keyword[i];
                    }
                    show(root);
                    merge(father , mark);
                    show(root);
                }else{
                    root -> keyword[root -> number] = father -> keyword[mark];
                    merge(father , mark);
                    for (int i = 1; i < father -> number; ++i)
                    {
                        father -> keyword[i-1] = father -> keyword[i];
                    }
                    root -> number ++;
                    special = false;
                }
                if(!satisfied(father)) {
                    deal = false;
                    return false;
                }
                deal = true;
                return true;
            }
        }else if(mark == father -> number){
            if(father -> son[mark-1] -> number > down){
                deal = true;
                return rental(root , position , false);
            }else{
                if(!special){
                    for (int i = position; i > 0 ; --i)
                    {
                        root -> keyword[i] = root -> keyword[i-1];
                    }
                    root -> keyword[0] = father -> keyword[father -> number - 1];
                    merge(father , mark-1 , false);
                }else{
                    for (int i = root -> number; i > 0; --i)
                    {
                        root -> keyword[i] = root -> keyword[i-1];
                    }
                    root -> keyword[0] = father -> keyword[father -> number - 1];
                    merge(father , mark-1 , false);
                    special = false;
                    root -> number ++;
                }
                if(!satisfied(father)) {
                    deal = false;
                    return false;
                }
                deal = true;
                return true;
            }
        }else if(father -> son[mark -1] -> number > father -> son[mark + 1] -> number){
            if(father -> son[mark - 1] -> number > down){
                deal = true;
                return rental(root ,position , false);
            }else{
                if(!special){
                    for (int i = position; i > 0 ; --i)
                    {
                        root -> keyword[i] = root -> keyword[i-1];
                    }
                    root -> keyword[0] = father -> keyword[mark];
                    merge(father , mark-1 , false);
                }else{
                    for (int i = root -> number; i > 0; --i)
                    {
                        root -> keyword[i] = root -> keyword[i-1];
                    }
                    root -> keyword[0] = father -> keyword[mark];
                    merge(father , mark-1 , false);
                    root -> number ++;
                    special = false;
                }
                if(father -> number < down){
                    deal = false;
                    return false;
                }
                return true;
            }
        }
        else{
            if(father -> son[mark + 1] -> number > down){
                deal = true;
                return rental(root ,position , true);
            }else{
                if(!special){
                    for (int i = position; i < root -> number - 1; ++i)
                    {
                        root -> keyword[i] = root -> keyword[i+1];
                    }
                    root -> keyword[root -> number - 1] = father -> keyword[mark];
                    merge(father , mark);
                    for (int i = mark+1; i < father -> number; ++i)
                    {
                        father -> keyword[i-1] = father -> keyword[i];
                    }
                }else{
                    special = !special;
                    root -> keyword[root -> number] = father -> keyword[mark];
                    merge(father , mark);
                    root -> number ++;
                }
                for (int i = mark + 1; i < father -> number + 1; ++i)
                {
                    father -> keyword[i-1] = father -> keyword[i];
                }
                if(!satisfied(father)){
                    deal = false;
                    return false;
                }
                deal = true;
                return true;
            }
        }
    }
    else{
        // complete it for father == NULL later

        deal = false;
        return false;
    }
}

template <typename T>
void B_Tree<T> :: delete_without(Node<T> * root , int position){
    for (int i = position; i < root -> number; ++i)
    {
        root -> keyword[i] = root -> keyword[i+1];
    }
    --(root -> number);
}

template <typename T>
bool B_Tree <T> :: remove(T info){
    int temp;
    bool flag = true , attention = false , end = true;
    if(root != NULL && root -> number > 0){
        for (int i = 0; end &&  i < root -> number; ++i)
        {
            if(info < root -> keyword[i]){
                if(root -> son == NULL || root -> son[0] == NULL || root -> son[0] -> number <= 0){
                    flag = false;
                    return false;
                }else{
                    position = i;
                    temp = i;
                    father = root;
                    back = i;
                    inner_remove(root -> son[i] , info);
                    flag = false;
                    end = false;
                    break;
                }
            }else if(info == root -> keyword[i]){
                father = NULL;
                flag = false;
                cout << "Found in root " << endl;
                temp = i;
                attention = true;
                next_remove(root, i);
                break;
            }
        }
        if(flag){
            father = root;
            position = root -> number;
            temp = position;
            back = root -> number;
            if(root -> son == NULL || root -> son[0] == NULL || root -> son[0] -> number <= 0) {
                return false;
            }else{
                cout << "Removin from root " << endl;
                inner_remove(root -> son[root -> number] , info);
            }
        }
        if(!deal){
            cout << "jump to father and deal" << endl;
            if(enough(root , temp)){
                deal = true;
                rental_from_brother(root , temp);
            }else{
                cout << "Run rental from father" << endl;
                show(root->son[0]);
                rental_from_father(root , temp);
                cout << root -> number << endl;
            }
            deal = true;
        }
        if(root -> number <= 0){
            delete root -> keyword;
            root = root -> son[0];
            if(attention){
                // Must need be changed here .
                for (int i = 0; i < root -> son[root -> number + 1] -> number; ++i)
                {
                    insert(root -> son[root -> number + 1] -> keyword[i]);
                }
            }
        }
        return true;
    }
    return false;
}

template <typename T>
void B_Tree<T> :: inner_remove(Node<T> * root , T info){
    cout << "Get in inner remove for info : " << info << endl;
    Node<T> * backup = father;
    int temp = back;
    bool flag = false , end = true;
    for (int i = 0; end &&  i < root -> number; ++i)
    {
        if(info < root -> keyword[i]){
            position = i;
            if(root -> son == NULL) {
                deal = true;
                return ;
            }
            else {
                father = root;
                back = i;
                position = i;
                flag = true;
                inner_remove(root -> son[i] ,info);
                cout << "Attention before inner . " << endl;
                cout << this -> root -> number << endl;
                end = false;
            }
        }else if(info == root -> keyword[i]){
            father = backup;
            next_remove(root , i);
            cout << "removing from the son and jump" << endl;
            return ;
        }
    }
    if(!flag){
        if(root -> son == NULL || (root -> son[0] -> number) <= 0) {
            deal = true;
            return ;
        }else {
            father = root;
            position = root -> number;
            back = position;
            inner_remove(root -> son[root -> number] , info);
        }
    }
    if(!deal){
        if(enough(backup , temp)){
            deal = true;
            cout << "rental from brother" << endl;
            rental_from_brother(backup , temp);
        }else{
            cout << "Error in here " << endl;
            rental_from_father(backup , temp);
        }
    }
}

template <typename T>
bool B_Tree<T> :: enough(Node<T> * root , int position){
    if(root == NULL || root -> number <= 0) return false;
    if(position == 0){
        return root -> son[1] -> number > down;
    }else if(position == root -> number){
        return root -> son[root -> number - 1] -> number > down;
    }else {
        return root -> son[position -1] > root -> son[position + 1] ? root -> son[position -1] -> number > down : root -> son[position + 1] -> number > down ;
    }
}

template <typename T>
void B_Tree<T> :: merge(Node<T> * root , int left , int right){
    // the function is to merget the two node which
    int limit = root -> son[right] -> number;
    for (int i = root -> son[left] -> number , count = 0; count < limit; ++count , ++i)
    {
        root -> son[left] -> keyword[i] = root -> son[right] -> keyword[count];
    }
    // to merge son -> keyword
    if(root -> son[left] -> son != NULL){
        for (int i = root -> son[left] -> number , count = 0 ; count < root -> son[right] -> number + 1; ++i , ++count)
        {
            root -> son[left] -> son[i] = root -> son[right] -> son[count];
        }
    }
    root -> son[left] -> number += root -> son[right] -> number;
    // to merget son -> son
    for (int i = right; i < root -> number; ++i)
    {
        root -> son[i] = root -> son[i+1];
    }
    // to merge son
    for (int i = left; i < root -> number; ++i)
    {
        root -> keyword[i] = root -> keyword[i+1];
    }
    // to merge root -> keyword
    -- root -> number;
}

template <typename T>
void B_Tree<T> :: rental_from_father(Node<T> * root , int position){
    if(root -> number <= 0){
        root = root -> son[0];
        deal = true;
        return ;
    }
    if(position == 0){
        root -> son[position] -> keyword[root -> son[position] -> number] = root -> keyword[position];
        // to move data from root to son
        cout << "Must be here " << endl;
        cout << root -> number << endl;
        ++ root -> son[position] -> number ;
        merge(root , position , position+1);
        //merge(root , position);
    }else if(position == root -> number){
        for (int i = root -> son[position] -> number; i > 0; --i)
        {
            root -> son[position] -> keyword[i] = root -> son[position] -> keyword[i-1];
        }
        root -> son[position] -> keyword[0] = root -> keyword[position-1];
        // to move data from root to son
        ++ root -> son[position] -> number;
        //merge(root , position - 1 , position);
        merge(root , position-1);
    }else{
        if(root -> son[position+1] -> number > root -> son[position-1] -> number ){
            root -> son[position] -> keyword[root -> son[position] -> number] = root -> keyword[position];
            // to move data from root to son
            ++ root -> son[position] -> number ;
            merge(root , position , position + 1);
            //merge(root , position);
        }else{
            for (int i = root -> son[position] -> number; i > 0; --i)
            {
                root -> son[position] -> keyword[i-1] = root -> son[position] -> keyword[i];
            }
            root -> son[position] -> keyword[0] = root -> keyword[position-1];
            ++ root -> son[position] -> number ;
            //merge(root , position - 1 , position);
            merge(root , position-1);
        }
    }
    deal = satisfied(root);
}

template <typename T>
void B_Tree<T> :: rental_from_brother(Node<T> * root , int position){
    if(position == 0){
        root -> son[position] -> keyword[root -> son[position] -> number] = root -> keyword[position];
        // to move data from root to son
        ++ root -> son[position] -> number ;
        // adjust the number of son
        root -> keyword[position] = root -> son[position+1] -> keyword[0];
        // to move data frome son to root;
        root -> son[position] -> son[root -> son[position] -> number] = root -> son[position+1] -> son[0];
        // to move data from brother to itself
        for (int i = 1; i < root -> son[position+1] -> number; ++i)
        {
            root -> son[position+1] -> son[i-1] = root -> son[position+1] -> son[i];
        }
        // adjust the order of the brother
        for (int i = 0; i < root -> son[position+1] -> number; ++i)
        {
            root -> son[position+1] -> keyword[i] = root -> son[position+1] -> keyword[i+1];
        }
        -- root -> son[position+1] -> number;
        // adjut the number of the brother
    }else if(position == root -> number){
        for (int i = root -> son[position] -> number; i > 0; --i)
        {
            root -> son[position] -> keyword[i-1] = root -> son[position] -> keyword[i];
        }
        root -> son[position] -> keyword[0] = root -> keyword[position-1];
        // to move data from root to son
        ++ root -> son[position] -> number ;
        // adjust the number of son
        root -> keyword[position-1] = root -> son[position-1] -> keyword[root -> son[position-1] -> number - 1];
        // to move data frome son to root;
        for (int i = root -> son[position] -> number; i > 0; --i)
        {
            root -> son[position] -> son[i] = root -> son[position] -> son[i-1];
        }
        // adjust the itself's order
        root -> son[position] -> son[0] = root -> son[position-1] -> son[root -> son[position-1] -> number];
        // to move data from brother to itself
        -- root -> son[position-1] -> number;
        // adjut the number of the brother
    }else{
        if(root -> son[position+1] -> number > root -> son[position-1] -> number ){
            root -> son[position] -> keyword[root -> son[position] -> number] = root -> keyword[position];
            // to move data from root to son
            ++ root -> son[position] -> number ;
            // adjust the number of son
            root -> keyword[position] = root -> son[position+1] -> keyword[0];
            // to move data frome son to root;
            root -> son[position] -> son[root -> son[position] -> number] = root -> son[position+1] -> son[0];
            // to move data from brother to itself
            for (int i = 1; i < root -> son[position+1] -> number; ++i)
            {
                root -> son[position+1] -> son[i-1] = root -> son[position+1] -> son[i];
            }
            // adjust the order of the brother
            //root -> son[position+1] -> keyword = root -> son[position+1] -> keyword + 1;
            for (int i = 0; i < root -> son[position+1] -> number  ; ++i)
            {
                root -> son[position+1] -> keyword[i] = root -> son[position+1] -> keyword[i+1];
            }
            -- root -> son[position+1] -> number;
            // adjut the number of the brother
        }else{
            for (int i = root -> son[position] -> number; i > 0; --i)
            {
                root -> son[position] -> keyword[i-1] = root -> son[position] -> keyword[i];
            }
            root -> son[position] -> keyword[0] = root -> keyword[position-1];
            // to move data from root to son
            ++ root -> son[position] -> number ;
            // adjust the number of son
            root -> keyword[position-1] = root -> son[position-1] -> keyword[root -> son[position-1] -> number - 1];
            // to move data frome son to root;
            for (int i = root -> son[position] -> number; i > 0; --i)
            {
                root -> son[position] -> son[i] = root -> son[position] -> son[i-1];
            }
            // adjust the itself's order
            root -> son[position] -> son[0] = root -> son[position-1] -> son[root -> son[position-1] -> number];
            // to move data from brother to itself
            -- root -> son[position-1] -> number;
            // adjut the number of the brother
        }
    }
    deal = satisfied(root);
}

template <typename T>
void B_Tree<T> :: next_remove(Node<T> * root  , int position){
    cout << "TARGET INFO POSITION FOUND : " << position << endl;
    if(father == NULL){
        if(root -> son == NULL || root -> son[0] == NULL || root -> son[0] -> number <= 0){
            cout << "remove from root without son ." << endl;
            for (int i = position; i < root -> number; ++i)
            {
                root -> keyword[i] = root -> keyword[i+1];
            }
            root -> number --;
            deal = true;
            return ;
        }else{
            cout << "remove from root with son ." << endl;
            if(complete_with_children(root , position)){
                return ;
            }
            cout << "remove from children failed ." << endl;
            if(delete_with(root , position)){
                cout << "delete with brother .  " << endl;
                return ;
            }
            special = false;
            //If you run here . it means the node father and son and brother is on the limit .
        }
        deal = false;
        return ;
    }else if(root -> son == NULL || root -> son[0] == NULL || root -> son[0] -> number == 0){
        cout << "Removing with father which isn't the root" << endl;
        if(root -> number > down){
            delete_without(root , position);
            return ;
        }else{
            if(delete_with(root , position)){
                return ;
            }
            show(root);
            cout << "removing from brother failed . " << endl;
            deal = false;
            special = false;
            return ;
            // in the end which to be the recurse form .
        }
    }else {
        // just to remove the node wihch with children .
        cout << "Run with node which with children in media " << endl;
        if(complete_with_children(root , position)){
            return ;
        }
        cout << "complete with children here . "  << endl;
        if(delete_with(root , position)){
            return ;
        }
        special = false;
        //If you run here . it means the node father and son and brother is on the limit .
    }
    deal = false;
    return ;
}

template <typename T>
void B_Tree<T> :: show(Node<T> * node){
    if(node != NULL)
        for (int i = 0; i < node -> number; ++i)
        {
            cout << "keyword[" << i << "] : " << node -> keyword[i] << endl;
        }
}

template <typename T>
void B_Tree<T> :: print_son(Node<T> * root){
    for (int i = 0; i < root -> number + 1; ++i)
    {
        for (int j = 0; j < root -> son[i] -> number; ++j)
        {
            cout << "son info [" << i << "] : "  << root -> son[i] -> keyword[j] << endl;
        }
    }
}
template <typename T>
void B_Tree<T> :: test(){
    cout << "Root number -> " << root -> number << endl;
    for (int i = 0; i < root -> number + 1; ++i)
    {
        cout << "son[" << i << "] -> number ";
        cout << root -> son[i] -> number << endl;
    }
    print_son(root);
}


template <typename T>
bool B_Tree<T> :: adjust(Node<T> * root){
    /*
      if(root -> number == 1){
      if(((root -> son[0]) == NULL)){
      cout << "FALSE" << endl;
      }else{
      cout << "TRUE" << endl;
      }
      }
    */
    return ((root -> son[0]) == NULL) ? true : false;
}

template <typename T>
int B_Tree <T> :: get_position(Node<T> * father ,T info){
    for (int i = 0; i < father -> number; ++i)
    {
        if(info < father -> keyword[i]) return i+1;
    }
    return father -> number+1;
}

template <typename T>
void B_Tree <T> :: insert_son(Node<T> * root , int position , Node<T> * & newer){
    for (int i = root -> number ; i > position; --i)
    {
        root -> son[i+1] = root -> son[i];
    }
    root -> son[position] = newer;
    /*
      cout << "position " << position << endl;
      show(newer);
      cout << "FLAG" << endl;
      show(root);
      for (int i = 0; i < root -> number + 2; ++i)
      {
      show(root -> son[i]);
      }
      cout << "FLAG" << endl;
    */
}

template <typename T>
B_Tree <T> :: B_Tree(int argc , T * argv , int order){
    this -> order = order;
    up = order - 1;
    down = ceil(double(up) / 2);
    root = new Node<T>();
    root -> son = new Node<T> * [up + 1];
    for (int i = 0; i < argc; ++i)
    {
        insert(argv[i]);
    }
}

template <typename T>
void B_Tree <T> :: insert(T info){
    cout << "Info for : " << info <<endl;
    if(root -> number == 0){
        cout << "init . " << endl;
        root -> number = 1;
        root -> keyword = new T[up + 1];
        root -> keyword[0] = info;
    }else {
        //root without children.
        if(adjust(root)){
            //after adding to tree , root won't split.
            if(root -> number < up){
                cout << "Runing in without children , after adding to tree , root won't split." << endl;
                for (int i = 0; i < root -> number; ++i)
                {
                    if(info < root -> keyword[i]){
                        for (int j = root -> number-1; j >= i; --j)
                            root -> keyword[j+1] = root -> keyword[j];
                        root -> keyword[i] = info;
                        root -> number++;
                        return;
                    }
                }
                root -> keyword[root -> number] = info;
                root -> number ++;
            }else{
                cout << "Runing in without children . root split ." << endl;
                //after adding to tree , root split.
                Node<T> * rebirth = new Node<T>();
                rebirth -> keyword = new T[up + 1];
                int limit = (root -> number + 1)/2 , count = 0;
                bool flag = true;
                for (int i = 0; i < limit; ++i , ++(rebirth -> number))
                {
                    if(flag && info < root -> keyword[count]) {
                        rebirth -> keyword[i] = info;
                        flag = false;
                    }else {
                        rebirth -> keyword[i] = root -> keyword[count++];
                    }
                }
                Node<T> * birthre = new Node<T>();
                birthre -> keyword = new T[up + 1];
                limit = count;
                for (int i = count; i < root -> number; ++i)
                {
                    if(flag && info < root -> keyword[count]) {
                        if(i == limit){
                            root -> keyword[0] = info;
                            flag = false;
                        }else{
                            birthre -> keyword[(birthre -> number)++] = info;
                        }
                    }else {
                        if(i == limit) root -> keyword[0] = root -> keyword[count++];
                        else {
                            birthre -> keyword[(birthre -> number)++] = root -> keyword[count++];
                        }
                    }
                }
                if(flag){
                    birthre -> keyword[(birthre -> number) ++] = info;
                }
                root -> son = new Node<T> * [up+1];
                root -> son[0] = rebirth;
                root -> son[1] = birthre;
                root -> number = 1;
            }
        }else{
            //tree with children
            //find the true position to insert.
            cout << "Runing with children and finding . " << endl;
            bool flag = true;
            father = root;
            for (int i = 0; i < root -> number; ++i)
            {
                if(flag && info < root -> keyword[i]){
                    insert(root -> son[i] , info);
                    flag = false;
                    break;
                }
            }
            if(flag){
                insert(root -> son[root -> number] , info);
            }
            if(split){
                if(root -> number < up){
                    cout << "children split but root won't split " << endl;
                    for (int i = 0; i < root -> number; ++i)
                    {
                        if(embed < root -> keyword[i]){
                            for (int j = root -> number - 1;  j >= i; --j)
                            {
                                root -> keyword[j+1] = root -> keyword[j];
                            }
                            root -> keyword[i] = embed; // his children is root -> son[i] && root -> son[i+1]
                            //insert_son(root , i + 1 , node);
                            root -> number ++;
                            return ;
                        }
                    }
                    root -> keyword[root -> number] = embed;
                    //insert_son(root , root -> number , node);
                    root -> number ++;
                }else{
                    //which need make tree high .
                    cout << "children split and root will split " << endl;
                    //show(root);
                    //cout << "EMBED : " << embed << endl;
                    Node<T> * rebirth = new Node<T>();
                    rebirth -> keyword = new T[up + 1];
                    bool flag = true;
                    int count = 0;
                    T temp[root -> number + 1];
                    for (int i = 0; i < root -> number + 1; ++i)
                    {
                        if(flag && embed < root -> keyword[count]){
                            flag = false;
                            temp[i] = embed;
                        }else {
                            temp[i] = root -> keyword[count++];
                        }
                    }
                    if(flag){
                        temp[root -> number] = embed;
                    }
                    int limit = (root -> number + 1) / 2;
                    embed = temp[limit];
                    rebirth -> number = root -> number - limit;
                    rebirth -> keyword = new T[up+1];
                    for (int i = limit + 1; i < root -> number + 1; ++i)
                    {
                        rebirth -> keyword[i - limit - 1] = temp[i];
                    }
                    Node<T> * birthre = new Node<T>();
                    birthre -> keyword = new T[up+1];
                    for (int i = 0; i < limit; ++i)
                    {
                        birthre -> keyword[i] = temp[i];
                    }
                    birthre -> number = limit;
                    birthre -> son = new Node<T> *[up+1];
                    //birthre -> son = root -> son;
                    for (int i = 0; i < limit + 1; ++i)
                    {
                        birthre -> son[i] = root -> son[i];
                    }
                    //rebirth -> son = root -> son + limit + 1;
                    rebirth -> son = new Node<T> * [up+1];
                    for (int i = 0; i < rebirth -> number + 1 ; ++i)
                    {
                        rebirth -> son[i] = root -> son[i+limit+1];
                    }
                    root -> number = 1;
                    root -> keyword[0] = temp[limit];
                    root -> son[0] = birthre;
                    root -> son[1] = rebirth;
                }
            }
        }
    }
}

template <typename T>
void B_Tree <T> :: insert(Node<T> * root , T info){
    Node<T> * backup = father;
    if(root -> son == NULL){
        if(root -> number < up){
            bool flag = true;
            for (int i = 0; i < root -> number; ++i)
            {
                if(flag && info < root -> keyword[i]){
                    for (int j = root -> number - 1; j >= i; --j)
                    {
                        root -> keyword[j+1] = root -> keyword[j];
                    }
                    root -> keyword[i] = info;
                    flag = false;
                }
            }
            if(flag){
                root -> keyword[root -> number] = info;
            }
            root -> number ++;
            split = false;
            return;
        }else{
            cout << "split" << endl;
            //get the end . and split
            split = true;
            bool flag = true;
            Node<T> * rebirth = new Node<T>();
            T temp[root -> number + 1];
            int count = 0;
            for (int i = 0; i < root -> number + 1; ++i)
            {
                if(flag && info < root -> keyword[count]){
                    flag = false;
                    temp[i] = info;
                }else {
                    temp[i] = root -> keyword[count++];
                }
            }
            if(flag){
                temp[root -> number] = info;
            }
            int limit = (root -> number + 1) / 2;
            embed = temp[limit];
            rebirth -> number = root -> number - limit;
            rebirth -> keyword = new T[up+1];
            for (int i = limit + 1; i < root -> number + 1; ++i)
            {
                rebirth -> keyword[i - limit - 1] = temp[i];
            }
            for (int i = 0; i < limit; ++i)
            {
                root -> keyword[i] = temp[i];
            }
            root -> number = limit;
            insert_son(father ,get_position(father , embed), rebirth);
            return ;
        }
    }else{
        bool flag = true;
        for (int i = 0; i < root -> number; ++i)
        {
            if(flag && info < root -> keyword[i]){
                flag = false;
                father = root;
                cout << "ATTe" << endl;
                show(root);
                insert(root -> son[i] , info);
                break;
            }
        }
        if(flag) {
            father = root;
            insert(root -> son[root -> number] , info);
        }
    }
    if(split){
        if(root -> number < up){
            //media , won't split .
            split = false;
            for (int i = 0; i < root -> number; ++i)
            {
                if(embed < root -> keyword[i]){
                    for (int j = root -> number -1; j >= i; --j)
                    {
                        root -> keyword[j+1] = root -> keyword[j];
                    }
                    root -> keyword[i] = embed;
                    root -> number ++;
                    return ;
                }
            }
            root -> keyword[root -> number] = embed;
            root -> number ++;
        }else{
            //media , will split .
            //insert_son(father , get_position(embed) ,node);
            split = true;
            bool flag = true;
            Node<T> * rebirth = new Node<T>();
            T temp[root -> number + 1];
            for (int i = 0 , count = 0; i < root -> number + 1; ++i)
            {
                if(flag){
                    if(embed < root -> keyword[count]){
                        flag = false;
                        temp[i] = embed;
                    }else{
                        temp[i] = root -> keyword[count++];
                    }
                }else {
                    temp[i] = root -> keyword[count++];
                }
            }
            if(flag){
                temp[root -> number] = embed;
            }
            int limit = (root -> number + 1) / 2;
            cout << "COUT temp" << endl;
            for (int i = 0; i < root -> number + 1; ++i)
            {
                cout << temp[i] << endl;
            }
            embed = temp[limit];
            rebirth -> number = root -> number - limit;
            rebirth -> keyword = new T[up+1];
            for (int i = limit + 1; i < root -> number + 1; ++i)
            {
                rebirth -> keyword[i - limit - 1] = temp[i];
            }
            rebirth -> son = new Node<T> * [up+1];
            for (int i = 0; i < rebirth -> number + 1; ++i)
            {
                rebirth -> son[i] = root -> son[i+limit+1];
            }
            root -> number = limit;
            cout << "Make check" << endl;
            show(root);
            show(rebirth);
            insert_son(backup ,get_position(backup , embed), rebirth);
        }
    }
}

template <typename T>
bool B_Tree <T> :: search(T info){
    return search(this -> root , info);
}

template <typename T>
bool B_Tree <T> :: search(Node<T> * root , T info){
    if(root -> son != NULL){
        for (int i = 0; i < root -> number; ++i)
        {
            if(info < root -> keyword[i]){
                return search(root -> son[i] , info);
            }
            if(info == root -> keyword[i]) return true;
        }
        return search(root -> son[root -> number],info);
    }else {
        for (int i = 0; i < root -> number; ++i)
        {
            if(info < root -> keyword[i]){
                return false;
            }
            if(info == root -> keyword[i]) return true;
        }
        return false;
    }
}

template <typename T>
B_Tree <T> :: ~B_Tree(){
    free(root);
}

template <typename T>
void B_Tree<T> :: free(Node<T> * root){
    if(root != NULL && NULL != root -> keyword){
        delete root -> keyword;
    }else{
        if(root != NULL){
            int limit = root -> number + 1;
            for (int i = 0; i < limit; ++i)
            {
                if(root != NULL && root -> son != NULL && root -> son[i] != NULL){
                    free(root -> son[i]);
                }
            }
        }
        if(root != NULL && root -> son != NULL){
            delete root -> son;
        }
    }
}

int main(int argc ,char ** argv){
    B_Tree<int> btree(5);
    for (int i = 0; i < 26; ++i)
    {
        btree.check(i);
    }
    cout << "Attention" << endl;
    btree.debug(23);
    cout << "Judgement " << endl;
    for (int j = 0; j < btree.root -> number + 1; ++j)
    {
        cout << "Run for j : " << j << endl;
        for (int i = 0; i < btree.root -> son[j] -> number + 1; ++i)
        {
            btree.show(btree.root -> son[j] -> son[i]);
        }
    }
    cout << "end" << endl;
    return 0;
}
