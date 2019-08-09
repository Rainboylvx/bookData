/* 高精乘单精 */
#include <bits/stdc++.h>
using namespace std;

const int base = 4;
const int base2 = 10000;

char num[] = "450004000050000";
int b = 2809;
int a[400];
int c[400];

int str2num(char x[],int y[]){
    int i,j=1,k=1;
    int lenx= strlen(x);
    for(i=lenx-1;i>=0;i--){
        if(k==base2) j++,k=1;
        y[j] += k*(x[i]-'0');
        k*=10;
    }
    return j;
}

int mul(int a[],int len,int b,int c[]){
    int i;
    for(i=1;i<=len;i++){
        c[i] = a[i] *b;
    }

    for(i=1;i<=len;i++){
        c[i+1] += c[i] / base2;
        c[i] %= base2;
    }
    if( c[len+1] != 0)
        len++;
    return len;
}

int main(){
    int len = str2num(num,a);
    int len_c = mul(a, len, b, c);
    
    int i;
    printf("%d",c[len_c]);
    for(i=len_c-1;i>=1;--i){
        printf("%04d",c[i]);
    }
    return 0;
}
