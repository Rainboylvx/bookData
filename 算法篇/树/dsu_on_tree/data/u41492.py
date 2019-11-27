#!/usr/bin/env python
from cyaron import *

n = 5;
print(n)

tree = Graph.tree(n) # 生成一棵n个节点的随机树
for edge in tree.iterate_edges(): # 遍历所有边，其中edge内保存的也是Edge对象
    print(edge.start,edge.end)
print(' '.join(list([ str(randint(1,n)) for x in range(0,n)])))
print(n)
print(' '.join(list([ str(x+1) for x in range(0,n)])))
