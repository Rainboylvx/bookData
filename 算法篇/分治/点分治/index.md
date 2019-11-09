---
_id: db34c21177
title: "「入门」点分治"
date: 2019-11-08 14:58
update: 2019-11-08 14:58
author: Rainboy
---


@[toc]

## 知识网络

```viz-dot
<%- include("dot/know-net.dot") %>
```


## 定义

**点分治主要用于树上路径点权统计问题**

## 题目引入

题目地址:[POJ-1741 Tree ](https://vjudge.net/problem/poj-1741)

题目大意: 输入树的各边及其长度，求路径小于等于k的点对数目

## 思考解析

### 分治思想

核心思路:**分治思想**

满足条件的路径可以分为两种,$1$:**经过根结点**,$2$:**不经过根结点**.如果我们能求出情况$1$,那么剩下的都是情况$2$,也就是在根结点的子树上.所以整体上我们可以用分治(递归)算法.

::: line

```viz-dot
<%- include("dot/t1.dot") %>
```
```viz-dot
<%- include("dot/t2.dot") %>
```
:::

### 求出经过根的答案

我们可以用$DFS$在$O(n)$的时间内,算出每个点到$root$的距离(深度)$dis[i]$,**现在的问题是有多少对dis[i]的值加起来不超过$k$?**

阅读本书:[序列中不超过K的对数](/article/911fd7a889)的内容,发现排序($O(nlogn)$)后,可以在$O(n)$的时间内得到答案

### 剔除多余的计算

仔细思考,发现上面的计算会多算一些不是答案的路径:

::: line
```viz-dot
<%- include("dot/t3.dot") %>
```
```viz-dot
<%- include("dot/t4.dot") %>
```
:::

如上图1:$1 \rightarrow 2 \rightarrow 4 + 1 \rightarrow 2 \rightarrow 5$,++重复走了$1 \rightarrow 2$++

如上图2:$1 \rightarrow 2 + 1 \rightarrow 2 \rightarrow 4$,++重复走了$1 \rightarrow 2$++

剔除所有走了两次$1 \rightarrow 2$ 的不合法路径,


如何解决这个问题?

只有求出,以$2$为根的子树的内路径加起来$ \leq  2*len(1,2)$ 数量,可以和[求出经过根的答案](#剔除多余的计算)用同一种方法来计算

### 时间复杂度分析

我们分别用了**深搜**,**排序**,**递归**来完成算法,**排序**的时间复杂度为$O(nlogn)$,假如说输入的数据退化成了一个链，那么每次的子树大小就为$n−1$，想一想发现，时间复杂度到了$O(n^2\log n)$！这样是不行的！

```viz-dot
<%- include("dot/link-tree.dot") %>
```

如何才能缩小时间复杂度?

参考本书的[树的重心](/article/115260c5a0)这一节,
发现**树之重心**的子树大小不会超过$\frac {n} {2}$ 
。假如说我们每次选取点的时候，都使用树的重心，那么套回点分治的时间复杂度，在最坏情况下（链），子树大小为$\frac {n} {2}$ ，使用主方法将递推式转为通项公式，可以得到解法的时间复杂度:$O(n\log^2 n)$

## 代码

```c
<%- include("code/poj1741.cpp") %>
```

## 练习题目

- http://hzwer.com/category/algorithm/graph-theory/tree/some-divide-and-conquer
- https://blog.csdn.net/qq_35649707/article/category/6928731



https://blog.csdn.net/qq_39553725/article/details/77542223

题目:

POJ 1741 & BZOJ 1468 & BZOJ 3365


- luogu P3806 【模板】点分治1

## 参考

 - [B站 【AgOHの算法胡扯】点分治](https://www.bilibili.com/video/av69607337)
 - [POJ 1741 点分治](https://blog.sshockwave.net/poj-1741-point-division/)
 - [漆子超《分治算法在树的路径问题中的应用》](https://wenku.baidu.com/view/e087065f804d2b160b4ec0b5.html)
