# Little Kings

题目地址:[sgu223](https://vjudge.net/problem/SGU-223)

## 题目描述

在$$n \times n,1<=n<=10$$的棋盘上放$$k,1<=k<=n \times n$$个国王(可攻击相邻的8个格子),求使它们无法互相攻击的方案总数.

## 输入格式

输入有多组数据,每组只有一行为两个整数n和k

## 输出格式
每组数据输出一行为方案总数,若不能放置则输出0

## 输入样例

```
3 2
4 4
```

## 输出样例

```
16
152
```


## 解析

能搜索吗?好像很难.

你会发现第$$i+1$$行的放置状态只有第$$i$$行的状态有关.

f[i][j][k] 前i行,有k个国王且第i的状态为state[j]的条件下的方案数.

那么,状态转移方程为:



```math

f[i][j][k] \leftarrow f[i-1][j_1][k_1]

k_1+num(a[j]) = k

f[i][j][k] = max { f[i][j][k], f[i-1][j_1][k_1]+ \sum state[j]}

```
$$a(j_1) $$与$$a(j)$$不冲突

边界:$$f[0][0][0] = 0$$表示前0行,状态为a[0],且放0个国王的方案数为0


为了操作简单,我们可以先枚举一行的所有可能状态.`同一行相邻的国王的距离必须 大于 1`


枚举一行可能性的代码:

```c
int a[20] = {0};
int state[500];
int cnt = 0;

int arr2bin(){
    int i;
    int s = 0;
    for(i=n;i>=1;i--){
        if( a[i] )
            s = s |(1 <<(i-1));
    }
    return s;
}

void dfs(int dep){
    //边界
    if(dep == n+1){
        int t = arr2bin();
        state[cnt] = t;
        cnt++;
        return;
    }

    a[dep] = 0;  //不放
    
    dfs(dep+1);

    //放
    if(a[dep-1] == 0) // 前1个格子没有
    {
        a[dep] = 1;
        dfs(dep+1);
        a[dep] = 0;
    }
}
```


## 代码

```c
/* little kings sgu 223*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

typedef long long ll;

//输出二进制
void p_bin(ll n){
    char a[20];
    char b[20] = {0};
    ll idx= 0;
    while(n){
        ll t = n & 1;
        a[idx++] = t +'0';
        n = n >>1;
    }
    
    ll i;
    for(i=0;i<idx;i++)
        b[i] = a[idx-i-1];

    printf("%s\n",b);

}

ll n,K;

ll f[20][200][101];
ll a[20] ={0};
ll state[200] = {0};
ll num[200];
ll cnt = 0; //一行的可能放法数

ll numof1(){
    ll i, t = 0;
    for(i=1;i<=n;i++)
        if(a[i])
            t++;
    return t;
}

ll arr2bin(){
    ll i;
    ll s = 0;
    for(i=n;i>=1;i--){
        if( a[i] )
            s = s |(1 <<(i-1));
    }
    return s;
}

//枚举一行放法数
void dfs(ll dep){
    //边界
    if(dep == n+1){
        ll t = arr2bin();
        state[cnt] = t;
        num[cnt] = numof1();
        cnt++;
        return;
    }

    a[dep] = 0;  //不放
    dfs(dep+1);

    //放
    if(a[dep-1] == 0) // 前1个格子没有
    {
        a[dep] = 1;
        dfs(dep+1);
        a[dep] = 0;
    }
}


void dp(){

    memset(f,0,sizeof(f));
    f[0][0][0] = 1; //边界

    ll i,j,k,l;
    //开始dp
    for(i=1;i<=n;i++) //枚举前i行
        for(j=0;j<cnt;j++)  //第i行的状态
            for(k=0;k<=K;k++) //前i行的国王数
                if(num[j] <= k ){ //第i行的状态j要小于可能放置的数量
                    for(l=0;l<cnt;l++){ //枚举第i-1行的状态
                            if(  (state[j] & state[l]) == 0  && 
                                 ((state[j] <<1 ) & state[l]) == 0 &&
                                 ((state[j] >>1 ) & state[l]) == 0 
                              ){ //第i行 与 第i-1行不冲突

                                //dp 方程
                                f[i][j][k] += f[i-1][l][k-num[j]];
                            }
                    }
                }
    ll ans = 0;
    for(i=0;i<cnt;i++){
        ans+= f[n][i][K];
    }
    printf("%lld\n",ans);
}
int main(){

    while( scanf("%lld%lld",&n,&K) != EOF){
        memset(a,0,sizeof(a));
        cnt = 0;
        dfs(1); // 枚举一行的可能放置数
        dp();
    }
    
    return 0;
}
```
