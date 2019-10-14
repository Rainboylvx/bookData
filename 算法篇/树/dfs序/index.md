---
title: "DFS序:基础"
date: 2019-10-12 11:29
update: 2019-10-12 11:29
author: Rainboy
---

@[toc]

## 知识网络

```viz-dot
digraph g {
    "RMQ"-> "树上倍增";
    {
    "树状数组",
    "树上差分",
    "线段树",
    "树上倍增"
    } ->DFS序;
}
```

DFS序:就是将树上的点按顺序转为一维数组, 进而可以用我们前面所学的求解区间相关信息的数据结构来维护区间信息.

## 基础讲解

```viz-dot
<%- include("dot/base.dot") %>
```

所谓的$dfs$序,就是按$dfs$的访问的顺序形成的序列.


如上图可以形成,序列$1$:

```viz-dot
digraph g {
    a[shape=plaintext label=< <TABLE BORDER="0" CELLBORDER="1" WIDTH="10" CELLSPACING="0" CELLPADDING="4">
            <tr>
                <td>1</td>
                <td>2</td>
                <td>4</td>
                <td>5</td>
                <td>7</td>
                <td>3</td>
                <td>6</td>
            </tr>
        </TABLE> >]
}
```


如果按$dfs$的访问的次序($dfn$)来算,可以形成序列$2$:

```viz-dot
digraph g {
    a[shape=plaintext label=< <TABLE BORDER="0" CELLBORDER="1" WIDTH="10" CELLSPACING="0" CELLPADDING="4">
            <tr> <td>1</td> <td>2</td> <td>4</td> <td>2</td> <td>5</td> <td>7</td> <td>5</td> <td>2</td> <td>1</td> <td>3</td> <td>6</td> <td>3</td>
<td>1</td> </tr>
        </TABLE> >]
}
```


## 基本性质

### 性质1: 子树连续

针对序列$1$:

```viz-dot
<%- include("dot/1.dot") %>
```

发现规律: 某个点的子树对应的点,在$DFS$序列中刚好是连续的一段区间,子树求和转成**区间求和**

**模板代码**

<!-- template start -->
```c
int start[maxn],end[maxn];
int dep[maxn],fa[maxn];
int dfs_clock = 0;
int dfs(int d,int u,int pre){
    dep[u] = d;
    fa[u] = pre;
    start[u] = ++dfs_clock;
    int i;
    for(i = head[u]; ~i ; i = e[i].next){
        int v= e[i].v;
        if( v != pre){
            dfs(d+1,v,u);
        }
    }
    end[u] = dfs_clock;
}
```
<!-- template end -->

### 性质2: 子结点包含

针对序列$1$:
如果$v$是$u$的子结点,那么: $start[u] \leq start[v]\ \verb'&'\verb'&'\  end[v] \leq end[u]$,可以利用这个性质来判断结点的关系.

**模板代码**

```c
const int maxn = 1e5+5;
int in[maxn],out[maxn];
inline bool isChild(int a,int b)
    if( start[b]<= start[a] && end[a] <= end[b])
        return 1;
    return 0;
}
```

### 性质3: lca包含

```viz-dot
digraph g {
    a[shape=plaintext label=< <TABLE BORDER="0" CELLBORDER="1" WIDTH="10" CELLSPACING="0" CELLPADDING="4">
            <tr> 
            <td SIDES="R">序列:</td><td>1</td> <td>2</td> <td>4</td> <td>2</td> <td>5</td> <td>7</td> <td>5</td> <td>2</td> <td>1</td> <td>3</td> <td>6</td> <td>3</td> <td>1</td> 
            </tr>
            <tr> 
            <td SIDES="R">深度:</td>
            <td>1</td> <td>2</td> <td>3</td> <td>1</td> <td>3</td> <td>4</td> <td>3</td> <td>2</td> <td>1</td> <td>2</td> <td>3</td> <td>2</td> <td>1</td> 
            </tr>
        </TABLE> >]
}
```

针对序列$2$,$lca(4,7)$就是$4$第一次出现的位置和$7$第一次出现的位置之间深度最小值的点,也就是$2$,和$RMQ$联系在一起,求$lca$.

### 生成序列$1,2$

我们完全可以在一个dfs中生成序列1和序列2,代码如下

 - $seq_1,seq_2$,序列$1,2$
   - 序列1的值根据题意来决定
 - $st[u],ed[u]$,点u在序列1的开始位置和终止位置
 - $dep[u],fa[u]$,点u的深度和父亲
 - $first[u]$,点u在seq_2中第一次出现的位置

::: fold
```c
<%- include("cpp/example_generator_seq1_seq2.cpp") %>
```
:::



## 求lca

结合RMQ(具体看`算法篇/暴力算法/RMQ`),我们可以用序列2的性质来求LCA,


```c
```

::: fold

恭喜你发现了**彩蛋** :tada: :tada: :tada:

FAQ:只用序列$1$可以求出lca吗?

树上倍增,求lca.具体查看`树/树上倍增`.
这里我可以用性质2来简化树上倍增求lca的代码

::: 

## 样例题目

## 参考

 - [倍增LCA / DFS序 学习笔记](https://blog.flyinthesky.win/szLCA/)
 - [ SJTU 「PDF」 树的dfs序及其应用](https://acm.sjtu.edu.cn/w/images/3/35/%E6%A0%91%E7%9A%84dfs%E5%BA%8F%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8%EF%BC%88%E9%97%AB%E9%B8%BF%E5%AE%87%EF%BC%89.pdf)
 - [ DFS 序入门--Planet6174](https://www.luogu.org/blog/P6174/dfs-xu-ru-men)
 - [dfs序 Lucid dreaming](https://www.cnblogs.com/kousak/p/9192094.html)
