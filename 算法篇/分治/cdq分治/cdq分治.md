---
title: cdq分治
date: 2019-11-29 18:53
update: 2019-11-29 18:53
author: Rainboy
---

@[toc]

## 一维偏序

### 题目描述

有一组数列$a_1, a_2, a_3, \cdots,a_n$, 如果$a_j \leq a_i$满足的条件的j的数量为d,那么$f[i] = d$,输出$f[i]$ 分别为$1,2,3,\cdots n$的数量

### 样例输入

```
8
3 5 5 3 3 6 6 12
```

### 样例输出

```
0 3 0 2 0 2 1 0
```

### 解析

显然应该先排序:`3 3 3 5 5 6 6 12`,然后去重:`3 5 6 12`,然后一次计数就可以了,核心操作为**排序**,时间复杂度$O(nlog
n)$,代码如下

::: fold
```c
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e5+5;
struct _node{
    int val,cnt;
    bool operator<(const _node &b){
        return val < b.val;
    }
};
_node a[maxn],b[maxn];
int f[maxn];
int out[maxn];
int n;
int main(){
    scanf("%d",&n);
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i].val);
        a[i].cnt = 1;
        b[i] = a[i];
    }
    sort(a+1,a+1+n);    //排序
    int tot = 1;
    for(i=2;i<=n;i++){
        if( a[i].val == a[i-1].val){
            a[tot].cnt++;
        }
        else {
            a[++tot] = a[i];
        }
    }
    int cnt = 0;
    for(i=1;i<=tot;i++){
        cnt += a[i].cnt;
        f[i] = cnt-1;
        out[ f[i] ] += a[i].cnt; //计数
    }
    for(i=1;i<=n;i++){
        printf("%d ",out[i]);
    }

    return 0;
}
```
:::

## 二维偏序

有一组二元数列$(1,b_1), (2,b_2), (3,b_3), \cdots, (n,b_n)$, 如果$j \leq i$且$b_j \leq b_i$满足的条件的j的数量为d,那么$f[i] = d$,输出$f[i]$ 分别为$1,2,3,\cdots n$的数量.


### 解析

这不就是求**逆序对**!,明显可以用**归并排序**或者**树状数组**来求.时间复杂度$O(nlogn)$

如果问题变成：二元数列$(a_1,b_1), (a_2,b_2), (a_3,b_3), \cdots, (a_n,b_n)$,如果$a_j \leq b_i$且$b_j \leq b_i$满足的条件的j的数量为d,那么$f[i] = d$,输出$f[i]$ 分别为$1,2,3,\cdots n$的数量.

先对第一维进行排序

## 三维偏序

### 题目描述

有一组三元数列$(1,b_1,c_1), (2,b_2,c_2), (3,b_3,c_3), \cdots, (n,b_n,c_n)$, 如果$j \leq i$且$b_j \leq b_i$,$c_j \leq c_i$满足的条件的j的数量为d,那么$f[i] = d$,输出$f[i]$ 分别为$1,2,3,\cdots n$的数量。例如下面的数据：

```
1 1 2
2 2 1
3 2 2
4 3 1
5 3 2
6 3 1
7 3 3
8 1 1
9 1 2
10 3 3
```

### 解析

显然第一维度已经有序,我们不需要考虑它.

核心思想:我们可以对第二维进行归并排序,然后用树状数组来维护第三维.  :thinking::thinking::thinking: $what??$

如下



<<<< viz-gallery(title="动画演示",engine="dot",height="500")

<% 
var log =["归并排序最后一步,合并left,right两个有序序列",
"取出left第一个元素放入tmp内,并根据第三维,更新树状数组",
"取出right第一个元素放入tmp内,不用更新树状数组!!,查询BIT上此时≤1(第三维的值)的区间和!",
"取出right第一个元素放入tmp内,不用更新树状数组!!,查询BIT上此时≤1(第三为的值)的区间和!得到满足条件的三元组数量为1",
"取出left第一个元素放入tmp内,并根据第三维,更新树状数组",
];
var engine = "dot"
var n=5
for(let i=1;i<=n;i++){
    var page = `dot/a${i}.dot`
%>

``` <%= engine || ""%> <%= log[i-1] || "" %>
<%- include(page) %>
```
<%}%>

