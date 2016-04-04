#include <iostream>
using namespace std;

struct node{
	int x , y;
	node * next;
};

void enQueue(node * front , node * tail , int x , int y){
	if(front == NULL) front = tail = new node;
	else tail = tail -> next = new node;
	tail -> x = x;
	tail -> y = y;
	tail -> next = NULL;
}

void deQueue(node * front , int & x , int & y){
	node * p = front;
	front = front -> next;
	x = p -> x;
	y = p -> y;
	delete p;
}

int main(int argc , char ** argv){
	node * front = NULL , * tail = NULL;
	int * * maze;
	int row , col , i , j ,wall;
	int curX , curY ;
	cout << "Input the cube : (row and col)" << endl;
	cin >> row >> col;

	wall = row * col;

	maze = new int * [row];
	for(int i = 0 ; i < row ; i++){
		maze[i] = new int[col];
		cout << "Input the " << i << " row (0 for entry wall, " << wall <<" for the wall , seprator for space .):" ;
		for(j = 0 ; j < col ; ++j)
			cin >> maze[i][j];
	}
	enQueue(front , tail , 0 , 0);
	while(front != NULL){
		deQueue(front , curX , curY);
		if(curX != 0 && maze[curX -1][curY ] == 0){
			if(curX-1 != 0 || curY != 0){
				maze[curX-1][curY] = maze[curX][curY] +1;
				enQueue(front , tail , curX-1 , curY);
			}
		}
		if(curX == row -1 && curY==col-2) break;
		if(maze[curX][curY+1] == 0){
			maze[curX][curY+1] = maze[curX][curY] + 1;
			enQueue(front , tail , curX , curY + 1);
		}
		if(curX == row -2 && curY == col - 1) break;
		if(maze[curX + 1] [curY] == 0){
			maze[curX+1][curY] = maze[curX][curY] +1;
			enQueue(front , tail , curX , curY-1);
		}

		if(curY != 0 && maze[curX][curY-1] == 0){
			if(curX != 0 || curY != 0){
				maze[curX][curY-1] = maze[curX][curY]+1;
				enQueue(front , tail , curX , curY-1);
			}
		}
	}
	maze[row-1][col-1] = maze[curX][curY] + 1;
	int length = maze[row-1][col-1]+1;
	int * pathX = new int[length] , * pathY = new int[length];

	curX = row -1 ; curY = col -1;
	while(curX != 0 || curY != 0){
		pathX[maze[curX][curY]] = curX;
		pathY[maze[curX][curY]] = curY;
		if(curX!= 0 && maze[curX-1][curY]<maze[curX][curY]){
			curX=curX - 1;continue;
		}
		if(curX != row - 1 && maze[curX + 1][curY] < maze[curX][curY]){
			curY = curX + 1;continue;
		}
		if(curY != 0 && maze[curX][curY-1] < maze[curX][curY]){
			curY = curY -1 ; continue;
		}
		if(curY != 0 && maze[curX][curY+1] < maze[curX][curY]){
			curY = curY - 1; continue;
		}
	}
	pathX[0]=curX;pathY[0]=curY;
	cout << "Result is "<<endl;
	for(int i = 0 ; i < length - 1 ; i ++)
		cout << "(" << pathX[i] <<", " << pathY[i] << ") ->";
	cout << "(" << pathX[length-1] << ", "<<pathX[length-1] <<")" <<endl;
	return 0;
}
