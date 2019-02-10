---
title: 最大流算法:Dinic
date: 2019-01-27 17:45
update: 2019-01-27 17:45
author: Rainboy
cover: https://ww1.sinaimg.cn/large/007i4MEmgy1fzla9krgiug30qg0bk0wk.gif
---

## 连续最短增广路算法-Dinic

$Dinic$算法是一种最短增广路算法,其它的还有$SAP$,$ISAP$等.


为了解决我们上面遇到的低效方法，$Dinic$算法引入了一个叫做**分层图**的概念。具体就是对于每一个点，我们根据从源点开始的$bfs$序列，为每一个点分配一个深度，然后我们进行若干遍$dfs$寻找增广路，每一次由$u$推出$v$必须保证$v$的深度必须是$u$的深度$+1$.


层次图上的任意一条路径都是从$s$到层次$1$到层次$2$……直到$t$，可以发现，每一条这样的路径都是一条$s \to t$最短路，这样求，不会出现走多余的边的情况.


## 分层

顶点的层次：在残留网络中，把从源点到顶点$u$的最短路径长度（该长度仅仅是值路径上边的数目，与容量无关），称为顶点$u$的层次，记为$level(u)$。源点$s$的层次为$0$。

将残留网络中所有的顶点的层次标注出来的过程称为分层。

根据层次网络定义，层次网络中任意的一条弧$<u,v>$，有满足$level(u)+1 == level(v)$，这条弧也叫允许弧。直观的说，层次网络是建立在残留网络基础之上的一张“最短路径图”。从源点开始，在层次网络中沿着边不管怎么走，到达一个终点之后，经过的路径一定是终点在残留网络中的最短路径。

## Dinic 算法过程

```viz-dot
digraph G {
    splines=ortho;
    
    node[shape=box];
    x[shape=point];
    a[label="初始容量网络",shape="Mdiamond"];
    b[label="构造残余网络"];
    c[label="BFS 构造层次网络"];
    d[label="汇点在层次网络中",shape=diamond];

    e[label="DFS 进行增广"]
    f[label="算法结束"]

    a->b->c->d->e;
    e->f[style="invis"];
    
    {
        rank=same;
        x,d,y;
        y[shape=none,label="再次"];
    }
    x:we->d[arrowhead=none,headlabel="否"];

    x:w->f:w[constraint=false];

    e:e->y[constraint=false,arrowhead=none];
    y->c:e[constraint=false];
}
```

**为什么要多次建立层次网络?**

建立**层次网络**可以保证每一次的增广路都是**最短增广路**,为什么每一轮增广后,都要重新建立**层次网络**呢?


因为可能会走**反向边**!


```viz-dot
digraph G {
    rankdir= LR;
    edge[minlen=2];
    node[shape="circle"];
    { rank=same; 1,3; }
    { rank=same; 2,4; }
    { rank=same; 5,6; } 

    1[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>0</TD></TR></TABLE>>]

    2[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>1</TD></TR></TABLE>>]
    3[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>1</TD></TR></TABLE>>]

    4[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>2</TD></TR></TABLE>>]
    5[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>2</TD></TR></TABLE>>]
    6[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>3</TD></TR></TABLE>>]

    edge[label="2"]
    1->2->4->6;
    edge[label="1"]
    1->3->4;
    2->5->6;
}
```

如下图，你会发现：在找到一条增广路径:$1\to2\to4\to6$后,如果还用原来的**层次网络**,就找不到下一条增广路,因为$dep[2] \neq dep[4]+1$

