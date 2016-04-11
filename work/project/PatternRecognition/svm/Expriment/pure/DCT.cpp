#include <iostream>

void initDCTParam(int deg)
{
    // deg 为DCT变换数据长度的幂

    if(bHasInit)
    {
        return; //不用再计算查找表
    }

    int total, halftotal, i, group, endstart, factor;

    total = 1 << deg;

    if(C != NULL) delete []C;

    C = (double *)new double[total];

    halftotal = total >> 1;

    for(i=0; i < halftotal; i++)
        C[total-i-1]=(double)(2*i+1);

    for(group=0; group < deg-1; group++)
    {

        endstart=1 << (deg-1-group);

        int len = endstart >> 1;

        factor=1 << (group+1);

        for(int j = 0;j < len; j++)
            C[endstart-j-1] = factor*C[total-j-1];
    }

    for(i=1; i < total; i++)
        C[i] = 2.0*cos(C[i]*PI/(total << 1)); ///C[0]空着，没使用

    bHasInit=true;
}










void dct_forward(double *f,int deg)
{
    // f中存储DCT数据

    int i_deg, i_halfwing, total, wing, wings, winglen, halfwing;

    double temp1,temp2;

    total = 1 << deg;

    for(i_deg = 0; i_deg < deg; i_deg++)
    {
        wings = 1 << i_deg;
        winglen = total >> i_deg;
        halfwing = winglen >> 1;
        for(wing = 0; wing < wings; wing++)
        {
            for(i_halfwing = 0; i_halfwing < halfwing; i_halfwing++)
            {
                temp1 = f[wing*winglen+i_halfwing];
                temp2 = f[(wing+1)*winglen-1-i_halfwing];
                if(wing%2)
                    swap(temp1,temp2); // 交换temp1与temp2的值
                f[wing*winglen+i_halfwing] =
                    temp1+temp2;
                f[(wing+1)*winglen-1-i_halfwing] =
                    (temp1-temp2)*
                    C[winglen-1-i_halfwing];
            }
        }
    }
}


using namespace std;
int main(int argc , char ** argv){

    return 0;
}
