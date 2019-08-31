#include <cstdio>
#include <cstring>
#include <cmath>


int exgcd(int a,int b,int &x,int &y){//ax+by=gcd(a,b)
    if(b==0){x=1,y=0;return a;}
    int gcd=exgcd(b,a%b,x,y);
    int _x=x;
    x=y;
    y=_x-(a/b)*y;
/*
    int gcd=exgcd(b,a%b,y,x);
    y-=(a/b)*x;
*/
    return gcd;
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    int x,y;
    int t = exgcd(n,m,x,y);

    int m1 = m / t;
    if( x >= 0)
        printf("%d\n",x % m1);
    else
        printf("%d\n",(x % m1) + m1);
    return 0;
}
