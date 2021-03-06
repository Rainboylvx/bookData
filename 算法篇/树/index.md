---
_id: "f36085da97"
title: "树"
date: 2020-11-08 15:34
update: 2020-11-08 15:34
author: Rainboy
---

@[toc]

## 定义

**树状图**是一种数据结构，它是由`n（n>=1）`个有限节点组成一个具有层次关系的集合。把它叫做“树”是因为它看起来像一棵倒挂的树，也就是说它是根朝上，而叶朝下的。它具有以下的特点：

每个节点有零个或多个子节点；没有父节点的节点称为根节点；每一个非根节点有且只有一个父节点；除了根节点外，每个子节点可以分为多个不相交的子树；


![树](/images/树.png)


树（tree）是包含$n(n>0)$个结点的有穷集，其中：

 1. 每个元素称为**结点**（$node$）；
 2. 有一个特定的结点被称为**根结点或树根**（$root$）。
 3. 除根结点之外的其余数据元素被分为$m(m \geqslant 0)$个互不相交的集合$T_1,T_2,\cdots,T_{m-1}$，其中每一个集合$T_i(1<=i<=m)$本身也是一棵树，被称作原树的**子树(subtree)**。



树也可以这样定义：

**树是由根结点和若干个子树构成的**  

树是由一个**集合**以及在该集合上定义的一种**关系**构成的。集合中的元素称为树的结点，所定义的关系称为**父子关系**。父子关系在树的结点之间建立了一个**层次结构**。在这种层次结构中有一个结点具有特殊的地位，这个结点称为该树的根结点，或称为树根 

我们可以形式地给出树的递归定义如下:

1. 单个结点是一棵树，树根就是该结点本身。
2. 空集合也是树，称为空树。空树中没有结点。
3. 树的孩子包含孩子的所有子树也是一棵树。



## 树的性质

 1. $n$个点的树，有$n-1$条边
 2. 树上的任意两个点连通，且只有一条路径
 3. 树上不存在环

::: blackboard
满足上面任意两个条件的图，都是一棵树。
:::


这是一条很重要的结论，我们在做题目的时候，常常要用它来判断图是否是树。


## 树的相关术语

 - **节点的度**:一个节点含有的子树的个数称为该节点的度；
 - **叶节点或终端节点**:度为0的节点称为叶节点；
 - **非终端节点或分支节点**:度不为0的节点；
 - **双亲节点或父节点**:若一个节点含有子节点，则这个节点称为其子节点的父节点；
 - **孩子节点或子节点**:一个节点含有的子树的根节点称为该节点的子节点；
 - **兄弟节点**:具有相同父节点的节点互称为兄弟节点；
 - **树的度**:一棵树中，最大的节点的度称为树的度；
 - **节点的层次**:从根开始定义起，根为第1层，根的子节点为第2层，以此类推；
 - **树的高度或深度**:树中节点的最大层次；
 - **堂兄弟节点**:双亲在同一层的节点互为堂兄弟；
 - **节点的祖先**:从根到该节点所经分支上的所有节点；
 - **子孙**:以某节点为根的子树中任一节点都称为该节点的子孙。
 - **森林**:由$m(m \geqslant 0)$棵互不相交的树的集合称为森林；

