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

所以利用这个性质+dfs,如果存在正环,则一个点可以被访问多次,也就是说,当点u还在栈中时候,还能再次入栈.

伪代码 :


```c
bool spfa(int u) {
	in_stack[u] = 1;
	each edge has u:
	    v = edge.v;
	    if( dis[v] < dis[u] + edge.w){
	        dis[v] = dis[u] + edge.w;
	        if( in_stack[v] || spfa(v)){
	            in_stack[v] = 0;
	            return 1;
	        }
	    }
	in_stack[v] = 0;
	return 0;
```

注意:限制条件,这个方法只能判断从起点出发能到到达的正环,也就是图是连通的.

## 练习题目

 - poj 2949
