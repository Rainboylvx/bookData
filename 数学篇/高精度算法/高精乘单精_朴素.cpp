/* 高精乘单精 */
#include <bits/stdc++.h>
using namespace std;


char num_a[] = "123";
int a[100];
char b = 79;
int c[100];

int mul(int a[],int len,int b,int c[]){
    int i;
    for(i=1;i<=len;i++){
        c[i] = a[i] *b;
    }

    for(i=1;i<=len;i++){
        c[i+1] += c[i] / 10;
        c[i] %= 10;
    }
    if( c[len+1] != 0)
        len++;
    return len;
}

int main(){
    int len = strlen(num_a);
    int i;
    
    /* 字符转数字 */
    for (i=1;i<=len;i++){
        a[i] = num_a[len-i] - '0';
    }
    int len_c = mul(a, len, b, c);
    
    for(i=len_c;i>=1;--i){
        printf("%d",c[i]);
    }

    return 0;
}
