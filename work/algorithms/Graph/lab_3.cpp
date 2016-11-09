#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <boost/algorithm/string.hpp>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace boost;

template<class E>
struct node
{
    E info;
    bool isVisit;
};

template<class T , class E>
class graph
{
public:
    graph();
    node<E> * Graph;
    void DFS(int n, int falg);
    void SimpleRing(int n = 0);
    void SimpleRing(int n, int father);
    bool invalid( int i , int l , vector<T> iterator);
    void InnerForward(int count , int i = 0 , int j = 0 );
    bool forward(int n = 0);
    void show();
    bool adjust();
    bool contain(vector<int>& seq, int aim);
    bool erase(vector<int>& seq, int index);
    void TSP();
    void DealInput();
    void init();
    void BFS(int n = 0);
    void DFS(int n = 0);
    void reset();
    void OutputTree();
    void OutputMin();
    bool FindEuler(int index = 0);
    bool FindEuler(int index, int father);
    virtual ~graph();
    friend bool sort_by_value(const int& obj1, const int& obj2);
private:
    vector<int> sequence;
    vector<int> path;
    vector<vector<int> > ring;
    vector<int> tsp;
    int ** matrix = NULL;
    int ** weight = NULL;
    int ** copy = NULL;
    int ** euler = NULL;
    int length = -1;
    int start = -1;
};

template<class T , class E>
bool graph<T , E> :: erase(vector<int>& seq, int index)
{
    vector<int>::iterator it = seq.begin() + index;
    seq.erase(it);
}


// template<class T , class E>
bool sort_by_value(const int& obj1, const int& obj2)
{
    return obj1 > obj2;
}


template<class T , class E>
void graph<T , E> :: reset()
{
    for(int i = 0 ; i < length ;i++)
    {
        Graph[i].isVisit = false;
    }
}


template<class T , class E>
void graph<T , E> ::  BFS(int n)
{
    cout << "IN BFS > " << endl;
    vector<int> left;
    vector<int> right;
    left.push_back(n);
    while(left.size() != 0 || right.size() != 0)
    {
        if(left.size())
        {
            int Size = left.size();
            for(int i = 0 ; i < Size ; i++)
            {
                cout << "Visit the node " << Graph[left[i]].info << " . " << endl;
                Graph[left[i]].isVisit = true;}
            for(int i = 0 ; i < Size ; i++)
            {
                for(int k = 0 ; k < length ; k++)
                {
                    if(matrix[k][left[i]] && (!Graph[k].isVisit))
                    {
                        Graph[left[i]].isVisit = true;
                        right.push_back(k);
                    }
                }
            }
            left.clear();
        }
        else
        {
            int Size = right.size();
            for(int i = 0 ; i < Size ; i++)
            {
                cout << "Visit the node " << Graph[right[i]].info << " . " << endl;
                Graph[right[i]].isVisit = true;
            }
            for(int i = 0 ; i < Size ; i++)
            {
                for(int k = 0 ; k < length ; k++)
                {
                    if(matrix[k][right[i]] && (!Graph[k].isVisit))
                    {
                        Graph[right[i]].isVisit = true;
                        left.push_back(k);
                    }
                }
            }
            right.clear();
        }
    }
    reset();
}


template<class T, class E>
void graph<T, E> :: DFS(int n)
{
    DFS(n , -1);
    for(int i = 0 ; i < length ; i++)
    {
        if(!Graph[i].isVisit)
        {
            DFS(i, -1);
        }
    }
    reset();
}


template<class T, class E>
void graph<T, E> :: DFS(int n, int father)
{
    cout << "Visit the node " << Graph[n].info << " . " << endl;
    Graph[n].isVisit = true;
    for(int i = 0 ; i < length ; i++)
    {
        if(matrix[n][i] && (!Graph[i].isVisit))
        {
            Graph[i].isVisit = true;
            DFS(i , n);
        }
    }
}


template<class T , class E>
void graph<T , E> :: SimpleRing(int n)
{
    sequence.push_back(n);
    SimpleRing(n , -1);
    for(int i = 0 ; i < length ; i++)
    {
        if(!Graph[i].isVisit)
        {
            sequence.clear();
            sequence.push_back(i);
            DFS(i, -1);
        }
    }
    for(int i = 0 ; i < ring.size() ; i++)
    {
        cout << "ring for : " << i+1 << endl;
        sort(ring[i].begin, ring[i].end, graph::sort_by_value);
        for(int j = 0; j < ring[i].size() - 1 ; j++)
        {
            cout << ring[i][j] << "->" ;
        }
        cout << ring[i][ring[i].size()-1];
        cout << endl;
    }
    reset();
}


