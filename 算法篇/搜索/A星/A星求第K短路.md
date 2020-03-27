---
title: A星求第K短路
date: 2019-10-01 09:16
update: 2019-10-01 09:16
author: Rainboy
---

@[toc]

## 原理解析

核心:去掉$close_list$.

**想一想**如果没有期望函数$F$,$Dijkstra$也可以求第$K$短路.当一个点$u$第$k$次从堆中取出时.表示起点$s$到达$u$的第$k$条最短路的值.

但是$Dijkstra$是一种盲目的查找,有许多不必要的状态.

```viz-dot
graph g {
    node[shape=circle fixedsize=true style=filled fillcolor=white colorscheme=accent8 ];
    rankdir=LR;
    1--2[label="1"];
    1--3[label="2"];
    1--4[label="3"];
    2--5[label="6"];
    3--5[label="5"];
    4--5[label="1"];
}
```


2和3是无用的点,如果不取2,3,直接取4,就可以加快运算.
```viz-dot
graph g{
    node[shape=plaintext fixedsize=true  fillcolor=white colorscheme=accent8 ];
    a[
        label=< <TABLE CELLBORDER="1" BORDER="0" CELLSPACING="0" CELLPADDING="10">
            <tr>
                <td PORT="">出栈</td>
                <td PORT="">1</td>
                <td PORT="" BGCOLOR="6">2</td>
                <td PORT="" BGCOLOR="6">3</td>
                <td PORT="">4</td>
                <td PORT="">5</td>
                <td PORT="">5</td>
            </tr>
            <tr CELLBORDER="0">
                <td PORT="" CELLBORDER="0">距离</td>
                <td PORT="" CELLBORDER="0">0</td>
                <td PORT="" CELLBORDER="0">1</td>
                <td PORT="" CELLBORDER="0">2</td>
                <td PORT="" CELLBORDER="0">3</td>
                <td PORT="" CELLBORDER="0">4</td>
                <td PORT="" CELLBORDER="0">5</td>
            </tr>
        </TABLE> >
    ]
}
```

我们使用期望函数$F=g+h$,其中$g$表示起点到点$u$的第$k$条最短路的值,$h$表示点$u$到达终点$t$最短路的值.每一次从堆中取出$F$值最小的点向周围拓展,直到终点$t$第$k$次从堆中取出,结束.

优点是:每一次都是向目标$t$前进,不会搜索许多不必要的状态.


## 代码模板

<!-- template start -->
```c
<%- include("astar_Kshort_path_template.cpp") %>
```
<!-- template end -->

## 样例题目


题目地址:[「POJ - 2449」 Remmarguts' Date  ](https://vjudge.net/problem/poj-2449#author=wawa_wawa)

::: warning
**坑点**:如何起点和终点相同,从起点出发时不算第一次到达!,所以`if(s == t) k++;`
:::

### 代码

```c
<%- include("poj2449.cpp") %>
```

### 代码:C++11 风格

::: warning
POJ 不支持C++11 所以下面的代码没有验证!
:::

::: fold
```c
<%- include("poj2449_c++11.cpp") %>
```
:::

## 题目列表

 - [POJ2449](https://vjudge.net/problem/POJ-2449)
 - [2018 ACM-ICPC沈阳网络赛——D——Made in Heaven]

