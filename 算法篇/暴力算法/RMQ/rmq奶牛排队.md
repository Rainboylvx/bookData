## 题目

题目地址:[Balanced Lineup排队](https://vjudge.net/problem/HYSBZ-1699)

## 分析

题目说了,读取的数据和写出的数据都很大! 所以我们使用了快读,快写.

```c
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

#define N 50000

int n,q,l,r;
int mx[N+5][25],mn[N+5][25];
inline char nc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
    int x=0,b=1;
    char c=nc();
    for(;!(c<='9'&&c>='0');c=nc())if(c=='-')b=-1;
    for(;c<='9'&&c>='0';c=nc())x=x*10+c-'0';
    return x*b;
}
inline void write(int x)
{
    if(x==0)putchar('0');
    else
    {
        char buf[15];
        int len=0;
        if(x<0)putchar('-'),x=-x;
        while(x)buf[++len]=x%10+'0',x/=10;
        for(int i=len;i>=1;i--)putchar(buf[i]);
    }
    putchar('\n');
}
inline int get_mx(int l,int r)
{
    int x=log2(r-l+1);
    return max(mx[l][x],mx[r-(1<<x)+1][x]);
}
inline int get_mn(int l,int r)
{
    int x=log2(r-l+1);
    return min(mn[l][x],mn[r-(1<<x)+1][x]);
}
int main()
{
    n=read();q=read();
    for(int i=1;i<=n;i++)mn[i][0]=mx[i][0]=read();
    for(int i=1;i<=20;i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            mn[j][i]=min(mn[j][i-1],mn[j+(1<<(i-1))][i-1]),
            mx[j][i]=max(mx[j][i-1],mx[j+(1<<(i-1))][i-1]);
    for(int i=1;i<=q;i++)
        l=read(),r=read(),write(get_mx(l,r)-get_mn(l,r)); 
    return 0;
}
```
