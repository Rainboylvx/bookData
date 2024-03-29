---
title: A星算法
date: 2019-09-23 10:19
update: 2019-09-23 10:19
author: Rainboy
---

@[toc]

# A*算法

> `A*`搜寻算法俗称A星算法。`A*`算法是比较流行的启发式搜索算法之一，被广泛应用于路径优化领域。它的独特之处是检查最短路径中每个可能的节点时引入了全局信息，对当前节点距终点的距离做出估计，并作为评价该节点处于最短路线上的可能性的量度。
> --- 百度百科

A*算法常被用作游戏的寻路算法

想一想,我们玩过的游戏,只要在游戏的地图上点一下(设置终点),游戏人物就自动沿着最短路开始前进了,这是如何实现的呢?

## 知识网络

```viz-dot
digraph g {
    a->b->c->d;
    a[label="BFS"];
    b[label="Dijkstra"];
    c[label="A星"];
    d[label="A星 求 K短路"];
    {
        rank="same";
        c,d;
    }
}
```

## 算法讲解

自行阅读 **[参考1](#参考)**

## 抽象的过程

::: blackboard
- 把起点加入**优先队列q**中
- 如果优先队列不空
  - 取出最优的点u，如果u是终点，结束运行
  - 不是终点，用u更新周围的点
  - 把u设为vis
- 如果优先队列空
:::

性质：队列中的最优点是实际中的最优。

::: fold
- 把起点添加 $open\_list$
- 当$open\_list$不空
    - 找到open\_list中$F$值最小的点$u$
    - if $u$是终点
        - 返回: 路径已经找到
    - 移动点$u$到$close\_list$
    - 对$u$相邻的所有点$v$
        - 如果$v$**不可通过**或者已经在$close\_list$中，略过它。反之如下。
        - 如果$v$不在$open\_list$中
            - 记录$v$的$(F,G,H)$值
            - 把$v$加入$open\_list$
            - $father[v] = u$
        - 如果$v$在$open\_list$中，重新计算$F$值,如果$F$值更小:
            - 更新$v$的$(F,G,H)$值
            - $father[v] = u$
- $open\_list$已经空,没有找到目标格,路径不存在。
:::

**核心代码**

<!-- template start -->
```c
struct node{
    int u,g,h;
    friend bool operator<(const node &a,const node &b){
        return a.g+a.h > b.g+b.h; //小的优先级高
    }
};

bool astart(){
    node start;
    priority_queue<node> q;
    q.push(start)

    while( !q.emptyl()){
        node head =q.top();q.pop();
        if( head.u is 终点) return head.u;
        if( head.u is vis) continue;
        vis[head.u ]= 1;
        
        for( each v in <head.u,v>){
            if( v is vis) continue;
            node t = {v,head.g + w,get_h(v)};
            q.push(t);
        }
    }
    return -1; //没有找到
}
```
<!-- template end -->

## 总结

你发现了吗?**A星算法和$Dijkstra$很像**!如果你会写堆优化的$Dijkstra$,应该很容易的就理解了上面的抽象过程.

**不同的在于:** 未标记点($open\_list$)的优先级计算不一样

```viz-dot
<%- include("1.dot") %>
```

## 估价函数

A*算法，是一种启发式搜索算法，我们可以自己设定一个**估价函数**，这样我们的搜索过程就会优先选择有更好的估价函数的点进行搜索

估价函数：
为了提高搜索效率，我们可以对未来可能产生的代价进行预估。我们设计一个估价函数，以任意状态输入，计算出从该状态到目标状态所需代价的估计值。
在搜索时，我们总沿着当前代价+未来估价最小的状态进行搜索。

估价函数需要满足：
　　设当前状态state到目标函数所需代价的估计值为f(state)
　　设在未来的搜索中，实际求出的从当前状态state到目标状态的最小代价为g(state)
　　对于任意的state，应该有f(state)<=g(state)
也就是说，估价函数的估值不能大于未来实际代价，估价比实际代价更优。


https://www.jianshu.com/p/27019231afec
## 代码实现

**数据:**

 - 第$1$行:地图尺寸
 - 第$2$行:起点
 - 第$3$行:终点
 - 接下来: 地图描述,$0$表示墙壁,不可以走

```
5 7
3 2
3 6
1 1 1 1 1 1 1
1 1 1 0 1 1 1
1 1 1 0 1 1 1
1 1 1 0 1 1 1
1 1 1 1 1 1 1
```
### 代码

```c
<%- include("maze_astart.cpp") %>
```

### 输出结果

```
(3,2) ==> (2,3) ==> (1,3) ==> (1,4) ==> (1,5) ==> (2,6) ==> (3,6)
0 0 1 1 1 0 0 
0 0 1 0 0 1 0 
0 1 0 0 0 1 0 
0 0 0 0 0 0 0 
0 0 0 0 0 0 0 
```

## 参考

 1. https://blog.csdn.net/zhulichen/article/details/78786493
 2. http://www.cnblogs.com/technology/archive/2011/05/26/2058842.html
 3. http://blog.csdn.net/b2b160/article/details/4057781
 4. [A星寻路算法介绍](https://www.cnblogs.com/zhoug2020/p/3468167.html)


https://bestsort.cn/2019/04/28/396/