```viz-dot
digraph G {
    rankdir= LR;
    edge[minlen=2];
    node[shape="circle"];
    { rank=same; 1,3; }
    { rank=same; 2,4; }

    { rank=same; 5,6; } 


    1[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>0</TD></TR></TABLE>>]

    2[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>1</TD></TR></TABLE>>]
    3[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>1</TD></TR></TABLE>>]

    4[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>2</TD></TR></TABLE>>]
    5[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>2</TD></TR></TABLE>>]
    6[xlabel=< <TABLE BORDER="0" CELLBORDER="1"><TR><TD>3</TD></TR></TABLE>>]

    edge[weight=3];
    2->5[label="1"];
    3->4[label="1"];

    1->3[label="1"];
    5->6[label="1"];


    edge[weight=1];
    1->2[label="0",style="dashed"];
    2->1[label="2"];

    2->4[label="0",style="dashed"];
    4->2[label="2",constraint=false];

    4->6[label="0",style="dashed"];
    6->4[label="2"];
}
```

## 存储残余网络的方法

## 算法过程模拟

**1.实流网络**

每条边上的值代表最大流量,求**汇点** $T$ 能接收的最大流量是多少?

```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="12"];
    v1->v3[label="8"];
    v3->T[label="18"];


    v2->v1[label=2];

    v4->v3[label=6];
    v3->v2[label=5];

    S->v2[label=10];
    v2->v4[label=13];
    v4->T[label=4];
}
```

**2.根据实流网络初始化残余网络**

其中虚线的边为反向边



```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="12"];
    v1->v3[label="8"];
    v3->T[label="18"];

    v2->v1[label=2];

    v4->v3[label=6];
    v3->v2[headlabel=5,labelangle=-5,labeldistance=8];

    S->v2[label=10];
    v2->v4[label=13];
    v4->T[label=4];


    edge[style=dashed,labeldistance=5]
    v1->S[headlabel=0,labelangle=-10];
    v3->v1[headlabel=0,labelangle=-10];
    T->v3[headlabel=0,labelangle=-10];

    v1->v2[headlabel=0,labelangle=-10];

    v3->v4[headlabel=0,labelangle=-10];
    v2->v3[headlabel=0,labelangle=-5,labeldistance=8];

    v2->S[headlabel=0,labelangle=-10];
    v4->v2[headlabel=0,labelangle=-10];
    T->v4[headlabel=0,labelangle=-10];
}
```


**3.BFS分层**


```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="12"];
    v1->v3[label="8"];
    v3->T[label="18"];

    v2->v1[label=2];

    v4->v3[label=6];
    v3->v2[headlabel=5,labelangle=-5,labeldistance=8];

    S->v2[label=10];
    v2->v4[label=13];
    v4->T[label=4];


    edge[style=dashed,labeldistance=5]
    v1->S[headlabel=0,labelangle=-10];
    v3->v1[headlabel=0,labelangle=-10];
    T->v3[headlabel=0,labelangle=-10];

    v1->v2[headlabel=0,labelangle=-10];

    v3->v4[headlabel=0,labelangle=-10];
    v2->v3[headlabel=0,labelangle=-5,labeldistance=8];

    v2->S[headlabel=0,labelangle=-10];
    v4->v2[headlabel=0,labelangle=-10];
    T->v4[headlabel=0,labelangle=-10];
    
    
    
    S[xlabel=<<font color="blue">[0]</font>>];
    v1[xlabel=<<font color="blue">[1]</font>>];
    v2[xlabel=<<font color="blue">[1]</font>>];
    
    v3[xlabel=<<font color="blue">[2]</font>>];
    v4[xlabel=<<font color="blue">[2]</font>>];

    T[xlabel=<<font color="blue">[3]</font>>];

}
```

**4.DFS找增广路**

找到一条增广路,在这条增广路上的最小容量为$8$

