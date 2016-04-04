#include <iostream>
#include "SeqList.h"
#include "Stack.h"
#include <iomanip>
using namespace std;

#define  INFINITY  65535

template<class NameType, class DistType>
class Graph
{
private:
    SeqList<NameType> Vertices;
    DistType **Edges;
    int nVer, nEdges;

public:
    Graph()
		: Edges(NULL)
		, nEdges(0)
		, nVer(0)
        {}
    ~Graph()
        {}

public:
    int GetVer() const
        {
            return nVer;
        }

    istream & operator>>(istream &in)
        {
            int v, u, value;
            int i, j;
            NameType item;
            cout << "请输入顶点的个数: " << endl;
            in >> nVer;
            cout << "请输入顶点的数据信息: " << endl;
            for (i = 0; i < nVer; ++i)
			{
				in >> item;
				Vertices.push_back(item);    // 保存全部顶点
			}
            /////二维数组的创建并初始化
            Edges = new DistType*[nVer]; // DistType *ar[10];
            for (i = 0; i < nVer; ++i)
			{
				Edges[i] = new DistType[nVer];
				for (j = 0; j < nVer; ++j)
                {
                    Edges[i][j] = 0;
                }
			}
            cout << "请输入边的个数: " << endl;
            in >> nEdges;
            cout << "请输入边的信息：" << endl;
            for (i = 0; i < nEdges; ++i)
			{
				in >> v >> u >> value;
				Edges[v][u] = value;
				Edges[u][v] = value;
			}
            return in;
        }
    ostream & operator<<(ostream &out) const
        {
            int i, j;
            out << "顶点信息 " << endl;
            for (i = 1; i <= nVer; ++i)
			{
				out << Vertices[i] << setw(5);
			}
            out << endl;
            out << "矩阵信息：" << endl;
            out << setw(10);
            for (i = 1; i <= nVer; ++i)
			{
				out << Vertices[i] << setw(5);
			}
            out << endl;
            for (i = 0; i < nVer; ++i)
			{
				out << Vertices[i+1] << setw(5);
				for (j = 0; j < nVer; ++j)
                {
                    if (0 == Edges[i][j] && i != j)
                        Edges[i][j] = INFINITY;
                    cout << Edges[i][j] << setw(5);
                }
				out << endl;
			}
            out << endl;

            return out;
        }
    // 迪杰斯特拉算法实现
    void ShortestPath_Dijkstra(int v0, int* final, int*p, int *D)
        {
            int v, w, k, min;
            // 初始化数据
            for (v = 0; v < nVer; ++v)
			{
				final[v] = 0;    // 全部顶点初始化为未知对短路径状态
				D[v] = Edges[v0][v]; //将与V0点有连线的顶点加上权值
				p[v] = 0;    // 初始化路径数组p为0
			}
            D[v0] = 0;    // V0至V0路径为0
            final[v0] = 1;    // final[W]=1表示V0至V0不需要求路径
            // 开始主循环，每次求得V0到某个V顶点的最短路径
            for (v = 1; v < nVer; ++v)
			{
				min = INFINITY;    // 当前所知离V0顶点最近距离
				for (w = 0; w < nVer; ++w) // 寻找离V0最近的顶点
                {
                    if (!final[w] && D[w] < min)
                    {
                        min = D[w]; // w顶点离V0顶点更近
                        k = w;
                    }
                }

				final[k] = 1; // 将目前找到的最近的顶点置为1
				for (w = 0; w < nVer; ++w) // 修正当前最短路径距离
                {
                    // 如果经过V顶点的路径比现在这条路径的长度短的话
                    if (!final[w] && (min + Edges[k][w] < D[w]))
                    {
                        // 说明找到了最短的路径，修改D[w] 和 p[w]
                        D[w] = min + Edges[k][w]; // 修改当前路径长度
                        p[w] = k;
                    }
                }
			}
        }
};

template<class NameType, class DistType>
istream & operator>>(istream &in, Graph<NameType,DistType> &g)
{
    g >> in;
    return in;
}

