

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


**代码**

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
/*-------------------------------------------------
*  Author:Rainboy
*  2018-08-14 15:47
*-------------------------------------------------*/
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int n,m,S,tot,Next[500010],head[20000],tree[500010],val[500010];
bool visit[20000];
long long dis[20000];
struct cmp
{
    bool operator()(int a,int b)
    {
        return dis[a]>dis[b]; //小根堆
    }
};
priority_queue<int,vector<int>,cmp> Q;
void add(int x,int y,int z)
{
    tot++;
    Next[tot]=head[x];
    head[x]=tot;
    tree[tot]=y;
    val[tot]=z;
}
int main()
{
    scanf("%d%d%d",&n,&m,&S);
    tot=0;
    for (int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        if (x==y) continue;
        add(x,y,z);
    }
    for (int i=1;i<=n;i++) 
    {
        visit[i]=false;
        dis[i]=2147483647;
    }
    Q.push(S);
    dis[S]=0;
    while (!Q.empty())
    {
        int u=Q.top();
        Q.pop();
        if (visit[u]) continue; // 取出的点已经标记过了,不进行运算
        visit[u]=true;
        for (int i=head[u];i;i=Next[i])
        {
            int v=tree[i];
            if (!visit[v]&&dis[v]>dis[u]+(long long)val[i])
            {   
                dis[v]=dis[u]+val[i];
                Q.push(v);
            }
        }
    }
    for (int i=1;i<=n-1;i++) printf("%lld ",dis[i]);
    printf("%lld\n",dis[n]);
    return 0;
}
```

## 练习题目

 - luogu P3371 【模板】单源最短路径
 - luogu P1078 文化之旅

