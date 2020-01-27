---
title: "IDA*"
date: 2019-12-11 00:13
update: 2019-12-11 00:13
author: Rainboy
cover: 
---

<!-- template start -->
 - A* 用在BFS上 ,A* = 优先队列 + 估价函数
 - IDA*用在DFS上,IDA* = 迭代加深 +　估价函数
<!-- template end -->

<!-- template start -->
```c
bool iddfs(int d,int maxd, args...){
    if( d == maxd+1){
        if( 符合题意 ) return true;
    }

    for(int abble = 1;  abble <= 最大次数; abble++ ){
        if( 估价函数(d,maxd) 符合条件　)
            iddfs(d+1,maxd, args...)
    }
}

//迭代加深
for( int maxd = 1 ;  ; maxd++){
    if(iddfs(dep=1,maxd, ... ) ) break;
}
```
<!-- template end -->

## 练习题目

- hard version
- [SCOI2005]骑士精神和UVA11212 Editing a Book）。
