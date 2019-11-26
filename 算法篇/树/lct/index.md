---
_id: adf08a95d9
title: "「LCT入门」序"
date: 2019-11-20 17:47
update: 2019-11-20 17:47
author: Rainboy
---

@[toc]

## 前置知识

```viz-dot
digraph title {
    node[shape=plaintext fixedsize=true  fillcolor=white colorscheme=accent8 ];
    { "Splay", "树链剖分" }->"link cut tree"
}
```

## 题目引入

[P3690 【模板】Link Cut Tree （动态树）](https://www.luogu.org/problem/P3690)

**题目理解**:

 - 不停的连接两个点,会形成多棵树组成的森林或者一棵树
 - 操作$0$其实是询问树上的两个点之间的

## 基础

性质:

1. 对于某一个结点U,它只存在于一个Splay中
2. 每个Splay中的结点的深度按中序遍历的顺序递增


基础代码:

```c

```

## 操作

### 最最基本的操作:Access(x)

Access(x)原树上的根到root拉拉一条实链

1. 伸展$x$到根
2. 把x的右儿子修改为上一个x,如果是第一次就是0(虚实转换)
3. 对x的父亲重复以上步骤

**代码**

```c
```

### MakeRoot(x)

$MakeRoot(x)$作用:给原树换根为x

1. $Access(x)$
2. 伸展$x$
3. 翻转整棵Splay(把深度翻转)

**代码**

```c
```

### FindRoot(x)

FindRoot(x)作用:找x结点在原树的根结点是哪位

1. Access(x)
2. Splaying(x)
3. 找到x所在的Splay的最左点的那个点u,它就是原树的根结点
4. 为了防止数据卡链保证时间复杂度,还需要再Splay(u)

**代码**

```c
```

### Link(x,y)

作用:$x,y$两个点直接连边

1. MakeRoot(x)
2. 如果FindRoot(y)是x,那说明x和y在同一个树上,数据不合法就不要连边,不然可能出现环
3. 把x的父亲置为y连一条虚边

**代码**

```c
```

### Cut(x,y)

作用:断掉x和y之间的边

1. MakeRoot(x)
2. 判断数据合法性:如果FindRoot(y)不是x或者x和y不是相邻的(y的父亲不是x,或者y有左孩子)
3. 双向断边: x的右儿子和y的父亲置为NULL
4. 更新信息(异或和,大小等)

**代码**

```c
```

### split(x,y)

作用:把x到y的路径拆成一棵方便操作的SPlay出来

1. MakeRoot(x)
2. Access(y)
3. splay(y)


## 题目列表

 - bzoj2049洞穴勘测

## 工具/脚本

 - :arrow_down: [数据生成器](./tools/data_generator.py)


## 引用资料

 - [【AgOHの算法胡扯】Link/Cut Tree](https://www.bilibili.com/video/av65682026)
 - [ LCT总结——概念篇+洛谷P3690 模板 Link Cut Tree(动态树)（LCT，Splay）](https://www.cnblogs.com/flashhu/p/8324551.html)
 - [LCT（Link-Cut Tree）详解（蒟蒻自留地）](https://blog.csdn.net/saramanda/article/details/55253627)
