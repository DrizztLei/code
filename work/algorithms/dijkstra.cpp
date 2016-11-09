#include <stdio.h>
#define MAXVEX 9
#define INFINITY 65536
typedef int Pathmatrix[MAXVEX];
typedef int ShortPathTable[MAXVEX];

void ShortPathTable(MGrapth , int , Pathmatrix * , ShortPathTable *);

void ShortestPath_Dijkstra(MGrapth G , int v_ , Pathmatrix *P , ShortPathTable *D){
    int v , w , k , min;
    int final[MAXUEX];
    for(v = 0 ; v < G.numVertexes; v++){
        final[v] = 0;
        (*D)[v] = G.matrix[v_][v];
        (*P)[v] = 0;
    }
    (*D)[v_] = 0;
    final[v_] = 1;
    for(v = 1 ; v < G.numVertexes ; v++){
        min = INFINITY;
        for(w = 0 ; w < G.numVertexes ; w++){
            if(!final[w] && (*D)[w] < min){
                k = w;
                min = (*D) [w];
            }
        }
        final[k] = 1;
        for(w = 0 ; w < G.numVertexes ; w++){
            if(!final[w] && (min + G.matrix[k][w] < (*D)[w]))
            {
                (*D)[w] = min + G.matrix[k][w];
                (*P)[w] = k;
            }
        }
    }
}

int main(int argc, char ** argv)
{
    return 0;
}