template<class T , class E>
void graph<T , E> ::  SimpleRing(int n , int father)
{
    cout << "Visit the node " << Graph[n].info << " . " << endl;
    Graph[n].isVisit = true;
    for(int i = 0 ; i < length ; i++)
    {
        if(matrix[n][i] && i != n)
        {
            if(contain(sequence, i))
            {
                if(i != n && i != father)
                {
                    cout << "--------------->" << endl;
                    cout << "now " << n << endl;
                    cout << "find " << i << endl;
                    cout << "father " << father << endl;
                    cout << "size " << sequence.size() << endl;
                    for(int l = 0 ; l < sequence.size() ; l++)
                    {
                        cout << sequence[l] << "\t";
                    }
                    cout << endl;
                    ring.push_back(vector<int>());
                    bool flag = false;
                    for(int k = sequence.size()-1; k >= 0 ; k--)
                    {
                        if(sequence[k] == i)
                        {
                            flag = true;
                            break;
                        }
                        ring[ring.size()-1].push_back(sequence[k]);
                    }
                    if(ring[ring.size()-1].size() == 0)
                    {
                        ring.pop_back();
                    }
                    else if(!flag)
                    {
                        ring.pop_back();
                    }
                    else
                    {
                        ring[ring.size()-1].push_back(i);
                        ring[ring.size()-1].push_back(n);
                        for(int l = 0 ; l < ring[ring.size()-1].size() ; l++)
                        {
                            cout << ring[ring.size()-1][l] << endl;
                        }
                    }
                    cout << "--------------->" << endl;
                }
            }
            else
            {
                Graph[i].isVisit = true;
                sequence.push_back(i);
                SimpleRing(i , n);
                sequence.pop_back();
            }
        }
    }
}


template<class T , class E>
void graph<T , E> :: OutputTree()
{
    if(copy != NULL)
    {
        for(int i = 0 ;i < length ; i++)
        {
            delete[] copy[i];
        }
    }

    copy = new int* [length];

    for(int i = 0 ; i < length ; i++)
    {
        copy[i] = new int[length];
    }
    int count = 0;
    for(int i = 0 ; i < length ; i++)
    {

        for(int j = i ; j < length ; j++)
        {
            // copy[i][j] = copy[j][i] = matrix[i][j];
            copy[i][j] = matrix[i][j];
            copy[j][i] = matrix[j][i];
            if(matrix[i][j] == 1)
            {
                count++;
                // cout << "Get the connect of " << i << " and " << j << endl;
            }
        }
    }

    cout << "----------------------->" << endl;
    InnerForward(count);
    reset();
}


template<class T , class E>
void graph<T , E> :: InnerForward(int count , int i , int j)
{
    if(count < length - 1)
    {
        return;
    }
    if(j + 1 == length)
    {
        j = ++ i;
    }
    else
    {
        j ++;
    }
    if(count == length - 1 && i == length && j == length)
    {
        int ** temp = new int * [length];
        for(int i = 0 ; i < length ; i++)
            temp[i] = new int[length];
        for(int i = 0 ; i < length ; i++)
            for(int j = i ; j < length ; j++)
                temp[i][j] = temp[j][i] = copy[i][j];
        if(adjust())
        {
            cout << "Find the tree " << endl;
            copy = temp;
            show();
        }
        copy = temp;
        reset();
        return ;
    }
    else if(i == length && j == length)
    {
        return;
    }
    if(copy[i][j] == 1)
    {
        InnerForward(count , i , j);
        copy[i][j] = copy[j][i] = 0;
        InnerForward(count - 1 , i , j);
        copy[i][j] = copy[j][i] = 1;
    }
    else
    {
        InnerForward(count , i , j);
    }
}


template<class T , class E>
void graph<T , E> :: show()
{
    cout << "------------------------------------------------------>" << endl;
    for(int l = 0 ; l < length ; l++)
    {
        for(int m = l ; m < length ; m++)
        {
            if(copy[m][l] == 1) cout << "Connect the " << m << " and  " << l << endl;
        }
    }
    cout << "------------------------------------------------------<" << endl;
}


template<class T , class E>
bool graph<T , E> :: forward(int n)
{
    for(int i = 0 ; i < length ; i++)
    {
        if(copy[n][i] == 1)
        {
            copy[n][i] = copy[i][n] = 0;
            Graph[i].isVisit = true;
            Graph[n].isVisit = true;
            forward(i);
        }
    }
}


