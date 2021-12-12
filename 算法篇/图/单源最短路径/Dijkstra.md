---
_id: "17d1c1837f"
title: Dijkstra
date: 2020-05-15 09:48
update: 2020-05-15 09:48
author: Rainboy
---


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

![二个图](/images/二个图.png)


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

## 代码-普通版

时间复杂度：$O(n^2)$
::: fold
```c
<%- include("code/dijkstra_normal.cpp") %>
```
:::


## Dijkstra + 堆优化

代码模板：时间复杂度：$O(nlog(n))$
<!-- template start -->
```c
struct Dijkstra {
    int dis[maxn];
    bool vis[maxn];
    typedef pair<int,int> P; //第一个存dis，第二个存点编号
    priority_queue<P,vector<P>,greater<P>> q; //优先队列
    Dijkstra(){ //格构函数
        memset(dis,0x7f,sizeof(dis)); //所有的点都是0x7f7f7f7f 代表无穷大
        memset(vis,0,sizeof(vis));    //所有点都是没有标记的
        //注意这里起点也未标记的
    }

    void work(int s,linkList& e){
        dis[s] = 0; 
        q.push(make_pair(0, s)); //把起点加入

        while ( !q.empty() ) { //当优先队列不空时
            int u = q.top().second;
            q.pop();
            if( vis[u] ) continue; //这个点已经标记过了，什么也不做
            vis[u] = 1; //标记这个点

            //用新标记的点去更新它周围的末标记点
            for(int i=e.h[u];~i;i=e[i].next){
                int &v = e[i].v, &w = e[i].w;
                if( vis[v] == 0 && dis[v] > dis[u]+w){
                    dis[v] = dis[u] + w;
                    q.push(make_pair(dis[v], v)); //新更新的点加入队列
                }
            }
        }
    }
} dijkstra;
```
<!-- template end -->

完整代码

::: fold
```c
<%- include("code/dijkstra_better.cpp") %>
```
:::


## 练习题目

但我们发现每次找一个最近点有点耗时，因为要支持减值和求最小的操作，就用小根堆.

为了减少代码量,这里我们使用**STL中的priority_queue**,优先队列.

题目: [luogu P3371 【模板】单源最短路径（弱化版）](https://www.luogu.org/problemnew/show/P3371)

```c
todo
```

## 练习题目

 - luogu P3371 【模板】单源最短路径
 - luogu P1078 文化之旅

