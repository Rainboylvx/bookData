---
title: "深度优先搜索"
date: 2019-12-10 16:12
update: 2019-12-10 16:12
author: Rainboy
---

# 深度优先搜索


> 深度优先搜索算法（英语：Depth-First-Search，DFS）是一种用于遍历或搜索树或图的算法。沿着树的深度遍历树的节点，尽可能深的搜索树的分支。当节点v的所在边都己被探寻过，搜索将回溯到发现节点v的那条边的起始节点。这一过程一直进行到已发现从源节点可达的所有节点为止。如果还存在未被发现的节点，则选择其中一个作为源节点并重复以上过程，整个进程反复进行直到所有节点都被访问为止。属于盲目搜索。
> 来自[wiki百科](https://zh.wikipedia.org/wiki/%E6%B7%B1%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2)



![](./dfsbfs.gif)

> [图片来源](https://eugene-eeo.github.io/blog/tree-traversal-storage.html)

**算法演示**

 - [DFS动画演示1](https://www.cs.usfca.edu/~galles/visualization/DFS.html)
 - [DFS动画演示2](https://visualgo.net/en/dfsbfs)

## 学习路径


```viz-dot
digraph g {
    node[shape=rect]
    "前置知识:递归"-> "DFS"->2;
    2[label="基本的dfs题目"]

    {
        rank=same;
        2
        "迷宫问题"
        "八皇后"
    }

    2->{3,4,5,6};
    3[label="剪枝"]
    4[label="迭代加深"]
    5[label="记忆化"]
    6[label="种子填充"]
}
```



## DFS重要的知识点

 - **边界条件**
 - 搜索的状态表示(dfs的参数)
    - **状态:** 能唯一表明事物所处的一种形态
 - 搜索的状态转移(如果从一种状态过渡到另一种的状态的)


## 回溯大法

**如果不行,就返上一步重新尝试**

## 核心思想


<easy-memory-board size="2">
    <p slot="title">口决</p>
    <li>一直往"深"走</li>
    <li>撞了南墙就回头</li>
</easy-memory-board>

## DFS框架


// 状态小的时候,
可以用参数来表示状态
<!-- template start -->
```c
void dfs( state arguments){

    if(到达边界条件)
        结束函数
    
    for(i=0;i<=max;i++){
        
        state_next = opt
        //

        dfs(state_next)
                        
    }
}
```
<!-- template end -->

// 状态大的时候,
用全局变量来表示状态,每次操作都修改这个全局变量,但是在回溯的时候又把这个全局变量重置回来.

```c
 state arguments
void dfs(){
    
    if(到达边界条件)
        结束函数

    for(i=0;i<=max;i++){
        
        state_next = opt
        //
        dfs()
        unset state_next
                        
    }
}
```


## 练习题目


###   迷宫类问题 
题目所在的OJ: 1.信息学奥赛一本通 2.SlimeOJ

  - 1252 走迷宫
  - 1254 走出迷宫
  - 1255 迷宫问题
  - 1256 献给阿尔吉侬的花束
  - 1257 Knight Moves
  - 1215 迷宫