template<class T , class E>
bool graph<T , E> :: adjust()
{
    forward();
    for(int i = 0 ; i < length ; i++)
    {
        if(!Graph[i].isVisit) return false;
    }
    for(int i = 0 ; i < length ; i++)
        delete[] copy[i];
    return true;
}


template<class T , class E>
void graph<T , E> :: OutputMin()
{
    if(euler == NULL)
    {
        euler = new int*[length];
        for(int i = 0 ; i < length ; i++)
        {
            euler[i] = new int[length]();
        }
    }

    for(int i = 0 ; i < length ; i++)
    {
        for(int j = 0 ; j < length ; j++)
        {
            weight[i][j] = matrix[i][j] == 0 ? 1024 : i + j;
            weight[j][i] = weight[i][j];
            euler[i][j] = 0;
        }
    }

    for(int i = 0 ; i < length ; i++)
    {
        for(int j = 0 ; j < length ; j++)
        {
            cout << weight[i][j] << "\t";
        }
        cout << endl;
    }

    int min = weight[0][0];
    vector<T> iterator;
    vector<T> edge;
    int select_i = 0 , select_j = 0;
    bool flag = true;

    for(int i = 0 ; i < length ; i++)
    {
        for(int j = 0 ; j < length - i; j++)
        {
            if(min > weight[i][j])
            {
                min = weight[i][j];
                select_i = i;
                select_j = j;
                flag = false;
            }
        }
    }

    if(flag)
    {
        return;
    }

    iterator.push_back(select_i);
    iterator.push_back(select_j);
    euler[select_i][select_j] = 2;
    euler[select_j][select_i] = 2;
    edge.push_back(min);
    bool isSelected = true;

    while(!flag && iterator.size() != length)
    {
        int size = iterator.size();
        int min , select;
        for(int i = 0 ; i < size ; i++)
        {
            for(int j = 0 ; j < length ; j++)
            {
                if(invalid(iterator[i] , j , iterator) && (isSelected || min > weight[iterator[i]][j]))
                {
                    min = weight[iterator[i]][j];
                    select = j;
                    flag = true;
                    if(isSelected)
                    {
                        isSelected = false;
                    }
                }
            }
        }
        if(flag)
        {
            euler[iterator[iterator.size()-1]][select] = 2;
            euler[select][iterator[iterator.size()-1]] = 2;
            iterator.push_back(select);
            edge.push_back(min);
            flag = false;
            isSelected = true;
        }
        else
        {
            break;
        }
    }
    cout << "Output the min tree order : " << endl;
    for(int i = 0 ; i < iterator.size() ; i++)
    {
        cout << iterator[i] << endl;
    }
    cout << "Output the min edge order : " << endl;
    for(int i = 0 ; i < edge.size() ; i++)
    {
        cout << edge[i] << endl;
    }
    iterator.clear();
    reset();
}


template<class T , class E>
bool graph<T , E> :: invalid(int i , int l , vector<T> iterator)
{
    if(matrix[i][l] == 0) return false;
    for(int j = 0 ; j < iterator.size() ; j++)
    {
        if(l == iterator[j]) return false;
    }
    return true;
}


template<class T , class E>
void graph<T ,E> :: init()
{
    int length = 50;
    this -> length = length;
    matrix = new E * [length];
    weight = new int * [length];

    for(int i = 0 ; i < length ; i++ )
    {
        matrix[i] = new int[length]();
        weight[i] = new int[length]();
    }
    Graph = new node<T>[length];

    for(int i = 0 ; i < length; i++)
    {
        for(int j = 0 ; j < length; j++)
        {
            if(i != j)
            {
                matrix[i][j] = 1;
            }
        }
    }

    matrix[0][1] = 1;
    matrix[0][5] = 1;
    matrix[1][2] = 1;
    matrix[1][5] = 1;
    matrix[2][3] = 1;
    matrix[2][4] = 1;
    matrix[4][1] = 1;
    matrix[5][2] = 1;

    matrix[1][0] = 1;
    matrix[5][0] = 1;
    matrix[2][1] = 1;
    matrix[5][1] = 1;
    matrix[3][2] = 1;
    matrix[4][2] = 1;
    matrix[1][4] = 1;
    matrix[2][5] = 1;

    Graph[0].info = 0;
    Graph[1].info = 1;
    Graph[2].info = 2;
    Graph[3].info = 3;
    Graph[4].info = 4;
    Graph[5].info = 5;
    copy = new int * [length];
}


template<class T , class E>
graph<T , E> :: graph()
{
    DealInput();
}


