## 费用用流

给定一个网络 $G=(V,E)$ ，每条边 $(x,y)$ 除了有容量限制 $c(x,y)$ ，还有一个给定的单位费用 $w(x,y)$ 。当边 $(x,y)$ 的流量为 $f(x,y)$ 时，就要花费 $f(x,y)\cdot w(x,y)$ 的费用。该网络中总花费最小的最大流被称为最小费用最大流，花费最大的最大流被称为最大费用最大流，二者合称为费用流模型。需要注意费用流的前提是最大流，然后再考虑费用的最值。

计算费用流一般使用 Edmonds-Karp 算法或 Zkw 费用流，这里仅介绍 Edmonds-Karp 算法。

思路:

 - 建立残余网络
   - 正向边的花费为正
   - 反向边的花费为负
 - 先找出最小费用路
    - 可用$SPFA$
    - $Dijkstra$+堆优化,比较稳定
    - 公式为:$ans += dis[t] \times flow $
 - 在最小费用路上增流减流
 - 重复上面的步骤,直到找到不一条$S \to T$的最短路


## 模板题目

 - [题目地址:luogu P3381 【模板】最小费用最大流](https://www.luogu.org/problemnew/show/P3381)


## 代码:SPFA

**注意**:下面的代码在**luogu p3381**下会$T$四个点!
```c
/*-------------------------------------------------
*  luogu 3381 SPFA代码
*  Author:Rainboy
*  2019-03-11 16:30
*-------------------------------------------------*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define maxn 5005
#define maxe 50005
#define inf 0x3f3f3f3f


int n,m,S,T;

int cost = 0,flow = 0;

int h[maxn] = {0};
int dis[maxn];
int pre_edge[maxn];
int pre_node[maxn];
bool in_que[maxn];


/* ================= 向量星 for flowNet=================*/
int head[maxn];
int edge_cnt = 0;
struct _e{
    int u,v,cap,next,f;
}e[maxe<<1];

void inline xlx_init(){
    edge_cnt = 0;
    memset(head,-1,sizeof(head));
}

void addEdge(int u,int v,int cap,int f){
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].f= f;
    e[edge_cnt].cap=cap;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}
/* ================= 向量星 end =================*/



void in(int &a){
    a = 0;
    int flag = 1;
    char ch = getchar();
    while( ch < '0' || ch > '9'){ if( ch == '-') flag = -1; ch = getchar(); }
    while( ch >= '0' && ch <= '9'){ a = a*10 + ch-'0'; ch = getchar(); }
    a = a*flag;
}


bool spfa(int s,int t){
    memset(dis,0x3f,sizeof(dis));
    memset(in_que,0,sizeof(in_que));

    queue<int> q;
    dis[s] = 0;
    in_que[s] = 1;
    q.push(s);

    while(!q.empty()){
        int u = q.front(); q.pop();
        int i;
        for(i=head[u];i != -1;i = e[i].next){
            int v= e[i].v;

            if( e[i].cap >0 && dis[v] > dis[u]+e[i].f){
                dis[v] = dis[u] + e[i].f;

                if( in_que[v] == 0){
                    q.push(v);
                    in_que[v] =1;
                    pre_edge[v] = i;
                    pre_node[v] = u;
                }
            }
        }
        in_que[u] = 0;
    }

    return dis[t] != inf;

}

void min_cost_flow(int s,int t){
    while( spfa(s,t)){
        int i;
        /* 找增广路 */
        int minflow = inf;
        for(i=t; i!=s;i=pre_node[i]){
            int f = e[pre_edge[i]].cap;
            minflow = min(minflow,f);
        }
        flow += minflow;
        cost += minflow*dis[t];
        /* 增流减流 */
        for(i=t;i!=s;i=pre_node[i]){
            int edge = pre_edge[i];
            e[edge].cap -= minflow;
            e[edge^1].cap += minflow;
        }
    }
}

void init(){
    xlx_init();
    in(n); in(m); in(S); in(T);
    int i,j;
    int t1,t2,t3,t4;
    for (i=1;i<=m;i++){
        in(t1); in(t2); in(t3); in(t4);
        addEdge(t1,t2,t3,t4);
        addEdge(t2,t1,0,-t4);
    }
}
int main(){
    init();
    min_cost_flow(S,T);
    printf("%d ",flow);
    printf("%d\n",cost);
    return 0;
}
```

## 代码:Dijkstra


鉴于现在SPFA人人喊打,以下给出一种使用$Dijkstra$算法的方法.


### 如何解决负边权的问题

$Dijkstra$不能跑含有**负边权**的图

最简单的想法,每一个边都加上一个固定的值,使每条边变成正值

 - 加上后,新的边值可以溢出
 - 计算真正的最短路的值的时候,还要记录边的数量

如果要满足上面的两点,做出来很麻烦.

假如我们已经知道了每个点的到源的最短路径的值$h[i]$,面对任意一条边上的两个点$<u,v>$,同样我们设$w$表示$<u,v>$边的权值

```viz-dot
digraph g {

    nodesep=1;
    ranksep=1;
    u[xlabel="h[u]"]
    v[xlabel="h[v]"]
    edge[arrowhead=vee];
    {
        rank=same;
        u->v[label="w"];
    }
    u->S[style=dashed,arrowhead=none,dir=both,arrowtail=vee];
}
```
根据**最短路的性质**,有以下的公式成立:
$$
h[v] - h[u] <= w
$$

变形得:

$$
h[u]-h[v]+w >= 0
$$

那么我们就让这个边的权值改成:$h[u]-h[v]+w$,就可以满足所有跑的边权都是**非负**的了!就可以用$Dijkstra$算法了

$$
dis[v] = \\\\
(h[S]-h[1]+w1) + (h[1]-h[2]+w2) + (h[2]-h[3]+w2) + \cdots + (h[u]->h[v]+w<u,v>)
$$

因为$h[S] == 0$,所以可以得到如下的公式:

$$
dis[v] + h[v]= \sum w
$$


$\sum w$是我们**真正需要的真实的最短路的值**.

**想一想1**:每次我们就$Dijkstra$求完最短路,我们都要更新$h[i]$为最新的真实的最短路的值,也哪是

```c
for(i=1;i<=n;i++)
    h[i] += dis[i];
```

**想一想2**:每次我们就$Dijkstra$求完最短路,还需要对$S \to T$的最短路径进行增流减流操作,会不会破坏:$h[u]-h[v]+w <=0$?

我们设一个正的边权为$w$,那么它对应的反向边就是$-w$,那么 $w' = -w+h[v]-h[u]$,也就是$-(h[u]-h[v]+w) <= 0$,那么会不会出现$<0$呢?
其实不会,因为我们增广的路径就是最短路,也就是$h[u]+w=h[v]$,那么就不会出现反边是负数,就是一直为$0$了!


```viz-dot
digraph g {

    rankdir=LR
    u->v[xlabel=w,minlen=2];
    v->u[xlabel="-w",minlen=2];
    {
        nodesep=0.1;
        node[shape=plaintext]
        1[label="h[u]"]
        2[label="h[v]"]
        1->u[style=invis,minlen=0.1];
        2->v[style=invis,minlen=0.2];
    }

}
```

**想一想3**:这里做法能保证求出来的最短路径就是我们需要的最短路径吗?

todo!暂时没有想出来

**想一想4**:第一次求$h[i]$可以不可以用$Dijkstra$?

可以,因为最初的残余网络的反向边的花费为负值,但容量为$0$.


### 代码:开O2优化可以过 Luogu p3381

```c
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define maxn 5005
#define maxe 50005
#define inf 0x3f3f3f3f


int n,m,S,T;

int cost = 0,flow = 0;

int h[maxn] = {0};
int dis[maxn];
int pre_edge[maxn];
int pre_node[maxn];


/* ================= 向量星 for flowNet=================*/
int head[maxn];
int edge_cnt = 0;
struct _e{
    int u,v,cap,next,f;
}e[maxe<<1];

void inline xlx_init(){
    edge_cnt = 0;
    memset(head,-1,sizeof(head));
}

void addEdge(int u,int v,int cap,int f){
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].f= f;
    e[edge_cnt].cap=cap;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}
/* ================= 向量星 end =================*/



void in(int &a){
    a = 0;
    int flag = 1;
    char ch = getchar();
    while( ch < '0' || ch > '9'){ if( ch == '-') flag = -1; ch = getchar(); }
    while( ch >= '0' && ch <= '9'){ a = a*10 + ch-'0'; ch = getchar(); }
    a = a*flag;
}

typedef pair<int,int> P;
/* 找最短路 */
bool dijkstra(int s,int t){

    priority_queue<P,vector<P>,greater<P> > pq;
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;
    pq.push(P(0,s));    //起点加入

    while(!pq.empty()){
        P now = pq.top();
        pq.pop();

        if( dis[now.second] < now.first) continue;

        int u = now.second;

        int i;
        for(i=head[u];i !=-1 ;i = e[i].next){
            int v = e[i].v;

            int len = e[i].f+h[u]-h[v];
            if( e[i].cap > 0 && dis[u]+ len < dis[v]){
                dis[v] = dis[u] + len;
                pre_edge[v] = i;
                pre_node[v] = u;
                pq.push(P(dis[v],v));
            }

        }

    }

    return dis[t] != inf;
}

void min_cost_flow(int s,int t){
    while( dijkstra(s,t)){
        int i;
        for(i=1;i<=n;i++)
            h[i] += dis[i];

        /* 找增广路 */
        int minflow = inf;
        for(i=t; i!=s;i=pre_node[i]){
            int f = e[pre_edge[i]].cap;
            minflow = min(minflow,f);
        }
        flow += minflow;
        cost += minflow*h[t];
        /* 增流减流 */
        for(i=t;i!=s;i=pre_node[i]){
            int edge = pre_edge[i];
            e[edge].cap -= minflow;
            e[edge^1].cap += minflow;
        }
    }
}

void init(){
    xlx_init();
    in(n); in(m); in(S); in(T);
    int i,j;
    int t1,t2,t3,t4;
    for (i=1;i<=m;i++){
        in(t1); in(t2); in(t3); in(t4);
        addEdge(t1,t2,t3,t4);
        addEdge(t2,t1,0,-t4);
    }
}
int main(){
    init();
    min_cost_flow(S,T);
    printf("%d ",flow);
    printf("%d\n",cost);
    return 0;
}
```



## 参考/引用

 - [最小费用最大流(详解+模板) by  Bartholomew_](https://blog.csdn.net/qq_39809664/article/details/79109811)
 - [从入门到精通: 最小费用流的“zkw算法”](https://artofproblemsolving.com/community/h1020435)

