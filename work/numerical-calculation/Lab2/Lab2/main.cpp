#include<stdio.h>
#include<math.h>
//判断是否是素数
int isPrime(int n)
{
    int flag=1;
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            flag=0;
            break;
        }
    }
    return flag;
}
//数字循环
int fun(int n)
{
    int a = n%10;//取出最后一位  比如12345得出a=5
    int b = n/10;//取出前面4位                b=1234
    return a*10000+b; //经典的循环返回， 5*10000+1234=51234
}
int main()
{
    int i,j;//i代表需要求的数字，从99999到10000，j代表数字需要循环5次
    int count;
    int temp;
    for(i=99999;i>=10000;i--)//在所有的5位数中从最大开始找起
    {
        temp = i;
        count = 0;//切记要在这里把count的值赋为0，千万别在外面赋值，因为每次求一个数字i它的count值都要变为0不然的花就会求得99971是结果
        for(j=0;j<5;j++)//因为5位数的话就要循环5次
        {
            if(isPrime(temp))
            {
                //printf("%d\t",temp);//错误，因为有些素数循环2、3次后就不是素数了，就不应该输出，O(∩_∩)O
                count++;
                temp=fun(temp);//调用fun函数，实现循环的判断是否还是素数
            }
        }
        if(count==5)//如果循环5次那可以确定5次都是素数了
        {
            printf("\n%d\n",i);
            break;//找到了就跳出循环，结束
        }
    }
    return 0;
}
