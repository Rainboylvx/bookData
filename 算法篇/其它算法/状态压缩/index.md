---
title: 状态压缩:序
date: 2019-02-27 08:47
update: 2019-02-27 08:47
author: Rainboy
---

## 学习路线

```viz-dot
digraph G {
    ranksep=1;
    node[shape="rect"];
    1[label="STL <bitset>"]
    2[label="原生位操作"]
    x[label="状态压缩",fillcolor=lightblue,style=filled]
    {1,2}->x->{3,4};
    3[label="状压DP",style=dashed]
    4[label="状压线段树",style=dashed]
}
```

关于$STL$的中$<bitset>$,请查看**语法篇**
