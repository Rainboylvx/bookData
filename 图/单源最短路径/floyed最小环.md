# floyed求最小环

## 求无向图最小环

题目地址: [ hdu 1599 find the mincost route ](https://vjudge.net/problem/hdu-1599)


这里是要求无向图最小环,最小环:最少有三个点

![4](./floyed最小环.png)

存在一个最小环,那么:

 - 设最小环上的点的编号最大编号为$$k$$
 - $$i,j$$是与$$k$$相邻的点
 - 对于最小环的剩下一部分必然是$$i$$到$$j$$的最短路径$$f(i,j)$$,因为最佳
 - $$f(i,j)$$所经过的最大点绝对不超过$$k$$

```math
ans= f(i,j)+Graph[i][k]+Graph[j][k] 
```

所以**我们只需要修改floyed**的代码就可以找到**最小环**

 - 枚举$$k$$的时候,在更新$$f(i,j)$$自己本身之前,这个时候的$$f(i,j)$$一定是**经过的点的最大值不超过$$k-1$$的$$i \rightarrow j$$的最短路**.
 - 在这个时候我们找到这样的$$i,j$$
  - 是$$k$$的相邻点
  - $$i <k,j<k, i != j$$
 - 那么可以求出$$i,j,k$$所在环的最小环的值A
 - 所有的A中最小的那个就是**最小环的值**


```c
for(k=1；k<=n；k++) {
    for(i=1；i<k；i++)
        for(j=i+1；j<k；j++) // 为什么是i+1,不用枚举f[i][j]后又枚举f[j][i],对称性
            if(f[i][j]+m[i][k]+m[k][j]<ans)
                ans=f[i][j]+m[i][k]+m[k][j]；
    for(i=1；i<=n；i++)
        for(j=1；j<=n；j++)
            if(f[i][k]+f[k][j]<f[i][j])
                f[i][j]=f[i][k]+f[k][j]；
}
```

**如果输出最小环上的点?**

每一次得到一个新的最小环值$$ans$$的时候,就把$$f(i,j)$$路径上的点保存下来.

**代码**
注意:切记别爆inf*3即可,笔者第一次提交就错在这里`_(:з」∠)_`

```c
#include <cstdio>
#include <cstring>

int n,m;

int inf = 0x1f1f1f1f;
int f[110][110];
int g[110][110];
int i,j,k;
int ans;

int min(int a,int b){
    if(a < b)
        return a;
    return b;
}

//初始化,相关数据
void init(){

    memset(f,0x1f,sizeof(f));
    memset(g,0x1f,sizeof(g));
    ans = inf;

    //读取数据

    for(i=1;i<=m;i++){
        int t1,t2,t3;
        scanf("%d%d%d",&t1,&t2,&t3);
        g[t1][t2]= g[t2][t1] =  min(t3, g[t1][t2]);
        f[t1][t2]= f[t2][t1] = min(t3, f[t1][t2]); //边界
    }
}

void floyed(){

    for (k=1;k<=n;k++){
        
        for(i=1;i<k;i++) //找最小值
            for(j=i+1;j<k;j++)
                ans =min( ans, g[i][k] + g[k][j] + f[i][j]);

        //更新
        for(i=1;i<=n;i++) 
            for(j=1;j<=n;j++)
                f[i][j]= min( f[i][j],f[i][k]+f[k][j]);

    }
}


int main(){
    
    while( scanf("%d%d",&n,&m) !=EOF){
        init();
        floyed();
        if( ans < inf)
            printf("%d\n",ans);
        else
            printf("It's impossible.\n");
    }
    return 0;
}


```
## 有向图最小环

题目地址:[vijos 1243 最佳路线](https://vijos.org/p/1423)

对于上面代码红色部分，这个j之所以从i+1开始就可以了是因为无向图的对称性质，而有向图并不具有这个性质，所以需要改动.  
但是要是仔细想想的话，有向图的最小环其实只要直接跑一遍floyd，然后遍历一遍dis[i][i]即可，因为图是无向的所以不必担心出现重边啊


代码 todo!!

## 练习题目

 - [poj 1734 Sightseeing trip ](https://vjudge.net/problem/POJ-1734)
 - [noip2015 信息传递](https://www.luogu.org/problemnew/show/P2661)
