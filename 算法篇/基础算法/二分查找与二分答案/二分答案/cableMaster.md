## 题目: Cable master  

 - [题目地址](https://vjudge.net/problem/POJ-1064)


### 题目描述

有$n$条绳子，长度分别为$L[i]$。如果从他们中切割出$k$条长度相同的绳子的话，这$k$条绳子每条最长能有多长？（答案保留小数点后两位，规定1单位长度的绳子最多可以切割成100份）

### 输入格式

输入文件的第一行包含两个整数麻木$N$和$K$，用空格分隔。 $N(1 <= N <= 10000)$是库存中的电缆数量，$K(1 <= K <= 10000)$是请求件数。第一行后面是$N$行，每行一个数字，用于指定库存中每根电缆的长度（以米为单位）。所有电缆长度至少为1米，最长为100千米。输入文件中的所有长度都以厘米精度写入，小数点后面只有两位数。

### 输出格式

将$Cable Master$可以从库存中的电缆切割的部件的最大长度（以米为单位）写入输出文件，以获得所需的件数。必须以厘米精度写入数字，小数点后面只有两位数。
如果无法切割所请求的每个长度至少为1厘米的片段，则输出文件必须包含单个数字“0.00”（不带引号）。


### 样例输入

```
4 11
8.02
7.43
4.57
5.39
```

### 样例输出

```
2.00
```

## 解析

这属于情况1:答案尽可能大,根据口决:**求大朝小**


```
0 1 2 3 ..... 1000*1000*100=10^8
```

核心的在于怎么求出在某个长度数值下,能否切割出$$k$$条蝇子


## 代码

```c
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

int a[10000+5];
int n,k;
int mmax;

void init(){
    int i,j;

    mmax = -1;

    int t1,t2;
    for (i=1;i<=n;i++){
        scanf("%d.%d",&t1,&t2); // 略过.
        a[i] = t1*100+t2;
        mmax = max(a[i],mmax);
    }


    /* 从大小排序 */
    sort(a+1,a+n+1,greater<int>());
}

bool isAnswer(int len){
    int i;
    int tmp = 0;
    for(i=1;i<=n;i++){
        tmp += ( a[i]/len);
        if( tmp >= k)
            return true;
    }
    return false;
}

int bsearch(){ //upper_bounder
    int l = 1,r = mmax+1;

    while(l < r){ //upper_bound
        int m = (l+r) >> 1;
        if( isAnswer(m)){
            l = m+1;
        }
        else
            r = m;
    }

    return l-1;
}

int main(){
    while( scanf("%d%d",&n,&k) != -1) {
        init();
        int ans = bsearch();
        printf("%d",ans /100);
        printf(".");
        int t = ans %100;
        if( t < 10)
            printf("0");
        printf("%d\n",t);
    }
    return 0;
}
```

## 参考/引用

 - [poj 1064 Cable master](https://www.cnblogs.com/scau20110726/archive/2013/06/11/3131991.html)
