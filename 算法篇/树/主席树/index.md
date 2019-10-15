---
title: "主席树:入门" 
date: 2019-10-14 13:09
update: 2019-10-15 15:19
author: Rainboy
password: "zxs42"
---

@[toc]

## 知识网络

```viz-dot
digraph net {
    线段树->权值线段树->"主席树"
}
```

## 介绍

 - 需要的前置知识:线段树,
 - 全名:函数式版本的线段树,可持久化线段树、函数式线段树,可保存历史版本的线段树
 - 是一种离线结构
 - 一般解决问题:区间第k大

**为什么叫主席树呢?**

 > 我感觉这种求k大的方法应该是我最早开始用的,至于别人喜欢怎么称呼函数式线段树这我管不着对吧..

以上出自[知乎](https://www.zhihu.com/question/31133885)--[黄嘉泰](https://www.zhihu.com/people/fotile96/activities)

你会发现他的名字的缩写是HJT,对应了一个人...



## 注意

每个结点需要存下:

 - 指向左右孩子的指针

```c
struct Node {
    int l,r; //左右孩子的指针
    int sum; //其他信息
};
```

维护的信息:

前i个树的权值线段树

如何求区间[i,j]内的第k大说?

 - tree[i]表示

tree[j],tree[i-1]相应的结点相减,代表在序列[i,j]在对应值区间内数的个数,这样就可以用线段树的性质,来

这样就可以用线段树的性质来判断要查找的第K大的数是在当前节点的左孩子,还是在当前节点的右孩子所代表的区间内,来判断每一次向左和还是向右查找,直到叶节点就是需要查找的数字.

## 从一个题目讲起

题目地址:[luogu P3834 【模板】可持久化线段树 1（主席树）](https://www.luogu.org/problem/P3834)


```viz-neato
<%- include("dot/base.dot") %>
```

```viz-dot
<%- include("dot/2.dot") %>
```



<<<< viz-gallery(title="动画演示",engine="neato",height="400")

<% 
var log =["针对下面的序列交流主席树"]
var engine = ""
for(let i=0;i<=5;i++){
    var page = `dot/animation_${i}.dot`
%>

``` <%= engine || ""%> <%= log[i] || `建立第${i}颗树` %>
<%- include(page) %>
```
<%}%>

<<<<



## 解析

先离散化,然后分别针对[1,i]建立权值线段树为root[i],那一共要建立n颗树.每颗树维护的信息为:前i个数中,在值域[1,n]内出现的次数.


## 代码

```c
<%- include("code/luogu3834.cpp") %>
```

## 参考

 - [视频-UESTCACM 每周算法讲堂 主席树](https://www.bilibili.com/video/av4619406/?from=search&seid=15426933771046703959)
 - [视频-【算法讲堂】【电子科技大学】【ACM】权值线段树与主席树](https://www.bilibili.com/video/av16552942/?from=search&seid=15426933771046703959)
 - [主席树（可持久化线段树）入门专题](https://blog.csdn.net/htt_h/article/details/47704209)
 - [可持续化线段树（主席树）](https://www.cnblogs.com/shenben/p/5598371.html)

## 练习题目

 - poj-2104 查询区间第k小
 - hdu 4417 区间查询<=H的数有多少个
 - hdu 4348 可持久化线段树，区间更新，不下放的懒惰标记（空间优化）

