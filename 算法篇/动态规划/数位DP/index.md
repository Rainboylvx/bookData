---
_id: "4ddae18be0"
title: 数位DP：序
date: 2020-10-14 15:31
update: 2020-10-14 15:31
author: Rainboy
cover: 
---

## 什么是数位DP

数位DP就是说我们DP转移的过程和**数的位置有关**.

luogu 题目列表:
https://www.luogu.org/problemnew/lists?name=&orderitem=pid&tag=141&content=0&type=

## 模板
<!-- template start -->
数据dp本质上是在树上行走的过程
```c
namespace DIGIT_DP {
    typedef long long ll;
    ll f[30][10][200],a[100];
    //pre 前面加起来mod 位
    ll dfs(int pos,int pre,int n,bool lead,bool eq){
        if( pos == 0 ) {
            if( n == 0) return 1;
            else return 0;
        }
        if( !eq && f[pos][pre][n] !=-1) return f[pos][pre][n];
        ll ret = 0;
        int ed = eq ? a[pos] : 9;
        for(int i = 0;i<= ed ; i++){
            ret += dfs(pos-1,i,((n+N-i%N)+N) % N,lead && i == 0 ,eq && i == ed);
        }
        if( !eq )f[pos][pre][n] = ret;
        return ret;
    }

    ll solve(int n){
        if( n==0) return 1;
        ll k = 0;ll sum=0;
        while( n) a[++k] = n%10,sum+=n%10,n/=10;
        memset(f,-1,sizeof(f));
        ll ans = dfs(k,0,0,1,1);
        //if( sum % N == 0) ans++;
        return ans;
    }
}
```
<!-- template end -->
