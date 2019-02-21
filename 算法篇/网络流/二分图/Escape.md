---
title: Escape
date: 2019-02-21 15:05
update: 2019-02-21 15:05
author: Rainboy
---

## 题目
    
- [题目地址](https://vjudge.net/problem/HDU-3605)

### 题目大意:

$N(1<=N<=10^6)$个人从$earth$去$M(1<=M<=10)$个星球，每个人只能去其适应的星球，每个星球有容量$V_i(0<=V_i<=10^6)$问是否都能离开$earth$。

## 解析

主要在于建图,下面给出一组数据

```
5 3
1 1 0
1 0 1
0 0 1
1 0 1
0 1 0
2 2 3
```

建立最简单的图如下:
```viz-dot
digraph G {
    rankdir=LR;
    node[shape=circle];
    n1,n2,n3,n4,n5;
    m1,m2,m3;

    edge[label=1];
    ranksep=1.5;
    S->{n1,n2,n3,n4,n5};
    n1->{m1,m2};
    n2 ->{m1,m3};
    n3 ->{m3};
    n4 ->{m1,m3};
    n5 ->{m2};


    m1->T[label=2];
    m2->T[label=2];
    m3->T[label=3];
}
```

但是针对数据$1<=n<=100000$,$m<=10$,我们是无法建立这么多条边来做最大流的,

我们发现$m$比较少,所有可以选择的星球的状态最多有$2^{10} = 1024$种,所以我们可以这样建图

 - $S$连接某个选择状态人,容量为人数
 - 状态人连接对应的星球,容量为人数
 - 星球连接$T$,容量为星球的容纳人数

例如上面的数据我们可以建立如下的图:

```viz-dot
digraph G {
    rankdir=LR;
    node[shape=circle];
    ranksep=1.5;
    n1[label="100"];
    n2[label="010"];
    n3[label="101"];
    n4[label="011"];
    m1,m2,m3;

    edge[label=1];
    S->{n1,n2,n4};
    S->n3[label=2];
    n1->{m3};
    n2 ->{m2};


    n3 ->{m1,m3}[label=2];
    n4 ->{m1,m2};


    m1->T[label=2];
    m2->T[label=2];
    m3->T[label=3];
}
```
其中$101$为二进制,表示这点的人数有两个,都是选择$m1,m3$星球的人.

这里我们用到了**缩点**:把多个点当成一个点


## 代码

```c
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n,m;

int state[1024+5];
int m_cap[20];
int S =0,T;
#define maxn 5000

/* 得到m点的编号 */
#define getM(x) ((1<<m)-1)+x

/* ================= 向量星 =================*/
int head[maxn];
int edge_cnt = 0;
struct _e{
    int u,v,cap,next;
}e[maxn<<3];

void inline xlx_init(){
    memset(head,-1,sizeof(head));
}

void addEdge(int u,int v,int w){
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].cap = w;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}
/* ================= 向量星 end =================*/

void init(){
    xlx_init();
    memset(state,0,sizeof(state));
    int i,j,k,t;
    S = 0;
    T = getM(m)+1;
    for (i=1;i<=n;i++){
        int s = 0;
        for(j=1;j<=m;j++){
            scanf("%d",&t);
            if(t)
                s |= (1<<(j-1));
        }
        state[s]++;

    }
    for (i=1;i<=m;i++){ //读取星球的容量
        scanf("%d",&m_cap[i]);
    }
    for(i=1;i<(1<<m);i++){ //建立图
        if( state[i] == 0) continue;

        // S-> state[i]
        addEdge(S,i,state[i]);
        addEdge(i,S,0);

        // state[i] -> m
        for(j=0;j<m;j++){
            if( (1<<j) & i){ // 和第(j+1)个星球有联系
                addEdge(i,getM(j+1),state[i]);
                addEdge(getM(j+1),i,0);
            }
        }
    }
    //m -> T
    for(i=1;i<=m;i++){
        addEdge(getM(i),T,m_cap[i]);
        addEdge(T,getM(i),0);
    }
}

int dep[maxn];
int cur[maxn];
bool bfs(){ //分层
    memset(dep,-1,sizeof(dep));
    queue<int> q;
    q.push(S);
    dep[S] = 0;
    while( !q.empty()){
        int u= q.front(); q.pop();
        int i;
        for(i=head[u];i!=-1;i = e[i].next){
            int v = e[i].v;
            if( e[i].cap > 0 && dep[v] == -1){
                dep[v] = dep[u]+1;
                q.push(v);
            }
        }

    }
    return dep[T] != -1;
}

int dfs(int u,int low){

    if( u == T) return low;

    int ret = low;
    int i;
    for(i=cur[u];i!=-1;i = e[i].next){
        cur[u] = i;
        int v= e[i].v;

        if( e[i].cap > 0 && dep[v] == dep[u]+1){
            int flow = dfs(v,min(ret,e[i].cap));

            e[i].cap -= flow;
            e[i^1].cap += flow;
            ret -= flow;
            if(!ret) break;
        }
    }

    if( ret == low) dep[u] = -1;
    return low -ret;
}


int dinic(){
    int tmp = 0;
    while( bfs()){
        int i;
        for(i=S;i<=T;i++)
            cur[i] = head[i];
        tmp += dfs(S,0x7f7f7f7f);
    }
    return tmp;
}


int main(){
    while(scanf("%d%d",&n,&m) !=EOF){
        init(); // 读取数据 与建图
        int ans = dinic();
        if( ans == n)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
```

## 参考/引用

 - [HDU3605: Escape-二进制优化建图-最大流 - Cwolf9](https://www.cnblogs.com/Cwolf9/p/9418994.html)
