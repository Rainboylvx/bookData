# 广度优先搜索

广度优先搜索,Breadth First Search(BFS),使用队列的搜索算法,常用于解决搜索中的最短,最少等最值问题.

![1](./自然界的BFS.jpg)

## 知识网络

```viz-dot
digraph G {
    node[shape=rect];
    "队列"->"基础的BFS"->{"双向BFS","A*算法"}
}
```

## 动画演示

 - [动画演示1](http://yanhan.github.io/bfsvis/)
 - [动画演示2](https://www.hackerearth.com/zh/practice/algorithms/graphs/breadth-first-search/visualize/)
 - [动画演示3](https://www.cs.usfca.edu/~galles/visualization/BFS.html)


bfs最大的特点,就是这些点按层级的顺序访问.因为这个特点,我们可以使用bfs来求一些有关,最短路径,最小步骤等相关问题.


## 练习题目列表

 - 穿越泥地 Mud Puddles[地址](https://vjudge.net/problem/POJ-3626)
 - 抓住那头牛 bfs 剪枝 poj 3278
 - 素数路    数位bfs poj 3126
 - 推箱子    bfs  poj 1457
 - dearboy's Puzzle bfs poj 2308
 - 八数码  bfs  poj 1077
 - bzoj 1306 剪枝