```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="12",color="limegreen",penwidth=3];
    v1->v3[label="8",color="limegreen",penwidth=3];
    v3->T[label="18",color="limegreen",penwidth=3];

    v2->v1[label=2];

    v4->v3[label=6];
    v3->v2[headlabel=5,labelangle=-5,labeldistance=8];

    S->v2[label=10];
    v2->v4[label=13];
    v4->T[label=4];


    edge[style=dashed,labeldistance=5]
    v1->S[headlabel=0,labelangle=-10];
    v3->v1[headlabel=0,labelangle=-10];
    T->v3[headlabel=0,labelangle=-10];

    v1->v2[headlabel=0,labelangle=-10];

    v3->v4[headlabel=0,labelangle=-10];
    v2->v3[headlabel=0,labelangle=-5,labeldistance=8];

    v2->S[headlabel=0,labelangle=-10];
    v4->v2[headlabel=0,labelangle=-10];
    T->v4[headlabel=0,labelangle=-10];
    
    
    
    S[xlabel=<<font color="blue">[0]</font>>];
    v1[xlabel=<<font color="blue">[1]</font>>];
    v2[xlabel=<<font color="blue">[1]</font>>];
    
    v3[xlabel=<<font color="blue">[2]</font>>];
    v4[xlabel=<<font color="blue">[2]</font>>];

    T[xlabel=<<font color="blue">[3]</font>>];

}
```

回溯:**对应边增加流量,当前边减少流量**

```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="4"];
    v1->v3[label="0",color="grey80",penwidth=0.5];
    v3->T[label="10"];

    v2->v1[label=2];

    v4->v3[label=6];
    v3->v2[headlabel=5,labelangle=-5,labeldistance=8];

    S->v2[label=10];
    v2->v4[label=13];
    v4->T[label=4];


    edge[style=dashed,labeldistance=5]
    v1->S[headlabel=8,labelangle=-10,color="orange",penwidth=2];
    v3->v1[headlabel=8,labelangle=-10,color="orange",penwidth=2];
    T->v3[headlabel=8,labelangle=-10,color="orange",penwidth=2];

    v1->v2[headlabel=0,labelangle=-10];

    v3->v4[headlabel=0,labelangle=-10];
    v2->v3[headlabel=0,labelangle=-5,labeldistance=8];

    v2->S[headlabel=0,labelangle=-10];
    v4->v2[headlabel=0,labelangle=-10];
    T->v4[headlabel=0,labelangle=-10];
    
    
    
    S[xlabel=<<font color="blue">[0]</font>>];
    v1[xlabel=<<font color="blue">[1]</font>>];
    v2[xlabel=<<font color="blue">[1]</font>>];
    
    v3[xlabel=<<font color="blue">[2]</font>>];
    v4[xlabel=<<font color="blue">[2]</font>>];

    T[xlabel=<<font color="blue">[3]</font>>];

}
```

 - $v1 \to v3$ 这条边的流量为$0$,也就是不通了
 - 回溯到每个点的时候都会尝试继续往下走,但是要符合$dep[v] = dep[u]+1$,且流量 $\neq 0$ 这两个条件
 - 回溯到点$S$的时候,这趟$DFS$还没有结束,因为还可以走$S \to v2 \to v4 \to T$ 这条路径

**这趟发DFS结束后得到:**

```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="4"];
    v1->v3[label="0",color="grey80",penwidth=0.5];
    v3->T[label="10"];

    v2->v1[label=2];

    v4->v3[label=6];
    v3->v2[headlabel=5,labelangle=-5,labeldistance=8];

    S->v2[label=6];
    v2->v4[label=9];
    v4->T[label="0",color="grey80",penwidth=0.5];


    edge[style=dashed,labeldistance=5]
    v1->S[headlabel=8,labelangle=-10,];
    v3->v1[headlabel=8,labelangle=-10,];
    T->v3[headlabel=8,labelangle=-10,];

    v1->v2[headlabel=0,labelangle=-10];

    v3->v4[headlabel=0,labelangle=-10];
    v2->v3[headlabel=0,labelangle=-5,labeldistance=8];

    v2->S[headlabel=4,labelangle=-10];
    v4->v2[headlabel=4,labelangle=-10];
    T->v4[headlabel=4,labelangle=-10];
    
    
    
    S[xlabel=<<font color="blue">[0]</font>>];
    v1[xlabel=<<font color="blue">[1]</font>>];
    v2[xlabel=<<font color="blue">[1]</font>>];
    
    v3[xlabel=<<font color="blue">[2]</font>>];
    v4[xlabel=<<font color="blue">[2]</font>>];

    T[xlabel=<<font color="blue">[3]</font>>];

}
```

