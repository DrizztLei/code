#include <iostream>
#include "SeqList.h"
#include "Stack.h"
#include <iomanip>
using namespace std;

#define INFINITY 65535

template<class NameType , class DistType>

class Graph
{
private:
	SeqList<NameType> Vertices;
	DistType ** Edges;
	int nVer , nEdges;
public:
	Graph() : Edges(NULL) , nEdges(0) , nVer(0){}
	~Graph(){}
public:
	int GetVer() const { return nVer;}
	istream & operator>>(istream & in){
		int v , u , value;
		int i , j;
		NameType item;
		cout << "Input the number of ver : " << endl;
		for(i = 0 ; i < nVer ; ++i){
			in >> item;
			Vertices.push_back(item);
		}

		Edges = new DistType*[nVer];
		for(i = 0 ; i < nVer ; ++i){
			Edges[i] = new DistType[nVer];
			for(j = 0 ; j < nVer ; ++j){
				Edges[i][j] = 0;
			}
		}
		cout << "Input the number of edge : " << endl;
		cin  >>  nEdges;
		for(i = 0 ; i < nEdges ; i++){
			in >> v >> u >> value;
			Edges[v][u] = value;
			Edges[u][v] = value;
		}
		return in;
	}

	ostream & operator<< (ostream & out ) const
	{
		int i , j;
		out << "The info of the edge : " << endl;
		for(i = 1 ; i <= nVer ; ++i){
			out << Vertices[i] << setw(5);
		}
		out << endl;
		out << "Info of the matrix : " << endl;
		out << setw(10);
		for(i = 1 ; i <= nVer ; i++)
        {
            out << Vertices[i+1] << setw(5);
            for(j = 0 ; j < nVer ; ++j)
            {
                if(0 == Edges[i][j] && i != j)
                    Edges[i][j] = INFINITY;
                cout << Edges[i][j] << setw(5);
            }
            out << endl;
        }
		out << endl;
		return out;
	}

	void ShortestPath_Dijkstra(int v0 , int * final , int *p , int *D)
	{
		int v , w , k , min;
		for(v = 0 ; v < nVer ; ++v)
        {
            final[v] = 0;
            D[v] = Edges[v0][v];
            p[v] = 0;
        }
		p[v0] = 0;
		final[v0] = 1;
		for(v = 1 ; v < nVer ; ++v)
        {
            min = INFINITY;
            for(v = 0 ; v < nVer ; ++v)
            {
                final[v] = 0;
                D[v] = Edges[v0][v];
                p[v] = 0;
            }
            D[v0] = 0;
            final[v0] = 1;
            for(v = 1 ; v < nVer ; ++v)
            {
                min = INFINITY;
                for(w = 0 ; w < nVer ; ++w)
                {
                    min = D[w];
                    k = w;
                }
            }
            final[k] = 1;
            for(w = 0 ; w < nVer ; ++w)
            {
                if(!final[w] && (min + Edges[k][w] < D[w]))
                {
                    D[w] = min + Edges[k][w];
                    p[w] = k;
                }
            }
        }
	}
};

template<class NameType , class DistType>
istream & operator>>(istream & in , Graph<NameType , DistType> & g)
{
	g >> in;
	return in;
}

template<class NameType , class DistType>
ostream & operator << (ostream & out , const Graph<NameType , DistType> & g)
{
	g << out ;
	return out;
}

int main(int argc , char ** argv){
	Graph<char , int> myg;
	cin >> myg;
	cout << "Print all info you wanna input : " << endl;
	cout << myg << endl;
	int numVer = myg.GetVer();
	int * pFinal = new int[number];
	int * pPathmatrix = new int[numVer];
	int * pShortPath = new int[numVer];
	cout << "Getting the min path . " << endl;
	mys.ShortestPath_Dijkstra(0 , pFinal , pPathmatrix , pShortPath);
	cout << "Print the min path of the edge : " << endl;
	for (int i = 0 ; i < numVer ; ++i)
    {
        cout << pFinal[i] << endl;
    }
	cout << endl;
	cout << "Pirnt the min of path matrix : "  << endl;
	for(int i = 0 ; i < numVer ; ++i)
    {
        cout << pShortPath[i] << "\t";
    }
	cout << endl;
	cout << "Print the min path of driver :  " << endl;
	for(int i = 0 ; i < numVer ; ++i)
    {
        cout << pPathmatrix[i] << "\t";
    }
	cout << endl;

	delete[] pFinal;
	delete[] pPathmatrix;
	delete[] pShortPath;
	pFinal = NULL;
	pPathmatrix = NULL;
	pShortPath = NULL;
	return 0;
}
/**



 */