template<class T , class E>
graph<T , E > :: ~graph()
{

    if(matrix != NULL && weight != NULL && copy != NULL && Graph != NULL)
    {
        for(int i = 0 ; i < length ; i++)
        {
            delete[] matrix[i];
            delete[] weight[i];
            delete[] copy[i];
        }
        delete[] matrix;
        delete[] weight;
        delete[] copy;
        delete[] Graph;
    }

    cout << "FREE THE MEMORY" << endl;
}


template<class T, class E>
bool graph<T, E> ::contain(vector<int> & seq, int aim)
{
    for(int i = 0 ; i < seq.size() ; i++)
    {
        if(seq[i] == aim)
        {
            return true;
        }
    }
    return false;
}


template<class T, class E>
void graph<T, E>::TSP()
{
    tsp.clear();

    OutputMin();

    cout << "Output the euler graph : " << endl;

    for(int i = 0; i < length ; i++)
    {
        for(int j = 0 ; j < length ; j++)
        {
            cout << euler[i][j] << "\t";
        }
        cout << endl;
    }

    FindEuler(length/2);

    cout << "Euler ring graph : " << endl;

    for(int i = 0 ; i < path.size() ; i++)
    {
        if(i != path.size()-1)
        {
            cout << path[i] <<"->";
            if(!Graph[path[i]].isVisit)
            {
                Graph[path[i]].isVisit = true;
                tsp.push_back(path[i]);
            }
        }
        else
        {
            cout << path[i] << endl;
            if(!Graph[path[i]].isVisit)
            {
                Graph[path[i]].isVisit = true;
                tsp.push_back(path[i]);
            }
        }
    }

    tsp.push_back(start);

    cout << "TSP graph : " << endl;

    for(int i = 0 ; i < tsp.size() ; i++)
    {
        if(i != tsp.size()-1)
        {
            cout << tsp[i] << "->" ;
        }
        else
        {
            cout << tsp[i] << endl;
        }
    }

    for(int i = 0; i < length ; i++)
    {
        delete[] euler[i];
    }

    delete euler;

    reset();
}


template<class T, class E>
bool graph<T, E>::FindEuler(int index)
{
    start = index;
    for(int i = 0 ; i < length ; i++)
    {
        path.clear();
        if(euler[index][i] != 0)
        {
            path.push_back(index);
            path.push_back(i);

            euler[index][i] --;
            euler[i][index] --;
            if(FindEuler(i, index))
            {
                break;
            }
            else
            {
                euler[index][i] ++;
                euler[i][index] ++;
                path.pop_back();
                path.pop_back();
            }
        }
    }
}


template<class T, class E>
bool graph<T, E>::FindEuler(int index, int father)
{
    for(int i = 0 ; i < length ; i++)
    {
        if(euler[index][i] != 0)
        {
            euler[index][i] --;
            euler[i][index] --;
            path.push_back(i);

            if(path.size() == (length-1) * 2 + 1)
            {
                if(i == start)
                {
                    return true;
                }
                else
                {
                    path.pop_back();
                    euler[index][i] ++;
                    euler[i][index] ++;
                }
            }
            else
            {
                if (FindEuler(i, index))
                {
                    return true;
                }
                else
                {
                    path.pop_back();
                    euler[index][i] ++;
                    euler[i][index] ++;
                }
            }
        }
    }
    return false;
}


template<class T, class E>
void graph<T, E>::DealInput()
{
    string info;
    cout << "Input the length : ";
    getline(cin, info);
    length = std::atoi(info.c_str());

    cout << length << endl;

    if(length < 1)
    {
        init();
    }
    else
    {
        matrix = new E * [length]();
        weight = new int * [length]();
        copy = new int * [length]();

        for(int i = 0 ; i < length ; i++ )
        {
            matrix[i] = new int[length]();
            weight[i] = new int[length]();
        }

        Graph = new node<T>[length]();
        vector<string> tokens;

        for(int i = 0 ; i < length; i++)
        {
            Graph[i].info = i;
            cout << "Input node  " << i << " 's adj : ";
            getline(cin , info);
            tokens.clear();
            info = trim_copy(info);
            split(tokens, info, is_any_of(" "));
            for(int j = 0 ; j < tokens.size() ; j++)
            {
                int aim = atoi(tokens[j].c_str());
                matrix[i][aim] = 1;
            }
        }
    }
}


void test(int i , int size , int * array)
{
    if(i == size)
    {
        for(int l = 0 ; l < size ; l++)
        {
            cout << array[l] << "\t";
        }
        cout << endl;
        return;
    }
    array[i] = 1;
    test(i+1 , size , array);
    array[i] = 0;
    test(i+1 , size , array);
}


int main(int argc , char ** argv)
{
    graph<int , int> TEMP;
    TEMP.TSP();
    return 0;
}
