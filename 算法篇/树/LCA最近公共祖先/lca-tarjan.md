---
_id: "316d79335f"
title: "lca-tarjan 离线法"
date: 2020-11-24 20:01
update: 2020-11-24 20:01
author: Rainboy
video: "https://www.bilibili.com/video/BV1854y167eP/"
titleEmojiTag: ":tv:"
---



@[toc]

## tarjan入门

解决LCA问题的Tarjan算法利用并查集在一次DFS（深度优先遍历）中完成所有询问。它是时间复杂度为$O(n + (2\times Q))$的离线算法

如下面的两个图,蓝色区域是DFS过程中已经访问过的点,红色是正在访问过的点,问此时`lca(7,4)`和`lca(7,12)`是谁?仔细想一想为什么是这样,有什么样的规律?

![1](./tarjan1.png)
![2](./tarjan2.png)

**一个点什么时候被访问过呢?**  当dfs回溯退出这个点的时候


::: blackboard

**结论**：正在访问的点$u$和已经访问过点$v$的$lca(u,v)$就是$v$所在的已经访问过的点组成的子树的父亲(就是子树的根)。
:::


## 如何在DFS的过程中知道已经访问过的点形成的子树的父亲?

当一个点u退出(回溯退出时),它就已经访问了,它和它所有的子树都应该访问完了,那它们的根应该是u的父亲,为了可以快速已经访问过的点的形成的子树的根,我们用**并查集**，具体看下面的代码。

## tarjan算法正确性证明

![1](./lca11.png)

证明1:**dfs的过程正在访问点U,这个时候点V是U的子树,那么V就是已经访问过的点,那么LCA(U,V)=U**


![2](./lca12.png)

证明2:**u是点p1的子树中的点,V是点p1的另一个子树中的点,dfs的过程正在访问点U,这个时候点V是所在的子树点全部被访问过,那么V就是已经访问过的点,那么LCA(U,V)=p1**


**我们发现所有的lca都可以概括成上面的两种情况**


**情况1:如果$u$和$v$不在同一个子树的时候**

我们发现如果设$p = lca(u,v)$,那么$v$,$u$一定$p$的子树上的点.我们规定$DFS$过程中先访问$v$,后访问$u$,那么在访问到$u$,且要回溯退出$u$时

 - 那么$v$所在的子树上的点w一定都被访问完了,**这个子树的根是就所求lca**
 - 你在回溯的过程可以把所有的点$w$值所在的并查集的根应该是$p$
 - 那么$lca(u,v) = find(v)$

::: blackboard
在dfs的过程中,即将回溯退出某个点x的时候,如果存在一个点u,且u是已经访问过的点,那么lca(x,u)就是 u所在的已经访问过的点的集合 形成的子树的父亲
:::


为什么是 **即将回溯退出某个点x的时候** 这个时刻呢?
 > 这个点x的所有子树上的点y都已经访问过了, 那lca(x,y)就是x

如何得知 **u所在的已经访问过的点的集合 形成的子树的父亲**
 > 点y退出返回到上一层点x的时候,f[y] = x

## 代码模板

<!-- template start -->
```c
struct tarjan {
    bool vis[maxn];
    int  ans[maxn];

    void dfs(int u,int f){
        for(int i=e.h[u];~i;i=e[i].next){
            int &v = e[i].v, &w = e[i].w;
            if( v == f) continue;
            dfs(v,u);
            uset.un(v,u);
        }
        vis[u] = 1; //即将退出时设已访问，注意这求lca(6,6)的这种情况
        for(int i=query.h[u];~i;i=query[i].next){
            int &v = query[i].v, &w = query[i].w;
            if(vis[v]) 
                ans[w] = uset.find(v);
        }
    }

    inline void operator()(){
        dfs(1,0); //dfs(root,root);
    }
} tar;
```
<!-- template end -->

## 具体代码

![tarjan](./tarjan_data.png)

数据如下

  - 第一行两个数n,m,表示树有n个点,m个查询
  - 接下来的n-1行表示树的边
  - 接下来的m行表示查询两个点的lca
```
13 5
1 2
1 8
1 9
2 3
2 4
9 10
9 11
3 5
3 6
10 12
5 7
5 13
4 12
7 6
7 13
6 12
12 13
```

```c
<%- include("code/lca_tarjan.cpp") %>
```

