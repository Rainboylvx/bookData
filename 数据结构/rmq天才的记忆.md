## 题目

题目地址:[vijos 1541](https://vijos.org/p/1514)

## 解析
标准RMQ问题,直接使用模板代码.

## 代码

```c
#include<iostream>
#include<cstdio>
using namespace std;
const int N = 200010;

int a[N];
int f[N][20],n,m;

void st(){
    for(int i = 1;i <= n; i++)f[i][0]=a[i];
    for(int j = 1;(1<<j)<=n;j++)
        for(int i = 1;i+(1<<j)-1<=n;i++)
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}
int query(int L,int R)
{
    int k = 0;
    while((1<<(k+1))<=R-L+1)k++;
    return max(f[L][k],f[R-(1<<k)+1][k]);
}

void init(){
    scanf("%d",&n);
    for(int i= 1;i <= n; i++)
        scanf("%d",&a[i]);
    scanf("%d",&m);
}

int main()
{
    init(); //读取数据
    st(); //预处理
    for(int i = 1;i <= m; i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
    }
    return 0;
}
```

