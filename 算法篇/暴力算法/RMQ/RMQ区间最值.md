---
title: RMQ区间最值
date: 2019-10-13 15:02
update: 2019-10-13 15:02
author: Rainboy
---

@[toc]

## 基本常识

 - 从1开始数10个数,停下的数是:10,**10=10+1-1**
 - 从1开始数99个数,停下的数是:99,**99=99+1-1**
 - 从2开始数99个数,停下的数是:100,**100=99+2-1**
 - 从n开始数m个数,停下的数是:**n+m-1**
 - 从10开始往前数3个数,停下的数是:8,**8=10-3+1**
 - 从n开始往前数m个数,停下的数是:**n-m+1**

## rmq原理:ST表

我们设$f[i,j]$表示**从第i个元素开始的长度为$2^j$个元素的最值**

由于元素个数为$2^j$个，所以从中间平均分成两部分，每一部分的元素个数刚好为$2^{j-1}$个，如下图:

![1](./rmq1.png)

整个区间的最大值一定是左右两部分最大值的较大值，满足动态规划的最优子结构

状态转移方程：

$$
f[i,j]=max(f[i,j-1],f[i+2^{j-1},j-1])
$$

边界条件为$f[i,0]=a[i]$

这样就可以在$O(nlogn)$的时间复杂度内预处理f数组:

```c
for(i=1;i<=n;i++) f[i][0] = a[i]; //初始化

for(j=1;(1<<j)<=n;j++){ //1<<j 表示处理的范围
    for(i=1;i+(1<<j)-1<=n;i++) // i+(1<<j)-1<=n 表示所求的范围的最后一个值在原数组范围内
        f[i][j] = max (f[i][j-1],f[i+(1<<(j-1))][j-1]);
}
```

其中`i+(1<<j)-1`表示$i+2^j-1$表示所求的范围的最后一个值在原数组范围内


## query查询

想一想:我们有1==>10个元素,我们想查$[1,8]$范围内的最值怎么查?查$[1,9]$范围内的最值怎么查?

如果查$[1,8]$那就是$f[1][3]$
如果查$[1,9]$那就是$f[1][3]$和$f[2][3]$

对于查询区间$[L,R]$，令$x$为满足$2^x<=R-L+1$的最大整数,即$x=int(log(R-L+1)/log(2))$

$[L,R]=[L,L+2^x-1] \cup [R-2^x+1,R]$，两个子区间元素个数都是$2^x$个，如图:

![2](./rmq2.png)


$$
RMQ(L,R)=max(f[L,x],f[R+1-2^x,x])
$$

```c
int query(int l,int r){
    //第一种方法
    int x = int( log(r-l+1)/log(2));

    //第二种方法,这种写法比上面的写法慢
    // 例如，luogu3865 就过不了
    int k =0;
    while( (1<<k) <=(r-l+1) ) k ++;
    k--;

    //return max(f[l][k],f[r-(1<<k)+1][r]);
    return max(f[l][x],f[r-(1<<x)+1][x]);
}
```
## 具体代码

数据:

```
10 3
1 5 7 2 9 7 2 5 9 6
1 5
6 9
1 10
```

代码:

```c
#include <cstdio>
#include <cmath>

#define N 10000

int a[N];
int f[N][32];

int n,m;//n个数,m次查询


int max(int a,int b){
    if( a > b )
        return a;
    return b;
}

int query(int l,int r){
    int x = int( log(r-l+1)/log(2));
    return max(f[l][x],f[r-(1<<x)+1][x]);
}

void rmq(){ //预处理
    int i,j;
    for(i=1;i<=n;i++ ) f[i][0]  = a[i];
    for(j=1;(1<<j)<=n;j++)
        for(i=1;i+(1<<j)-1 <=n;i++){
            f[i][j] = max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        }
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    //读入
    for (i=1;i<=n;i++)
        scanf("%d",&a[i]);
    rmq();
    for (i=1;i<=m;i++){
        int t1,t2;
        scanf("%d%d",&t1,&t2);
        printf("%d\n",query(t1,t2));
    }
    return 0;
}
```

## 题目1:  luogu P3865 ST表

模板题目：直接做
```c
#include <cstdio>
#include <cmath>

#define N 100005

int a[N];
int f[N][32];

int n,m;//n个数,m次查询


int max(int a,int b){
    if( a > b )
        return a;
    return b;
}

int query(int l,int r){
    int x = int( log(r-l+1)/log(2));
    return max(f[l][x],f[r-(1<<x)+1][x]);
}

void rmq(){ //预处理
    int i,j;
    for(j=1;(1<<j)<=n;j++)
        for(i=1;i+(1<<j)-1 <=n;i++){
            f[i][j] = max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        }
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    //读入
    for (i=1;i<=n;i++)
        scanf("%d",&f[i][0]);
    rmq();
    for (i=1;i<=m;i++){
        int t1,t2;
        scanf("%d%d",&t1,&t2);
        printf("%d\n",query(t1,t2));
    }
    return 0;
}
```

## 题目2:luogu P1440 求m区间内的最小值

todo


## 练习题目

 - luogu P1440 求m区间内的最小值
 - luogu P1816 忠诚
 - luogu P3865 ST表
 - luogu P2048 [NOI2010]超级钢琴
 - luogu P2214 [USACO14MAR]哞哞哞Mooo Moo
 - luogu P2216 [HAOI2007]理想的正方形
 - luogu P2251 质量检测
 - luogu P2471 [SCOI2007]降雨量
 - luogu P2880 [USACO07JAN]平衡的阵容Balanced Lineup
 - luogu P3763 [TJOI2017]DNA
 - luogu P4085 [USACO17DEC]Haybale Feas