template<class NameType, class DistType>
ostream & operator<<(ostream &out, const Graph<NameType,DistType> &g)
{
    g << out;
    return out;
}

void main()
{
    Graph<char, int> myg;
    cin >> myg;
    cout << "打印所有输入信息：" << endl;
    cout << myg << endl;
    cout << "求最短路径....." << endl;
    int numVer = myg.GetVer();
    int* pFinal = new int[numVer];
    int* pPathmatirx = new int[numVer];
    int* pShortPath = new int[numVer];
    myg.ShortestPath_Dijkstra(0, pFinal, pPathmatirx, pShortPath);
    cout << "打印各顶点最短路径标记数组值：" << " ";
    for (int i = 0; i < numVer; ++i)
    {
        cout << pFinal[i] << " ";
    }
    cout << endl;
    cout << "打印最短路径数组值：" << " ";
    for (int i = 0; i < numVer; ++i)
    {
        cout << pShortPath[i] << " ";
    }
    cout << endl;
    cout << "打印最短路径前驱数组值：" << " ";
    for (int i = 0; i < numVer; ++i)
    {
        cout << pPathmatirx[i] << " ";
    }
    cout << endl;
    cout << "打印V0到各个顶点最短路径值以及路径信息：" << endl;
    SeqStack<int> sQ;
    for (int i = 1; i < numVer; ++i)
    {
        cout << "V0~V" << i << ": " << pShortPath[i] << endl;

        sQ.Push(pPathmatirx[i]);
        int n = 0;
        while (sQ.GetTop(n) && n != 0)
        {
            sQ.Push(pPathmatirx[n]);
        }

        while (!sQ.IsEmpty())
        {
            int m = 0;
            sQ.Pop(m);
            cout << "V" << m << "->";
        }
        cout << "V" << i << endl;
    }
    delete []pFinal;
    delete []pPathmatirx;
    delete []pShortPath;
    pFinal = NULL;
    pPathmatirx = NULL;
    pShortPath = NULL;
}
// 备注：
// 最短路径迪杰斯特拉算法实现
// 整理于2013-12-04
// 测试输入程序为：
/*
  请输入顶点的个数:
  9
  请输入顶点的数据信息:
  A B C D E F G H I
  请输入边的个数:
  16
  请输入边的信息：
  0 1 1
  0 2 5
  1 2 3
  1 3 7
  1 4 5
  2 4 1
  2 5 7
  3 4 2
  3 6 3
  4 5 3
  4 6 6
  4 7 9
  5 7 5
  6 7 2
  6 8 7
  7 8 4
  打印所有输入信息：
  顶点信息
  A    B    C    D    E    F    G    H    I
  矩阵信息：
  A    B    C    D    E    F    G    H    I
  A    0    1    5655356553565535655356553565535
  B    1    0    3    7    565535655356553565535
  C    5    3    065535    1    7655356553565535
  D65535    765535    0    265535    36553565535
  E65535    5    1    2    0    3    6    965535
  F6553565535    765535    3    065535    565535
  G655356553565535    3    665535    0    2    7
  H65535655356553565535    9    5    2    0    4
  I655356553565535655356553565535    7    4    0


  求最短路径.....
  打印各顶点最短路径标记数组值： 1 1 1 1 1 1 1 1 1
  打印最短路径数组值： 0 1 4 7 5 8 10 12 16
  打印最短路径前驱数组值： 0 0 1 4 2 4 3 6 7
  打印V0到各个顶点最短路径值以及路径信息：
  V0~V1: 1
  V0->V1
  V0~V2: 4
  V0->V1->V2
  V0~V3: 7
  V0->V1->V2->V4->V3
  V0~V4: 5
  V0->V1->V2->V4
  V0~V5: 8
  V0->V1->V2->V4->V5
  V0~V6: 10
  V0->V1->V2->V4->V3->V6
  V0~V7: 12
  V0->V1->V2->V4->V3->V6->V7
  V0~V8: 16
  V0->V1->V2->V4->V3->V6->V7->V8
*/
