#include <iostream>

using std :: string;

void MinHeapFixup(int a[] , int i){
    int j , temp;
    temp = a[i];
    j = (i - 1) / 2;
    while(j >= 0 && i != 0){
        if(a[j] <= temp)
            break;
        a[i] = a[j];
        i = j;
        j = (i - 1) / 2;
    }
    a[i] = temp;
}

int main(int argc , char ** argv){

    return 0;
}
