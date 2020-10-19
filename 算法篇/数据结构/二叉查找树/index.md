---
title: "二叉查找树/序"
date: 2019-10-19 18:57
update: 2019-10-19 18:57
author: Rainboy
password: bst42
---

@[toc]

## 基础知识

### 定义

一棵空树，或者是具有下列性质的二叉树：

1. 若左子树不空，则左子树上所有结点的值均小于它的根结点的值；
2. 若右子树不空，则右子树上所有结点的值均大于它的根结点的值；
3. 左、右子树也分别为二叉排序树；
4. 没有键值相等的结点。

我们称为这种树为二叉查找树(Binary Search Tree,BST)

```viz-dot
<%- include("dot/demo.dot") %>
```

### 性质

1. 对于BST,它的中序遍历为单调上升的序列
2. 可以在O(log(n))的时间内找到第k的数
3. 快速的**按值找排名**,**按排名找值**

### 结点定义

```c
struct tree_node {
    int val; //值
    int l,r,fa; //左,右孩子,父亲的编号
    int size; //以当前点为根的子树的大小
};
```

## 常用操作

### 插入

 - 若b是空树，则将s所指结点作为根结点插入，否则：
 - 若s等于b的根结点的数值，则返回，否则：
 - 若s小于b的根结点的数值，则把s插入到左子树中，否则：
 - 把s所指结点插入到右子树中。

### 查找

在二叉排序树b中查找x的过程为：

- 若b是空树，则搜索失败，否则：
- 若x等于b的根结点的数值，则查找成功；否则：
- 若x小于b的根结点的数值，则搜索左子树；否则：
- 查找右子树。

```c
// now 当前结点编号 val 要查找的值
// (int *) &point 指针变量的引用,查找到的点,直接前驱的地址
int find(int now,int val, int * &point)
```

这里比较难以理解的就是`int * &fa`,`int *`是一种数据类型,可以认为是一个存放地址值的整数,每一次都会修改最初传递过来变量里的数值.

```viz-dot
digraph g{
    node[shape=record];
    point[xlabel=point,label="address:0x123"]
    1[label="<f0>l|val : 1| r"]
    2[label="l|val : 2| r"]
    point->1:f0[style=dotted];
    1:f0->2;
    1->3[style=invis];
    3[style=invis];
}
```

### 删除

二叉排序树删去一个结点，分三种情况讨论：

1.  若u结点为叶子结点，即u.l(左子树)和u.r(右子树)均为空树。由于删去叶子结点不破坏整棵树的结构，则只需修改其父亲结点的指向

```viz-dot
digraph g{
    node[shape=circle style="filled"]
    1->{2,3};
    2->{4,5};
    3[fillcolor="red"]
    4[fillcolor="red"]
    5[fillcolor="red"]
}
```
2.  若u结点只有左子树u.l或右子树u.r，此时只要令u.l或u.r直接成为其双亲结点f的左子树或右子树即可，作此修改也不破坏二叉排序树的特性。

```viz-dot
digraph g{
    node[shape=circle style="filled"]
        subgraph cluster_1{
            label="只有左子树";
            1->{2,3};
            2->{4};
            2->{6,5}[style="invis"];
            6[style="invis"]
            5[style="invis"]
            2[fillcolor="red"]
        }
        subgraph cluster_2{
            22[fillcolor="red"]
            label="只有右子树";
            11->{22,32};
            22->{44,66}[style="invis"];
            22->{55}[];
            44[style="invis"]
            66[style="invis"]
        }
}
```
3.  若u结点的左子树和右子树均不空。在删去u之后，为保持其它元素之间的相对位置不变，可按中序遍历保持有序进行调整.具体作法如下:

 1. 找到u的左孩子u.l,再找到u.l右子树的最右点v,fv表示v的父亲(前驱)
 2. 如果fv == u,那就表明,u.l == v,表明u.l没有右子树
    - u.val = v.val,u.l = v.l,删除u.l
 2. 如果fv != u,那就表明,u.l != v,表明u.l有右子树
    - fv.r = v.l
    - u.val = v.val
    - 删除v

<<<< viz-gallery(title="情况1:点u的左孩子没有右子树",engine="dot",height="400")

<% 
var log =["要删除6,5没有右子树","6是5的前驱,使6.lchild == 5.lchild","6的值改为5,删除5"]
var engine = "dot"
for(let i=1;i<=3;i++){
    var page = `dot/del_s1_${i}.dot`
%>

``` <%= engine || ""%> <%= log[i-1] || "" %>
<%- include(page) %>
```
<%}%>

<<<<


<<<< viz-gallery(title="情况2:点u的左孩子存在右子树",engine="dot",height="400")

<% 
var log =["需要删除18,17是18的左子树的最右点,15是17的前驱","前驱15,15.rchild = 17.lchild","18.val = 17.val ","删除17"]
var engine = "dot"
for(let i=1;i<=4;i++){
    var page = `dot/del_S2_${i}.dot`
%>

``` <%= engine || ""%> <%= log[i-1] || "" %>
<%- include(page) %>
```
<%}%>

<<<<



### 前驱

一个结点的后继，是大于u.val的最小关键字的结点

#### 1.存在左子树

如果存在左子树,**前驱 = 左子树中的最大值**

```viz-dot
<%- include("dot/前驱_1.dot") %>
```

读取看上图自己证明

#### 2.1 不存在左子树,但有左父亲

在只有左父亲，**前驱 = 左父亲的值**

```viz-dot
<%- include("dot/前驱_2.dot") %>
```

#### 2.2 不存在左子树,但有右父亲

**前驱 = 右父亲的左父亲**（如果右父亲不存在左父亲，就一直往上遍历，直至出现左父亲）。

```viz-dot
<%- include("dot/前驱_3.dot") %>
```

#### 模板代码

::: fold

```c
1
```
:::

### 后继

#### 1. 存在右子树

**后继 = 右子树中的最小值**。条件是：存在右子树

#### 2.1 不存在右子树

在只有右父亲，没有右子树的情况，**后继 = 右父亲的值**。

#### 2.2 不存在右子树和右父亲的情况呢？

那就只剩下左子树和左父亲了，显然，左子树肯定不行，它的所有元素都小于u.val。那就只能在左父亲中找了，毕竟虽然左父亲小于它，但是右父亲也有它本身的左/右父亲和左子树。

左父亲的左父亲，和左子树都不行，都小于左父亲本身，更小于X了。那就只能在左父亲的右父亲上找了，对于它的右父亲来说，他的左子树全都小于他，即包括X的左父亲和X，所以，此时找到的右父亲就是我们的后继。

所以，不存在右子树和右父亲的情况，**后继 = 左父亲的右父亲**（如果左父亲不存在右父亲，就一直往上遍历，直至出现右父亲）。

## 普通BST的不足

形态和插入的顺序有关,如:1,2,3,4,5,6,7,就会退化成一条链,时间复杂度退化成$O(n^2)$


尽可能保持平衡,平衡树

 - AVL
 - R-B tree (红黑树)
 - Splay
 - treap
 - fhq-treap
 - 替罪羊树



## 完整代码

数据
```
8
1 2 3 4 5 6 7 8
```
<!-- template start -->
```c
<%- include("code/full.cpp") %>
```
<!-- template end -->


## 参考

 - [visualgo-bst](https://visualgo.net/zh/bst)
 - [ 自主建立二叉搜索树（一），插入、建立、查询、最大最小关键字、前驱、后继](https://www.cnblogs.com/tz346125264/p/7766643.html)
 - [关于二叉查找树的一些事儿（bst详解，平衡树入门）](https://www.cnblogs.com/ztz11/p/9059534.html)
