---
_id: "911fd7a889"
title: 序列中不超过K的对数
date: 2019-11-08 13:58
update: 2019-11-08 13:58
author: Rainboy
---
@[toc]
## 描述

一个序列n中,任意两个数(i,j)的和不超过k的个数.


**输入**

```
6 6
1 2 3 4 5 6
```

**输出**

```
6
```

## 解析

上面的输入样例中,答案为$8$,我们写出所的的对数为:

```
(1,2) (1,3) (1,4) (1,5)
(2,3) (2,4)
```

发现如下的规律:

 - 先考虑最小的数$1$,可以和$5$组合,那么区间$[2,5]$内的数都可以和$1$组合
 - 上面我们其实在区间$[1,5]$内寻找,然后应该在它的子区间$[2,5]$内寻找
    - 想一想:为什么在$[2,6]$内寻找?
 - $2$和$5$不能组合,那应该缩小一下右边,接下来在区间$[2,4]$内寻找
 - 规律:**每一次寻找的区间都是上一个寻找区间的子区间**



<<<< viz-gallery(title="动画",engine="dot",height="400")

<% 
var log =["原始","区间1","区间2"]
var engine = "dot"
for(let i=1;i<=3;i++){
    var page = `dot/k-pair/${i}.dot`
%>

``` <%= engine || ""%> <%= log[i-1] || "" %>
<%- include(page) %>
```
<%}%>

<<<<


## 代码

```c
#include <cstdio>
#include <algorithm>
using namespace std;

int n,k;
int a[100];


int main(){
    scanf("%d%d",&n,&k);
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1, a+1+n);

    int l=1,r=n;
    int ans = 0;

    while( l < r){
        if(a[l] + a[r] <= k){
            ans += r - l;
            l++;
        }
        else
            r--;
    }
    printf("%d\n",ans);

    return 0;
}
```
