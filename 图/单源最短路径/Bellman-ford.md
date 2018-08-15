# bellman_ford 算法

## Bellman-ford 算法原理

**首先思考这个问题**：有一个n个点的无向图，点s到终点t的最短路最多可能经过几个点？几条边？

**答案是:**

- 最多经过n个点
- 最多经过n-1条边

见下面的ppt


链接: http://pan.baidu.com/s/1pL8KIeB 密码: qg9f


状态转移方程:

```math
dis[k][u] = \min(dis[k-1][j] + E[j][u])
```


----------------------------


## Bellman-ford 算法限制条件

 - **不能存在负权回路有向图**
 - **不能处理有负权的无向图**

## 状态压缩


如果我们写代码,存状态的话,要写$$dis[k][u]$$,$$k$$表示最多经过多少条边,可以不可以把$$k$$压缩了呢?变成$$dis[u]$$


二维代码如下:

```c
for(k=1;k<=n-1;k++)
for(j=1;j<=m;j++){//m条边
    int ss = u[j],vv=v[j],ww = w[j];
    if(dis[k][vv] < dis[k-1][ss]+ww)
        dis[k][vv] = dis[k-1][ss]+ww;
}
```

为什么我们可以这样写呢,我们通过一个实例的看一下过程.


 - 上面的点就是自己本身
 - 关键是前面的点已经是$$dis^{k}$$了,那么自己就是$$dis^{k+1}$$,不会有影响
 - 最终我们发现,即使一个$$dis[u]$$在第$$k$$次没有被更新,那么第$$k+1$$次也会被更新,最多经过$$n-1$$次就完成了所有的更新.


## 使用边集数组

按上面的思想把$$k$$压缩掉,我们发现:**只要我们保证点$$i$$至少被更新$$n-1$$,就可以得到$$dis[i]$$**

那么**我们不需要按$$1 \rightarrow n$$的点的顺序来更新!**所以我们可以使用**边集数组**来存边,只要枚举每条边,就知道了所有点的关系.

```c

struct _e {
    int u,v,w;
};
_e e[maxm];

for(k=1;k<=n-1;k++) //最多n-1次
    for(i=1;i<=m;i++){ //m条边
        int u =e[i].u,v=e[i].v;
        if( d[v] > d[u]+e[i].w)
            d[v] = d[u]+e[i].w;
    }

```


## 一句话算法

**有n个点,每一个用一个点用更新周围的点,最多更新n-1次,就得到了每个点的dis值**

----------------------------

## Bellman-ford 代码


![一个图](/book/images/一个图.jpg)

输入样列

第一行:有n个点,m条边,起点s,终点t

剩下m行:一条边的起点u,终点v,权值w

```
6 10 0 5
0 1 3
0 2 2
0 3 4
1 4 5
1 2 4
2 3 1
2 4 6
3 5 3
3 4 6
4 5 7
```

**代码**

```c
/*==================================
*Title :Bellman Ford算法
*Author:Rainboy
*Time  :2015-12-28 15:02
*update:2015-12-28 15:02
*© Copyright 2015 Rainboy. All Rights Reserved.
*=================================*/

#include <cstdio>

#define INF 0x7f7f7f7f
#define maxn 9999
#define maxe 9999

/* 边集数组 */
int u[maxe],v[maxe],w[maxe];

/* 每个点的最短路径 */
int dis[maxn];

int n,m,s,t;

void bellman_ford(){
    int i,j;
    for(i=1;i<=n-1;i++)//进行n-1轮操作
        for(j=1;j<=m;j++){
            int &ss = u[j],&tt=v[j],&ww = w[j];//引用
            
            if(dis[ss] > dis[tt] + ww)
                dis[ss] = dis[tt] +ww;

            /* 如果是无向图 要反过求一次 */
            if(dis[tt] > dis[ss] + ww)
                dis[tt] = dis[ss] +ww;
        }
    //代码完成
}

int main()
{
    int i,j,k,l;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(i=1;i<=m;i++){   //读取边上的两个点，和边长
        scanf("%d%d%d",&u[i],&v[i],&w[i]);
    }
    
    for(i=0;i<=n-1;i++){
        dis[i]= INF;
    }
    dis[s]=0;
    
    //进行bellman-ford
    bellman_ford();
    for(i=0;i<n;i++){
        printf("dis[%d]=%d\n",i,dis[i]);
    }
    return 0;
}
```

------------------------



## 技巧

### 负权回路

可以用Bellman-ford 求是否存在负权回路,如果一个图进行`n-1`轮bellman操作后,再进行一轮`dis[i]`还能更新,那就证明存在负权回路


### 结束条件

并不一定要计算$$n-1$$次,如果某一时间$$dis[i]$$的值不能被更新了,那就表明可以停止了,这种思想就是SPFA算法.

## 练习题目

 - luogu P1339 [USACO09OCT]热浪Heat Wave
