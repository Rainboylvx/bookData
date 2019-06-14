

## Dijkstra算法原理

见下面课件

链接: https://pan.baidu.com/s/1slVt0lf 密码: 6vva


设起点,为s,dis[i]表示,起点s到点i的最短路径的长度,dijkstra过程如下:
 
   - dis[s] = 0,标记点s
   - 用已经标记的点去更新未标记的点
   - 在未标记的点里找一个dis值最小的点,标记它
   - 重复2,3两个步骤,直到的点都标记了,就得到了所有点的dis值

**注意**:Dijkstra 不能处理负权

Dijstra算法:**贪心**

 - 有两个点的集合: A 确定的最短路径的点, B没有确定最短路径的点
 - 每一次从B中找到dis最小的点c,把c加入A
 - 不停这样下去,直到所有点都成为A


---------------------

## 代码

![二个图](/book/images/二个图.png)


输入数据

第一行:n,e;n个点,e条边

第二行:s,t;s起点,t终点

剩下e行:`u v w`分别是一条边的起点,终点,权值

```
5 7
1 5
1 2 2
1 3 4
1 4 7
2 3 1
3 4 1
2 5 2
3 5 6
```

**代码:向量星版本**

```c
/*-------------------------------------------------
*  Author:Rainboy   time:2018-08-19 20:09
*-------------------------------------------------*/
#include <cstdio>
#include <cstring>

#define N 100
#define inf 0x7f7f7f7f

int n,m;
int s,t;
int dis[N]; //每个点到起点的最短距离
bool flag[N] = {0}; //某个点是不是已经标记

int first[N];
int edge_cnt = 0;
struct _e{
    int u,v,w,next;
}e[N<<2];

void addEdge(int u,int v,int w){
    edge_cnt++;
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].w=w;
    e[edge_cnt].next = first[u];
    first[u] = edge_cnt;
}

void init(){
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);
    int i,j,k,l;
    for (i=1;i<=m;i++){
        scanf("%d%d%d",&j,&k,&l);
        addEdge(j,k,l);
        addEdge(k,j,l);
    }

    memset(dis,0x7f,sizeof(dis));
    dis[s] =0;

}

void dijkstra(){
    int i,j;
    for (i=1;i<=n;i++){ //进行ｎ次循环，每次标记一个点
        int min = inf; //记录最小值
        int tmp =-1; // 记录dis最的末标记的点
        for(j=1;j<=n;j++)
            if( flag[j] == 0 && min > dis[j])
                tmp = j, min = dis[j];

        if( tmp == -1)  //证明tmp没有被更新
             return;    //也就是有可能还存在末标记点
                        //但是它的值是无穷，证明从起点到达不了这个点
                        //那就不要再进行算法了

        flag[tmp] = 1; //标记
        //用新标记的点去更新它周围的末标记点
        for(j=first[tmp];j!=-1;j=e[j].next){
            int v  = e[j].v;
            if( flag[v] == 0 && dis[v]>dis[tmp]+e[j].w)
                dis[v]=dis[tmp]+e[j].w;
        }
    }
}
int main(){
    init(); //读取数据
    dijkstra();
    //输出结果
    printf("%d\n",dis[t]);
    return 0;
}
```


**代码:邻接表版本**

```c
/*-------------------------------------------------
*  Author:Rainboy
*  time: 2016-04-11 16:29
*  © Copyright 2016 Rainboy. All Rights Reserved.
*-------------------------------------------------*/

/*
 *  Dijstra算法: -- >贪心
 *      有两个点的集合: A 确定的最短路径的点, B没有确定最短路径的点
 *      每一次从B中找到dis最小的点c,把c加入A
 *      不停这样下去,直到所有点都成为A
 * */

#include <cstdio>
#include <cstring>

#define INF 0x7f7f7f7f
#define max_e 999
#define max_v 999

int dis[max_v];
bool vis[max_v]={0}; //判断是不是标记的点

int G[max_v][max_v];//二维数组来存图
int pre[max_v] ={0};

int n,m;//点和边的数量
int s,t;//起点 终点

void diskstra(int s){

    memset(dis,0x7f,sizeof(dis));
    dis[s] = 0; //起点dis 为0
    int i,j;

    /* 计算n次,因为每一次加入一个数进vis */
    for(i=1;i<=n;i++){
        int tmp=-1,min = INF;

        /* 找到未标记点中最小的 */
        for(j=1;j<=n;j++)
            if(!vis[j] && dis[j] < min)
                min = dis[j] ,tmp=j;

        if( tmp!= -1)//是否找到
            vis[tmp]=1;
        else 
            break;

        /* 用找到的tmp去更新其它点 */
        for(j=1;j<=n;j++)
            if(G[tmp][j] != INF && !vis[j] ) //相邻边,且可以更新
                if(dis[j] >G[tmp][j]+dis[tmp]){
                    dis[j] = dis[tmp]+G[tmp][j];
                    pre[j] =tmp;
                }
    }
}

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);

    //读取图
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            G[i][j]=INF;
    for(i=1;i<=m;i++){
        scanf("%d%d",&j,&k);
        scanf("%d",&G[j][k]);
        G[k][j]=G[j][k];
    }

    diskstra(s);

    //输出
    printf("dis[%d]=%d\n",t,dis[t]);
    //输出路径
    for(i=t;i!=0;i=pre[i])
        printf("%d ",i);
    return 0;
}
```


## Dijkstra + 堆优化( 没有写完)

但我们发现每次找一个最近点有点耗时，因为要支持减值和求最小的操作，就用小根堆.

为了减少代码量,这里我们使用**STL中的priority_queue**,优先队列.

```c
//dijkstra优先队列 堆优化
#include <bits/stdc++.h>
using namespace std;
#define inf 2147483647
#define N 200001

int n,m,s;
int dis[N];
bool vis[N];

priority_queue <pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;

struct ee{int u,v,w,next;}e[500000+100];
int ecnt=0,head[N];
void ae(int x,int y,int w){
    ecnt++;
    e[ecnt].v=y;
    e[ecnt].next=head[x];
    head[x]=ecnt;
    e[ecnt].w=w;
}

void dijkstra(int s){
    for(int i=1;i<=n;i++){
        dis[i]=inf;
    }
    dis[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty()){
        int now=q.top().second;
        q.pop();
        if(vis[now])continue;
        vis[now]=1;
        for(int i=head[now];i;i=e[i].next){
            if(dis[e[i].v]>dis[now]+e[i].w){
                dis[e[i].v]=dis[now]+e[i].w;
                q.push(make_pair(dis[e[i].v],e[i].v));
            }
        }
    }
}

int main(){
    memset(vis,0,sizeof(vis));
    scanf("%d%d%d",&n,&m,&s);
    int t1,t2,t3;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&t1,&t2,&t3);
        ae(t1,t2,t3);
    }

    dijkstra(s);
    for(int i=1;i<=n;i++){
        printf("%d ",dis[i]);
    }

    return 0;
}
```

## 练习题目

 - luogu P3371 【模板】单源最短路径
 - luogu P1078 文化之旅

