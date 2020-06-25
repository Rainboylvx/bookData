---
_id: "411f4de57f"
title: spfa_dfs
date: 2020-05-15 09:52
update: 2020-05-15 09:52
author: Rainboy
cover: 
---

## 说明

有关dfs版spfa基本都是出自: WC2009 姜碧野的《SPFA 算法的优化与应用》

## 资料

 - [SPFA算法的优化及应用](https://wenku.baidu.com/view/f22d0d36ee06eff9aef807e9.html)

## 判断负环

dfs_spfa:判断条件是存在一点在一条路径上出现多次。


判断正/负环,找最长路/最短路.以正环为例.

```viz-dot
digraph g{
    node[shape=circle fixedsize=true style=filled fillcolor=white colorscheme=accent8 ];
    edge[label=1]
    1->2->3;
    3->5[label="-10"];
    5->6->1;
    4->3[dir=back];
    7->4[dir=back];
    1->7[dir=back];
    {
        rank=same;
        4,3,5;
    }
    {
        rank=same;
        7,2,6;
    }
}
```

如果存在正环,则走一圈,最长路会增加,也就是环上的每个点的dis都会不停的增加,

初始化时: , dis[s] =0,其他点dis[u]=-inf

<!-- template start -->
所以利用这个性质+dfs,如果存在正环,则一个点可以被访问多次,也就是说,当点u还在栈中时候,还能再次入栈.

伪代码 :


```c
/*  求负环为什么dis清0？为什dis,ins只要清一次？
 * */
namespace spfa_dfs{
    using namespace xlx1;
    bool ins[maxn]; //在栈内
    int dis[maxn]; // double ,long long 根据题意更改
    bool dfs(int u){ //找负环
        ins[u] = 1;
        for( int i = head[u]; ~i; i = e[i].next){
             int v = e[i].v,w=e[i].w;
             if( dis[v] > dis[u]+w){
                 dis[v] = dis[u]+w;
                 if( ins[v] || dfs(v) ) return true;
             }
        }
        ins[u] = 0;
        return 0;
    }
    bool wk(){
        memset(dis,0,sizeof(dis));
        memset(ins,0,sizeof(ins)); // bool的全局变量可能不全是0
        for(int i=1;i<=n;++i){
            if( dfs(i) ) return 1;
        }
        return 0;
    }
}
```
<!-- template end -->

注意:限制条件,这个方法只能判断从起点出发能到到达的正环,也就是图是连通的.

## 练习题目

 - poj 2949
