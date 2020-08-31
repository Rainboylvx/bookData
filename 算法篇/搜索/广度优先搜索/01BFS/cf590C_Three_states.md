---
title: cf590C_Three_states
date: 2019-10-03 23:10
update: 2019-10-03 23:10
author: Rainboy
---

@[toc]

## 题目地址

[ 「CodeForces - 590C」 Three States ]( https://vjudge.net/problem/CodeForces-590C#author=0)

## 解析

::: line

```viz-dot
<%- include("cf590C_1.dot") %>
```

```viz-dot
<%- include("cf590C_2.dot") %>
```

```viz-dot
<%- include("cf590C_3.dot") %>
```
:::


**解法如下:**

::: info
以$3$个大陆为起点，求出该大陆到其他点的最小距离是多少， 然后枚举每个点作为$3$个大陆的路径交点。  
注意:如果交点是$[.]$,需要$-2$
:::

## 代码

```c
<%- include("cf590C_Three_states.cpp") %>
```