**5.重新BFS进行分层**


```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="4"];
    v1->v3[label="0",color="grey80",penwidth=0.5];
    v3->T[label="10"];

    v2->v1[label=2];

    v4->v3[label=6];
    v3->v2[headlabel=5,labelangle=-5,labeldistance=8];

    S->v2[label=6];
    v2->v4[label=9];
    v4->T[label="0",color="grey80",penwidth=0.5];


    edge[style=dashed,labeldistance=5]
    v1->S[headlabel=8,labelangle=-10,];
    v3->v1[headlabel=8,labelangle=-10,];
    T->v3[headlabel=8,labelangle=-10,];

    v1->v2[headlabel=0,labelangle=-10];

    v3->v4[headlabel=0,labelangle=-10];
    v2->v3[headlabel=0,labelangle=-5,labeldistance=8];

    v2->S[headlabel=4,labelangle=-10];
    v4->v2[headlabel=4,labelangle=-10];
    T->v4[headlabel=4,labelangle=-10];
    
    
    
    S[xlabel=<<font color="blue">[0]</font>>];
    v1[xlabel=<<font color="blue">[1]</font>>];
    v2[xlabel=<<font color="blue">[1]</font>>];
    
    v3[xlabel=<<font color="blue">[2]</font>>];
    v4[xlabel=<<font color="blue">[2]</font>>];

    T[xlabel=<<font color="blue">[3]</font>>];

}
```

进行DFS


```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="4"];
    v1->v3[label="0",color="grey80",penwidth=0.5];
    v3->T[label="10",color="limegreen",penwidth=2];

    v2->v1[label=2];

    v4->v3[label=6,color="limegreen",penwidth=2];
    v3->v2[headlabel=5,labelangle=-5,labeldistance=8];

    S->v2[label=6,color="limegreen",penwidth=2];
    v2->v4[label=9,color="limegreen",penwidth=2];
    v4->T[label="0",color="grey80",penwidth=0.5];


    edge[style=dashed,labeldistance=5]
    v1->S[headlabel=8,labelangle=-10,];
    v3->v1[headlabel=8,labelangle=-10,];
    T->v3[headlabel=8,labelangle=-10,];

    v1->v2[headlabel=0,labelangle=-10];

    v3->v4[headlabel=0,labelangle=-10];
    v2->v3[headlabel=0,labelangle=-5,labeldistance=8];

    v2->S[headlabel=4,labelangle=-10];
    v4->v2[headlabel=4,labelangle=-10];
    T->v4[headlabel=4,labelangle=-10];
    
    
    
    S[xlabel=<<font color="blue">[0]</font>>];
    v1[xlabel=<<font color="blue">[1]</font>>];
    v2[xlabel=<<font color="blue">[1]</font>>];
    
    v3[xlabel=<<font color="blue">[2]</font>>];
    v4[xlabel=<<font color="blue">[2]</font>>];

    T[xlabel=<<font color="blue">[3]</font>>];

}
```

回溯后得到


```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="4"];
    v1->v3[label="0",color="grey80",penwidth=0.5];
    v3->T[label="4"];

    v2->v1[label=2];

    v4->v3[label=0,color="grey80",penwidth=0.5];
    v3->v2[headlabel=5,labelangle=-5,labeldistance=8];

    S->v2[label=0,color="grey80",penwidth=0.5];
    v2->v4[label=3];
    v4->T[label="0",color="grey80",penwidth=0.5];


    edge[style=dashed,labeldistance=5]
    v1->S[headlabel=8,labelangle=-10,];
    v3->v1[headlabel=8,labelangle=-10,];
    T->v3[headlabel=14,labelangle=-10,];

    v1->v2[headlabel=0,labelangle=-10];

    v3->v4[headlabel=6,labelangle=-10];
    v2->v3[headlabel=0,labelangle=-5,labeldistance=8];

    v2->S[headlabel=10,labelangle=-10];
    v4->v2[headlabel=10,labelangle=-10];
    T->v4[headlabel=4,labelangle=-10];
    
    
    
    S[xlabel=<<font color="blue">[0]</font>>];
    v1[xlabel=<<font color="blue">[1]</font>>];
    v2[xlabel=<<font color="blue">[1]</font>>];
    
    v3[xlabel=<<font color="blue">[2]</font>>];
    v4[xlabel=<<font color="blue">[2]</font>>];

    T[xlabel=<<font color="blue">[3]</font>>];

}
```