<<<<


### 核心的核心

::: warning
1. 为什么left区域的元组加入tmp时更新BIT
2. 为什么right区域的元组加入tmp时只查询,不更新BIT?
:::



在$right$侧显然**已经排序好,并计算过**

```c
#include<cstdio>
#include<cstring>
#include<algorithm>
#define RG register
#define R RG int
using namespace std;
const int N=1e5+9,SZ=2.2e6;
char buf[SZ],*pp=buf-1;//fread必备
int k,a[N],b[N],c[N],p[N],q[N],v[N],cnt[N],ans[N],*e;
inline int in(){
    while(*++pp<'-');
    R x=*pp&15;
    while(*++pp>'-')x=x*10+(*pp&15);
    return x;
}
void out(R x){
    if(x>9)out(x/10);
    *++pp=x%10|'0';
}
inline bool cmp(R x,R y){//直接对数组排序，注意三关键字
    return a[x]<a[y]||(a[x]==a[y]&&(b[x]<b[y]||(b[x]==b[y]&&c[x]<c[y])));
}
inline void upd(R i,R v){//树状数组修改
    for(;i<=k;i+=i&-i)e[i]+=v;
}
inline int ask(R i){//树状数组查前缀和
    R v=0;
    for(;i;i-=i&-i)v+=e[i];
    return v;
}
void cdq(R*p,R n){//处理一个长度为n的子问题
    if(n==1)return;
    R m=n>>1,i,j,k;
    cdq(p,m);cdq(p+m,n-m);//递归处理
    memcpy(q,p,n<<2);//归并排序
    for(k=i=0,j=m;i<m&&j<n;++k){
        R x=q[i],y=q[j];
        if(b[x]<=b[y])upd(c[p[k]=x],v[x]),++i;//左边小，插入
        else  cnt[y]+=ask(c[p[k]=y])     ,++j;//右边小，算贡献
    }
    for(;j<n;++j)cnt[q[j]]+=ask(c[q[j]]);//注意此时可能没有完成统计
    memcpy(p+k,q+i,(m-i)<<2);
    for(--i;~i;--i)upd(c[q[i]],-v[q[i]]);//必须这样还原树状数组，memset是O(n^2)的
}
int main(){
    fread(buf,1,SZ,stdin);
    R n=in(),i,j;k=in();e=new int[k+9];
    for(i=0;i<n;++i)
        p[i]=i,a[i]=in(),b[i]=in(),c[i]=in();
    sort(p,p+n,cmp);
    for(i=1,j=0;i<n;++i){
        R x=p[i],y=p[j];++v[y];//模仿unique双指针去重，统计v
        if(a[x]^a[y]||b[x]^b[y]||c[x]^c[y])p[++j]=x;
    }
    ++v[p[j++]];
    cdq(p,j);
    for(i=0;i<j;++i)
        ans[cnt[p[i]]+v[p[i]]-1]+=v[p[i]];//答案算好
    for(pp=buf-1,i=0;i<n;++i)
        out(ans[i]),*++pp='\n';
    fwrite(buf,1,pp-buf+1,stdout);
}
```



## 练习题目

 - [luogu P3810 【模板】三维偏序（陌上花开）](https://www.luogu.com.cn/problem/P3810)
 - [CQOI2011动态逆序对](https://www.luogu.org/problemnew/show/P3157)
 - [Violet 天使玩偶/SJY摆棋子](https://www.luogu.org/problemnew/show/P4169)

## 参考/引用

 - [洛谷日报 CDQ分治学习笔记](https://www.cnblogs.com/ljc20020730/p/10395866.html)
 - [CDQ分治总结（CDQ，树状数组，归并排序） - Flash_Hu - 博客园](https://www.cnblogs.com/flashhu/p/9381075.html)

