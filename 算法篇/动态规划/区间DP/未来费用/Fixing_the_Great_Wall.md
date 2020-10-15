---
_id: "53be18d83b"
title: Fixing the Great Wall
date: 2019-05-06 16:47
update: 2019-05-06 16:47
author: Rainboy
---

## 题目地址

 - slimeoj
 - [uva 1336 Fixing the Great Wall ](https://vjudge.net/problem/uva-1336) 

## 解析

和关路灯一样的思路,只不过多了一个固定消耗,在计算的过程中只要加上就行.

f(i,j,0) 修复好区间$[i,j]$后,且位于$i$的情况下的最少消耗.这里的消耗把区间$[i,j]$外的消耗也计算上的.


注意的数据输入判定结束的问题,和使用`floor`

## 代码

```c
/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 05月 05日 星期日 17:38:57 CST
* problem: uva-1336
* tag: 未来费用
*
* f[i][j][0] = min{f[i+1][j][0]+cal(i,i+1,i+1,j), f[i+1][j][1]+cal(i,j,i+1,j)}  + C[i]
* cal(x,y,i,j) 从x到y的时间内,i->j 已经修好了的条件下 能达到的消耗
*
* 输入输出有问题 : https://blog.csdn.net/xl2015190026/article/details/52669689
* floor(向下取整)
*----------------*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


int n,v,x;

double pre_sum[1005];
double f[1005][1005][2];


struct _node {
    int x,c,d;

    bool operator<(_node &a){
        if( x < a.x)
            return true;
        return false;
    }
}node[1005];

double cal(int x,int y,int i,int j){
    int tot =  pre_sum[n]+pre_sum[i-1]-pre_sum[j];
    return fabs(node[y].x-node[x].x)/v * tot;
}

void init(){
    //memset(f,0x42,sizeof(f)); // double 的最大值 https://blog.csdn.net/popoqqq/article/details/38926889
    pre_sum[0] = 0;
    int i;
    for (i=1;i<=n;i++){
        scanf("%d%d%d", &node[i].x, &node[i].c, &node[i].d);
    }
    sort(node+1,node+1+n);
    for(i=1;i<=n;i++)
        pre_sum[i] = pre_sum[i-1] + node[i].d;
}



int main(){
    while(scanf("%d%d%d", &n, &v, &x) == 3 && n) {

        init();
        int i,j,k,l;
        for(l=1;l<=n;l++){ //初始化
            f[l][l][0] = f[l][l][1] =fabs(x-node[l].x)/v *pre_sum[n] + node[l].c;
        }

        for(l=2;l<=n;l++){      //长度
            for(i=1;i+l-1<=n;i++){//起点
                j = i+l-1; //终点
                f[i][j][0] = min(f[i+1][j][0]+cal(i,i+1,i+1,j),f[i+1][j][1]+cal(i,j,i+1,j)) + node[i].c;
                f[i][j][1] = min(f[i][j-1][0]+cal(i,j,i,j-1),f[i][j-1][1]+cal(j-1,j,i,j-1)) + node[j].c;
            }
        }
        printf("%0.lf\n",floor(min(f[1][n][0],f[1][n][1])));
    }
    return 0;
}
```
