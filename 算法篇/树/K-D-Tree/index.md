---
title: "序/入门"
date: 2019-12-05 09:33
update: 2019-12-05 09:33
author: Rainboy
---

## 基础

如何构建:

1.  选择的维度要满足其内部点的分布的差异度最大，即每次选择的切割维度是方差最大的维度。
2.  每次在维度上选择切割点时选择该维度上的 **中位数** ，这样可以保证每次分成的左右子树大小尽量相等。

我们来回顾一下快速排序的思想。每次我们选出一个数，将小于该数的置于该数的左边，大于该数的置于该数的右边，保证该数在排好序后正确的位置上，然后递归排序左侧和右侧的值。这样的期望复杂度是 $O(n\log n)$ 的。但是由于 k-D Tree 只要求要中位数在排序后正确的位置上，所以我们只需要递归排序包含中位数的 **一侧** 。可以证明，这样的期望复杂度是 $O(n)$ 的。在 `algorithm` 库中，有一个实现相同功能的函数 `nth_element()` ，要找到 `s[l]` 和 `s[r]` 之间的值按照排序规则 `cmp` 排序后在 `s[mid]` 位置上的值，并保证 `s[mid]` 左边的值小于 `s[mid]` ，右边的值大于 `s[mid]` ，只需写 `nth_element(s+l,s+mid,s+r+1,cmp)` 。

## 练习1: luogu p1429 P1429 平面最近点对（加强版）

[P1429 平面最近点对（加强版）](https://www.luogu.com.cn/problem/P1429)

```c
<%- include("code/p1429.cpp") %>
```

## 练习题目

 - P4169 [Violet]天使玩偶/SJY摆棋子
 - P4148 简单题 题解
 - Luogu4475 巧克力王国
 - Luogu2093 JZPFAR
 - Luogu4357 K远点对
 - BZOJ4154 Generating Synergy
 - BZOJ3489 A simple rmq problem
 - BZOJ3616 War

## 参考/引用

- [「OI Wiki」 K-D Tree](https://oi-wiki.org/ds/kdt/)
