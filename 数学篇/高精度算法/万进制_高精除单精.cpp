/* 万进制 高精除单精 */
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

void div(int len){
    int i,mod, x = 0;
    for(i=len;i>=1;--i){ //从高位到低位
        c[i] = (x*base2+a[i]) /b;
        x = (x*base2+a[i]) % b;
    }
}


int main(){
    
    int la = str2num(num, a);
    div(la);
    int pos = la;
    for( ; pos >=1&& c[pos] == 0;) pos--;

    printf("%d",c[pos]);
    for(--pos;pos>=1;--pos)
        printf("%04d",c[pos]);

    return 0;
}
