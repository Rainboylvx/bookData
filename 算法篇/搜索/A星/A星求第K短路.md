---
title: A星求第K短路
date: 2019-10-01 09:16
update: 2019-10-01 09:16
author: Rainboy
---

@[toc]

## 原理解析

核心:去掉$close_list$


## 代码模板

<!-- template start -->
```c
<%- include("astar_Kshort_path_template.cpp") %>
```
<!-- template end -->

## 样例题目


https://vjudge.net/problem/poj-2449#author=wawa_wawa

**坑点**:如何起点和终点相同,从起点出发时不算第一次到达!,所以`if(s == t) k++;`

### 代码

```c
<%- include("poj2449.cpp") %>
```

### 代码:C++11 风格

::: fold
```c
<%- include("poj2449_c++11.cpp") %>
```
:::

## 题目列表

 - [POJ2449](https://vjudge.net/problem/POJ-2449)
 - [2018 ACM-ICPC沈阳网络赛——D——Made in Heaven](https://vjudge.net/problem/POJ-2449)