**最终得到的最大网络流为:**
```viz-neato
digraph G {
    node[shape=circle];
    S[pos="-1,1!"];
    v1[pos="1,2!"];
    v2[pos="1,0!"];
    v3[pos="3,2!"];
    v4[pos="3,0!"];
    T[pos="5,1!"];


    edge[arrowhead=open]
    S->v1[label="8"];
    v1->v3[label="8"];
    v3->T[label="14"];

    v2->v1[label=0];

    v4->v3[label=6];
    v3->v2[headlabel=0,labelangle=-5,labeldistance=8];

    S->v2[label=10];
    v2->v4[label=10];
    v4->T[label="4"];

}
```

## 练习

找一张纸,使用下面的图,用笔模拟一遍$Dinic$算法.

```viz-neato
digraph G {
    node[shape=circle];
    1[label=S];
    7[label=T];

    1[pos="0,1!"];
    2[pos="1,2!"];
    3[pos="3,2!"];
    4[pos="1,0!"];
    5[pos="3,0!"];
    6[pos="2,1!"];
    7[pos="4,1!"];

    1->2[label="4"];
    2->3[label="7"];
    3->7[label="9"];
    1->4[label="10"];
    4->5[label="3"];
    5->7[label="6"];
    2->6[label="2"];
    6->5[label="1"];
    4->6[label="5"];
    6->3[label="6"];
    2->4[label="1"];
    5->3[label="5"];

}
```

## 分层的代码

## 如何存储残余网络



当一条边流量增加的时候(数字减少),它对应的边就应该减少流量(数字增加)

## Dinic算法复杂度分析

与最短增广路算法一样，Dinic算法最多被分为n个阶段，每个阶段包括建层次网络和寻找增广路两部分，其中建立层次网络的复杂度仍是O（n*m)。

现在来分析DFS过程的总复杂度。在每一阶段，将DFS分成两部分分析。

（1）修改增广路的流量并后退的花费。在每一阶段，最多增广m次，每次修改流量的费用为O（n）。而一次增广后在增广路中后退的费用也为O(n)。所以在每一阶段中，修改增广路以及后退的复杂度为O(m*n)。

（2）DFS遍历时的前进与后退。在DFS遍历时，如果当前路径的最后一个顶点能够继续扩展，则一定是沿着第i层的顶点指向第i+1层顶点的边向汇点前进了一步。因为增广路经长度最长为n，所以最坏的情况下前进n步就会遇到汇点。在前进的过程中，可能会遇到没有边能够沿着继续前进的情况，这时将路径中的最后一个点在层次图中删除。

注意到每后退一次必定会删除一个顶点，所以后退的次数最多为n次。在每一阶段中，后退的复杂度为O（n）。

假设在最坏的情况下，所有的点最后均被退了回来，一共共后退了n次，这也就意味着，有n次的前进被“无情”地退了回来，这n次前进操作都没有起到“寻找增广路”的作用。除去这n次前进和n次后退，其余的前进都对最后找到增广路做了贡献。增广路最多找到m次。每次最多前进n个点。所以所有前进操作最多为n+m*n次，复杂度为O（n*m）。

于是得到，在每一阶段中，DFS遍历时前进与后退的花费为O（m*n）。

综合以上两点，一次DFS的复杂度为O（n*m）。因此，Dinic算法的总复杂度即O（m*n*n）。

## 朴素Dinic

