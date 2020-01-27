---
title: 01BFS
date: 2019-09-30 13:40
update: 2019-09-30 13:40
author: Rainboy
---


@[toc]

## 知识网络

```viz-dot
graph g {
    node[shape=circle];
    rankdir=BT;
    subgraph cluster_1{
        label="A*"
            subgraph cluster_2{
                label="Dijkstra"
                    subgraph cluster_3{
                        label="01BFS"
                            a[label="BFS" shape=record];
                    }
            }
    }
}
```
$BFS$,$01BFS$,$Dijkstra$,$A*$,本质上用的都是同一种思想.如上图,它们是一种包含关系.例如,$BFS$是$01BFS$的一种特例,$Dijkstra$是$A*$特例.

## 背景

在一个边全部为$1$的图$G$上求最短路的时候,可以用普通的队列$BFS$.如果是在一个边只是$0$或$1$的图上求最短路呢?

```viz-dot
graph g {
    node[shape=circle];
    a--b[label=1];
    d--c[label=0];
    b--c[label=1];
    a--d[label=0];
    c--e[label=1];
    b--e[label=0];
    {
        rank="same";
        a,b;
    }
    {
        rank="same";
        c,d,e;
    }
}
```

## 算法过程

::: blackboard
<!-- template start -->
使用双端队列$deque$

 - 从$0$边拓展到的点放入队首
 - 从$1$边拓展到的点放入队尾
 - 每次从队首取点,直到队列为空
<!-- template end -->
:::


## 原理解析

为什么上面的方法是正确的呢?我们需要从$BFS$的原理来思考.

我们以水流的拓展(蔓延)，来理解$BFS$.

想象有一个时钟，在计时。计时的单位为一。每过一个时刻。水流就会向周围的点蔓延。当水流到达这个点的时刻。就是最短路.

为什么我们要采用队列呢?

很明显，队列头部的点要比后边的点。花费的时间要少(小于等于)那么从时间上来考虑，一定是队列头部的点先进行活动

所以，队列的本质就是对点的优先级进行排列。优先级高的点，先活动.

我们可以把这种思想带入到$01BFS$上.

## 代码模板

<!-- template start -->
```c
<%- include("01bfs_template.cpp") %>
```
<!-- template end -->

## 样例题目

## 题目列表

cf1064D. Labyrinth(01BFS)
