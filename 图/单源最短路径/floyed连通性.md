## floyed判断两点的连通性






**核心代码**

```c
for(int k=1;k<=n;k++)
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    dis[i][j]=dis[i][j]||(dis[i][k]&&dis[k][j]);
```

## 练习题目

todo!!
