#!/usr/bin/env python
from cyaron import *

n = randint(2,10);
n = 500000
print(n)
charsets = "wy"
for i in range(0,n):
    str = String.random(n,charset=charsets)
    print(str)

n = 5;
print(n)
tree = Graph.tree(n) # 生成一棵n个节点的随机树
print(' '.join(list([ str(x+1) for x in range(0,n)])))
for edge in tree.iterate_edges(): # 遍历所有边，其中edge内保存的也是Edge对象
    print(edge.start,edge.end)
    # edge.start # 获取这条边的起点
    # edge.end # 获取这条边的终点
    # edge.weight # 获取这条边的边权
    # io.input_writeln(edge) # 输出这条边，以u v w的形式