题目地址：[luogu P3376 【模板】网络最大流](https://www.luogu.org/problemnew/show/P3376)

**代码:**

```c
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

#define maxn 10005
#define maxe 200005

int n,m,s,t;
int dep[maxn]; //分层,点i的层数


//向量星
struct _e {
    int u,v,next,cap;
};
_e e[maxe];
int head[maxn];
int cnt = 0;

//边的编号从0开始
void addEdge(int u,int v,int cap){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].cap = cap;
    e[cnt].next = head[u];
    head[u] = cnt++;
}


//返回值表示是否能达到t点
bool bfs(){ //给各个点分层
    memset(dep,-1,sizeof(dep)); //初始化
    queue<int> q;
    dep[s] = 1; //起点的 层
    q.push(s);
    
    while(q.empty() == false){
        int now = q.front(); q.pop();
        int i;
        for(i=head[now];i!=-1;i=e[i].next){
            int v = e[i].v;
            //v没有访问过 且 容量可通行
            if(dep[v] == -1 && e[i].cap >0){ 
                dep[v] = dep[now] +1;
                q.push(v);
            }
        }
    }

    return dep[t] != -1; // !=-1 表示能分层到汇点
}

// u 当前点,low u前面的路径上的最小容量
int dfs(int u,int low){
    if( u == t) return low;
    int i;
    for(i=head[u]; i !=-1;i=e[i].next){
        int v = e[i].v;
        // 是下一层的点 且 可通行
        if(dep[v] == dep[u]+1 && e[i].cap > 0){
            int flow = dfs(v,min(low,e[i].cap));
            if( flow > 0){ //从v开始可以走到汇点
                e[i].cap -=flow;    //同向容量 缩小
                e[i^1].cap += flow; //反向容量 加大
                return flow;        //回溯
            }

        }
    }
    
    return 0; //从u点到不了汇点
}

int dinic(){
    int tmp  = 0;
    while( bfs()){ //分层
        int f ; 
        while( f  = dfs(s,0x7f7f7f7f)){ //多次dfs,直到找不到路
            tmp +=f;
        }
    }
    return tmp;
}


int main(){
    
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);
    int t1,t2,t3;
    int i,j,k;
    memset(head,-1,sizeof(head));
    for (i=1;i<=m;i++){
        scanf("%d%d%d",&t1,&t2,&t3);
        addEdge(t1,t2,t3); //正向边
        addEdge(t2,t1,0);  //反向边
    }
    int maxflow =dinic();
    printf("%d\n",maxflow);
    return 0;
}
```

## 当前弧优化

每次增广一条路后可以看做“榨干”了这条路，既然榨干了就没有再增广的可能了。但如果每次都扫描这些“枯萎的”边是很浪费时间的。那我们就记录一下“榨取”到那条边了，然后下一次直接从这条边开始增广，就可以节省大量的时间。这就是 当前弧优化 。

具体怎么实现呢，先把链式前向星的head数组复制一份，存进cur数组，然后在cur数组中每次记录“榨取”到哪条边了。

我们知道dinic算法中的dfs是为了在可行增广路中找到最小容量。而找增广路需要遍历每个点所连接的边，直至找到一条可到达终点的路。例如，我们在第一次dfs时找到了一条增广路：顶点1中的第3条边，顶点2中的第4条边，顶点3中的第4条边，顶点5中的第2条边。这四条边是我们在第一次dfs寻找到的可行路，我们可以看到，每次找增广路时都是从某个顶点所连接的第一条边开始，那也就是说从顶点1中的第1条边接着去找没找到，从而遍历到顶点1中的第3条边，接着去找发现顶点2中的前三条边也没找到。。。这样下去直到找到终点。那么，我们可以知道下次dfs时，顶点1的前两条边没用（下次bfs或者几次bfs后可能会有用），直接从顶点1的第三条边开始去找。

当我们将当前图的所有增广路都找到后，再次bfs分层，当前图的层次会发生变化，然后我们在从顶点1开始去找，所以我们每次bfs，都要清一下数组cur。


修改代码风格 todo
```c
bool bfs(){ //给各个点分层
    //拷贝head
    int i;
    for(i=1;i<=n;i++) cur[i] = head[i];

    ....
}

// u 当前点,low u前面的路径上的最小容量
int dfs(int u,int low){
    if( u == t ) return low;
    int i;
    for(i=cur[u]; i !=-1;i=e[i].next){
        cur[u] = i;

        ...

    }
    
    return 0; //从u点到不了汇点
}

int dinic(){
    int tmp = 0,f;
    while( bfs()){ //分层
        while( f  = dfs(s,0x7f7f7f7f)){ //多次dfs,直到找不到路
            tmp +=f;
        }
    }
    return tmp;
}
```

题目地址：[luogu P3376 【模板】网络最大流](https://www.luogu.org/problemnew/show/P3376)

**代码:**

```c
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

#define maxn 10005
#define maxe 200005

int n,m,s,t;
int dep[maxn]; //分层,点i的层数


//向量星
struct _e {
    int u,v,next,cap;
};
_e e[maxe];
int head[maxn];
int cur[maxn]; //存当前边
int cnt = 0;

//边的编号从0开始
void addEdge(int u,int v,int cap){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].cap = cap;
    e[cnt].next = head[u];
    head[u] = cnt++;
}


//返回值表示是否能达到t点
bool bfs(){ //给各个点分层
    //拷贝head
    int i;
    for(i=1;i<=n;i++) cur[i] = head[i];

    memset(dep,-1,sizeof(dep)); //初始化
    queue<int> q;
    dep[s] = 1; //起点的 层
    q.push(s);
    
    while(q.empty() == false){
        int now = q.front(); q.pop();
        int i;
        for(i=head[now];i!=-1;i=e[i].next){
            int v = e[i].v;
            //v没有访问过 且 容量可通行
            if(dep[v] == -1 && e[i].cap >0){ 
                dep[v] = dep[now] +1;
                q.push(v);
            }
        }
    }

    return dep[t] != -1; // !=-1 表示能分层到汇点
}

// u 当前点,low u前面的路径上的最小容量
int dfs(int u,int low){
    if( u == t ) return low;
    int i;
    for(i=cur[u]; i !=-1;i=e[i].next){
        cur[u] = i;
        int v = e[i].v;
        // 是下一层的点 且 可通行
        if(dep[v] == dep[u]+1 && e[i].cap > 0){
            int flow = dfs(v,min(low,e[i].cap));
            if( flow > 0){ //从v开始可以走到汇点
                e[i].cap -=flow;    //同向容量 缩小
                e[i^1].cap += flow; //反向容量 加大
                return flow;        //回溯
            }

        }
    }
    
    return 0; //从u点到不了汇点
}

int dinic(){
    int tmp  = 0;
    while( bfs()){ //分层
        int f ; 
        while( f  = dfs(s,0x7f7f7f7f)){ //多次dfs,直到找不到路
            tmp +=f;
        }
    }
    return tmp;
}


int main(){
    
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);
    int t1,t2,t3;
    int i,j,k;
    memset(head,-1,sizeof(head));
    for (i=1;i<=m;i++){
        scanf("%d%d%d",&t1,&t2,&t3);
        addEdge(t1,t2,t3); //正向边
        addEdge(t2,t1,0);  //反向边
    }
    int maxflow =dinic();
    printf("%d\n",maxflow);
    return 0;
}
```

## 练习题目1 : [USACO 4.2] 草地排水

[题目地址](https://vjudge.net/problem/POJ-1273#author=CCOA)


## 练习题目2: [USACO 2007 Open Gold]  Dining

[题目地址](https://vjudge.net/problem/POJ-3281#author=Darnt)


POJ3281  拆点

## 引用/资料

 - [Dinic算法详解及实现](https://www.cnblogs.com/LUO77/p/6115057.html)
 - https://www.cnblogs.com/LUO77/p/6115057.html
 - http://cnblogs.com/SYCstudio/p/7260613.html
 - https://blog.csdn.net/u012914220/article/details/23865829
