#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

void CalculateNorm(double ** matrix, int norm, int rows, int cols)
{
    double sum = 0;
    if(rows == 1)
    {
        switch (norm)
        {

        case 1:
        {
            for(int i = 0; i < cols; i++)
            {
                sum += pow(matrix[0][i], 2);
            }
            break;
        }

        case 2:
        {
            for(int i = 0; i < cols; i++)
            {
                sum += pow(matrix[0][i], 2);
            }
            sum = sqrt(sum);
            break;
        }

        case 5:
        {
            break;
        }

        case 'f':
        case 'F':
        {
            break;
        }

        default:
        {

            break;
        }

        }
        for(int i = 0; i < cols; i++)
        {
            sum += pow(matrix[0][i], 2);
        }
    }
    else
    {

    }
    cout << sum << endl;
}

int main(int argc, char *argv[])
{
    double ** matrix;
    matrix = new double*[1];
    matrix[0] = new double[4]();
    for(int i = 0; i < 4; i++)
    {
        matrix[0][i] = i * i;
    }
    CalculateNorm(matrix, 1, 1, 4);
    return 0;
}
