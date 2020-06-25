---
_id: "31d4e37b3d"
title: kruskal
date: 2020-05-12 19:55
update: 2020-05-12 19:55
author: Rainboy
---

@[toc]

# kruskal 算法

## 算法原理

避圈法,从小到大枚举每一条边,如果边的两个端点,不在同一个集合内,就可以选这个边.


[kruskal算法动画](https://www.cs.usfca.edu/~galles/visualization/Kruskal.html)


## 模板

<!-- template start -->
```c
// 向量星 略

/* ================= 并查集 =================*/
const int maxn = 1e5+5;
int fa[maxn];
//并查集 初始化
inline void bcj_init(int x){ for(int i=1;i<=x;i++) fa[i] = i; }
//查找 and 路径压缩
int find(int x){ 
    if( x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
/* ================= 并查集 end =================*/

bool cmp( edge a,edge b) {return a.w < b.w;}
// 传入点数，返回mst的值，不连通返回-1
int Kruskal(int n){
    bcj_init(n); //初始化
    sort(e+1,e+1+edge_cnt,cmp); //对边从小到大排序
    int ans = 0,cnt = 0; //答案，选边的数量

    for(int i = 1; i<=edge_cnt ; ++i){
        int u =e[i].u, v =e[i].v, w =e[i].w; 
        int f1 =find(u),f2 = find(v);
        if( f1 != f2){ //不再同一个集合
            ans+=w;
            cnt++;
            fa[f2] = f1;
        }
        if( cnt == n-1) break;
    }
    if( cnt < n -1) return -1;
    return ans;
}
```
<!-- template end -->

## 具体代码

图:

![1](./G.png)

数据:

```
6 10
1 2 4
1 3 2
2 3 5
2 4 4
2 5 3
3 4 1
3 6 2
5 4 6
5 6 4
6 4 2
```

```c
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


#define N 100 //点的数量

int n,m;
//边集数组
struct edge {
    int u,v,w;
}E[N];
int size = 0;

void addEdge(int x,int y,int z){
    size++;
    E[size].u = x;
    E[size].v = y;
    E[size].w = z;
}

bool cmp(const edge &a,const edge &b){
    if( a.w > b.w)
        return false;
    return true;
}

//并查集
int fa[N];

int find(int x){
    int t =x;
    while(fa[t] != t) //不停的往上走
        t=fa[t];
    int i = x,j;//路径压缩，再走一便路程，把走过的点都指向根
    while(i != t){
        j= fa[i];
        fa[i] = t; // 把这个点指向根
        i = j;
    }
    return t;
}

int kruskal(int s){
    int ans = 0;
    int i,j;
    int k=0 ;
    for(i=1;i<=n;i++) fa[i] = i; //并查集初始化
    for(i=1;i<=m;i++){
        int f1 = find(E[i].u);
        int f2 = find(E[i].v);
        if( f1 != f2){
            ans += E[i].w;
            fa[f1] = f2;
            k++;
            if( k == n-1) break; //选n-1条边
        }
    }
    if( k < n-1)
        return -1; //返回不可能
    else 
        return ans;
}

int main(){
    scanf("%d%d",&n,&m);
    int i,j;
    //读入图
    for(i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        addEdge(x,y,z);
    }
    sort(E+1,E+size+1,cmp);
    int ans = kruskal(1);
    printf("%d",ans);
    return 0;
}
```

## 练习题目

 - luogu P2126 Mzc家中的男家丁
 - luogu P1550 [USACO08OCT]打井Watering Hole
 - luogu P1265 公路修建 
