---
title: sap算法
date: 2019-02-10 00:07
update: 2019-02-10 00:07
author: Rainboy
cover: https://i.loli.net/2019/02/10/5c5efa9cb1665.gif
---

## sap算法

最短路增广算法($Shortest\ Augument\ Path,SAP$)

## 算法步骤


$SAP$最短增广路算法步骤

采用队列$q$来存放已访问未检查的结点。布尔数组$vis[]$标识结点是否被访问过，$pre[]$数组记录可增广路上结点的前驱。$pre[v]＝u$表示可增广路上$v$结点的前驱是$u$，最大流值 $maxflow＝0$。

 1. 初始化可行流$flow$为零流，即实流网络中全是零流边，残余网络中全是最大容量边(可增量).
 2. 初始化$vis[]$数组为 $false$，$pre[]$数组为$-1$.令$vis[s] = true$，$s$加入队列$q$
 3. 如果队列不空，继续下一步，否则算法结束，找不到可增广路。当前的实流网络就是最大流网络，返回最大流值 $maxflow$
 4. 队头元素$new$出队，在残余网络中检查$new$的所有邻接结点$i$如果未被访问，则访问之，令$vis[i] = true$，$pre[i] = new$；如果$i==t$，说明已到达汇点，找到一条可增广路，转向第(5)步；否则结点i加入队列$q$，转向第(3)步。
 5. 从汇点开始，通过前驱数组$pre$，逆向找可增广路上每条边值的最小值，即可增量$d$
 6. 在实流网络中增流，在残余网络中减流， $Maxflow += d$，转向第(2)步


## 代码

### 题目描述

求下图的最大流,边上的值代表最大容量.

```viz-neato
digraph G {
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label=12];
    v1->v3[label=8];
    v3->T[label=18];


    v2->v1[label=2];

    v4->v3[label=6];
    v3->v2[label=5];

    S->v2[label=10];
    v2->v4[label=13];
    v4->T[label=4];
}
```

### 数据输入

 - 第一行$n,m,s,t$,分别表示,点的数量,边的数据,源点,汇点
 - 接下$m$行,每行$u,v,c$,一条弧的起点,终点,容量

```
6 9 0 5
0 1 12
0 2 10
2 1 2
1 3 8
2 4 13
3 2 5
4 3 6
4 5 4
3 5 18
```

### 数据输出

一行,最大流的大小

```
18
```

### 代码

```c
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define maxn 200
const int INF = 0x7fffffff/3;

int n,m,s,t;

/* ================= 向量星 =================*/
int head[maxn];
int edge_cnt = 0;
struct _e{
    int flow,u,v,c,next; //flow 这条边的容量
}e[maxn<<2];

void inline xlx_init(){
    memset(head,-1,sizeof(head));
}

void addEdge(int u,int v,int c,int flow){

    e[edge_cnt].u= u;
    e[edge_cnt].v= v;
    e[edge_cnt].c=c;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;

    e[edge_cnt].flow = flow;

    edge_cnt++; //注意这里,我们从0的编号开始存边
}
/* ================= 向量星 end =================*/


void init(){
    xlx_init();
    
    scanf("%d%d%d%d",&n,&m,&s,&t);

    int i,j;
    int tu,tv,tc;
    for (i=1;i<=m;i++){
        scanf("%d%d%d",&tu,&tv,&tc);
        addEdge(tu,tv,tc,tc); //残余网络中的正向边
        addEdge(tv,tu,0,tc); //残余网络中的反向边
    }
}

/* ====== BFS ===== */

int pre[maxn]; // pre[v] 表示 u->v 这条边的编号
int vis[maxn];
bool bfs(int s,int t){
    memset(pre,-1,sizeof(pre));
    memset(vis,0,sizeof(vis));
    queue<int> q;       //队列
    vis[s] = true;
    q.push(s);

    while(!q.empty()){ //非空
        int now = q.front();
        q.pop();

        int i;
        for(i = head[now];i !=-1;i = e[i].next){
            
            int v = e[i].v;
            if( !vis[v] && e[i].c >0){ //没有被访问过,且可以走
                vis[v] = 1;
                pre[v] = i;     //边的编号
                if( v == t)     //是汇点,找到了一条路
                    return true;
                q.push(v);
            }
        }
    }

    return false; //没有找到找增广路
}

/* ====== BFS END===== */



int sap(int s,int t){
    int v,w,d,maxflow=0;

    while( bfs(s,t)){ //可以增广
        v = t;
        d= INF;
        while(v != s){
            int idx = pre[v];
            w = e[idx].c;
            if( d > w)
                d = w;
            v = e[idx].u;
        }
        maxflow+=d;
        v=t;

        while(v != s){ // 没可增广路增流
            int idx = pre[v];

            e[idx].c -=d; //正向边减流
            e[idx^1].c +=d; //反向边增流
            v = e[idx].u;

        }
    }


    return maxflow;
}

int main(){
    init();
    int ans = sap(s,t);
    printf("%d",ans);
    return 0;
}
```

## 总结

$sap$算法是一种时间复杂度很高的算法,因为**每一次BFS只能增广一条路**,你可以选择更好的算法,如$Dinic$,$ISAP$
