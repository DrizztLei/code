#include <iostream>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::string;
struct stack{
    int x , y , count ;
    stack * next;
    stack(int _x , int _y ,int cnt , stack * link) {x = _x ; y = _y ; count = cnt ; next = link;}
};

stack * pop(stack *& s){
    stack * temp = s;
    //cout << "X : " << temp -> x << endl;
    //cout << "Y : " << temp -> y << endl;
    if(s != NULL){
        s = s -> next;
    }
    //cout << "Is s == NULL ? : " << (s == NULL) << endl;
    return temp;
}

void push(stack *& s , int x , int y , int count){


    //cout << "Runing . " << endl;
    //cout << "S == NULL : " << (s == NULL) << endl;
    if(s == NULL) {
        if((x == 0 && y == 1) || (x == 1 && y == 0))
            s = new stack(x , y , 2 , s);//bug found here .
        else s = new stack(x , y , count , s);
    }else {
        s = new stack(x , y , count  , s);
    }
    //cout << "Push done . " << endl;
}

void recycle(stack *& target){
    stack * temp;
    while(target != NULL){
        temp = target;
        target = target -> next;
        delete temp;
    }
}

int main(int argc , char ** argv){
    //int ** maze;
    int row , col , i , j , curX = 0 , curY = 0;
    //cout << "Input the row and the col of maze : " << endl;
    //cin >> row >> col;
    row = 4 ;
    col = 4 ;
    int wall = row * col;
    int maze[row][col]={
        {0,0,wall,wall},
        {0,0,wall,0},
        {wall,0,0,wall},
        {wall,0,0,0}
    };
    //cout << maze[0][1] << endl;
    /**for(int i = 0 ; i < row ; i++){
       maze[i] = new int[col];
       cout << "Input the " << i << " col ( 0 for path , " << 100 << " for wall . separate with blank .) : " << endl;
       for(j = 0 ; j < col ; j++){
       cin >> maze[i][j] ;
       }
       }*/
    maze[0][0] = 1;
    int x , y , count;
    stack * g_s_stack_for_maze = new stack(0 , 0 , 1 , NULL);
    stack * g_t_stack_for_temp ;
    while(true){
        g_t_stack_for_temp = pop(g_s_stack_for_maze);
        x = g_t_stack_for_temp -> x;
        y = g_t_stack_for_temp -> y;
        count = g_t_stack_for_temp -> count;
        /**if(x + 1 == row && y + 1 == col) {
           delete g_t_stack_for_temp;
           continue;
           }*/
        //cout << "Pop" << endl;
        if(x-1 >= 0 && maze[x-1][y] != wall && (maze[x-1][y] == 0 || maze[x-1][y] > count + 1)) {
            //cout << maze[x-1][y] << "As , x-1 : "<< x-1 << " y : " << y << endl;
            //cout << "count + 1 : " << count + 1 << endl;
            maze[x-1][y] = count + 1;
            //cout << "Run as up . "<< endl;
            push(g_s_stack_for_maze , x-1 ,y , count + 1);
        }
        if(y-1 >= 0 && maze[x][y-1] != wall && (maze[x][y-1] == 0 || maze[x][y-1] > count + 1)){
            //cout << maze[x][y-1] << "\tAs , x : "<< x << " y-1 : " << y-1 << endl;
            //cout << "count + 1 : " << count + 1 << endl;
            maze[x][y-1] = count + 1;
            //cout << "Run as left . " << endl;
            push(g_s_stack_for_maze , x , y-1 , count + 1);
        }
        if(x+1 < row && maze[x+1][y] != wall &&  (maze[x+1][y] == 0 || maze[x+1][y] > count + 1)){
            //cout << maze[x+1][y] << "\tAs , x+1 : "<< x+1 << " y : " << y << endl;
            //cout << "count + 1 : " << count + 1 << endl;
            maze[x+1][y] = count + 1;
            push(g_s_stack_for_maze , x+1 , y , count + 1);
            //cout << "Run as down . " << endl;
        }
        if(y+1 < col && maze[x][y+1] != wall && (maze[x][y+1] == 0 || maze[x][y+1] > count + 1)){
            //cout << maze[x][y+1] << "\tAs , x : "<< x << " y+1 : " << y+1 << endl;
            //cout << "count + 1 : " << count + 1 << endl;
            maze[x][y+1] =  count + 1;
            //cout << "Run as right . " << endl;
            push(g_s_stack_for_maze, x ,y+1 , count + 1);
        }
        //cout << g_t_stack_for_temp -> count << " : COUNT " << endl;
        //cout << x << " : X " << endl << y << " : Y " << endl;
        delete g_t_stack_for_temp;
        if(g_s_stack_for_maze == NULL) break;
    }
    recycle(g_s_stack_for_maze);
    //recycle(g_t_stack_for_temp);
    int founder = maze[row-1][col-1];
    //cout << "Max = maze[row-1][col-1] : " << founder << endl;
    maze[row - 1][col - 1] = 1;
    int _i = row - 1 , _j = col - 1;
    while(founder != 1){
        if(_i+1 < row && maze[_i+1][_j] == founder - 1){
            founder --;
            _i = _i + 1;
            maze[_i][_j] = 1;
        }else if(_i-_j >= 0 && maze[_i-1][_j] == founder - 1){
            founder --;
            _i = _i - 1;
            maze[_i][_j] = 1;
        }else if(_j+1 < col && maze[_i][_j+1] == founder -1){
            founder --;
            _j = _j + 1;
            maze[_i][_j] = 1;
        }else if(_j-1 >= 0 && maze[_i][_j-1] == founder - 1){
            founder --;
            _j = _j - 1;
            maze[_i][_j] = 1;
        }else {
            //cout << "The maze is unsoloved ~ ." << endl;
            return 1;
        }
    }
    for(int l = 0 ; l < row ; l++){
        for(int m = 0 ; m < col ; m++){
            if(maze[l][m] != row * col && maze[l][m] != 1) maze[l][m] = 0;
        }
    }
    cout << "The maze get result as : " << endl;
    for(int sub = 0 ; sub < col - 1; sub++)
        cout << "---------" ;
    cout << "<" << endl;
    for(i = 0 ; i < row ; i++){
        for(j = 0 ; j < col ;j++)
        {
            cout << maze[i][j] << '\t' ;
        }
        cout << endl;
    }

    for(int sub = 0 ; sub < col - 1; sub++)
        cout << "---------" ;
    cout << ">" << endl;
    /**stack * temp = new stack(1125,2,2,NULL);
       temp = new stack(2544584,2,2,temp);
       temp = new stack(384,3,3,temp);
       /**cout << pop(temp) -> x << endl;
       cout << pop(temp) -> x << endl;
       cout << pop(temp) -> x << endl;
       cout << pop(temp) -> x << endl;*/
    //recycle(temp);
    //delete maze;

    return 0;
}
