#include <iostream>
#include <queue>
using namespace std;

const int MaxSize=10;
template<class DataType>
class MGraph
{
public:
	MGraph(DataType a[] , int n , int e);
	~MGraph();
	void DFSTraverse(int v);
	void BFSTraverse(int v);
private:
	DataType vertex[MaxSize];
	int arc[MaxSize][MaxSize];
	static int vertexNum , srcNum;
	int visited[];
};

template<class DataType>
MGraph<DataType> :: ~MGraph(){
	delete [] vertex;
	for(int i = 0 ; i < MaxSize ; i++)
		delete [] arc[i];
}

template<class DataType>
MGraph<DataType> :: MGraph(DataType a[] , int n , int e)
{
	int vertexNum = n ;
	visited[vertexNum];
	int arcNum = 0;
	for(int i = 0 ; i < vertexNum ;i++)
		vertex[i] = a[i];
	for(int i = 0 ; i < vertexNum ; i++)
		for(int j = 0 ; j < vertexNum ; j++)
			arc[i][j] = 0;
	int i , j;
	for(int k = 0 ; k < arcNum ; k++) 
		{
			cin >> i >> j;
			arc[i][j] = arc[j][i] = 1;
		}
}

template<class DataType>
void MGraph<DataType> :: DFSTraverse(int v)
{
	cout << vertex[v] ;
	visited[v] = 1;
	for(int j = 0 ; j < vertexNum ; j++)
		if(arc[v][j] == 1 && visited[j] == 0) DFSTraverse(j);
}

template<class DataType>
void MGraph<DataType> :: BFSTraverse(int v)
{
	queue<int> Q;
	int front = -1 ,  rear = -1;
	cout << vertex[v] ;
	visited[v] = 1;
	Q.push(v);
	//Q[++rear] = v;
	while(front != rear){
		v = Q.pop();
		for(int j = 0 ; j < vertexNum ; j++)
			if(arc[v][j] == 1 && visited [j] == 0){
				cout << vertex[j] ;
				visited[j] = 1;
				Q.push(j);
			}
	}
}   

int main(int artc , char ** argv){

	return 0;
}
