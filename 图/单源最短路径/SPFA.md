

## SPFA 算法原理

见下面的ppt


链接: http://pan.baidu.com/s/1nvnQiVZ 密码: 2pc1



SPFA算法原理：

 - 加入了队列优化的Bellman_ford算法；有些情况下，ford算法会重复运算某些点；
 - SPFA 当一个点的dis被更新的时候，也许与他相邻的点也需要被更新，所以把这个点加入队列
 - 如果队列为空，那么就结束运算

注意：加入点的进入队列的时候，还需要判断，点是否已经在队列里了，如果已经在，就不需要加入队列了
一个点被拿出队列的时候，也许还可以在被放进去，所以出队时要设为false


----------------------------

## 一句话算法

 - SPFA是对bellman-ford算法的队列优化
 - 一个点被更新了,它还有可能更新周围的点,入队



## 代码


![二个图](/images/二个图.png)

输入数据

第一行:n,e;n个点,e条边

第二行:s,t;s起点,t终点

剩下e行:`u v w`分别是一条边的起点,终点,权值

```
5 7
1 5
1 2 2
1 3 4
1 4 7
2 3 1
3 4 1
2 5 2
3 5 6
```

**代码**

```c
/*============================================================================
* Title : SPFA算法--边集数组实现
* Author: Rainboy
* Time  : 2016-04-12 10:13
* update: 2016-08-29 16:54
* © Copyright 2016 Rainboy. All Rights Reserved.
*=============================================================================*/




/*-----------------------------------------------------------------------------
 *  SPFA算法原理：
 *      加入了队列优化的Bellman_ford算法；有些情况下，ford算法会重复运算某些点；
 *      SPFA 当一个点的dis被更新的时候，也许与他相邻的点也需要被更新，所以把这个点加入队列
 *      如果队列为空，那么就结束运算
 *   注意：加入点的进入队列的时候，还需要判断，点是否已经在队列里了，如果已经在，就不需要加入队列了
 *          一个点被拿出队列的时候，也许还可以在被放进去，所以出队时要设为false
 *-----------------------------------------------------------------------------*/

/* 自己维护队列的版本 */
#include <cstdio>
#include <cstring>

#define maxv 1000
#define maxe 1000

const int INF = 0x7f7f7f7f;

const int lq =  2*maxv+5; //队列长度  能找都要那么多

int dis[maxv];
int queue[lq+1];
int head,tail;

bool inQueue[maxv] = {0};//点是否在队列中
int pre[maxv]={0};      //前趋

//邻接表-数组实现
int u[maxe],v[maxe],w[maxe];
int first[maxv];
int next[maxe];


int s,t;//起点,终点
int n,e;// 多少点，多少边


void spfa(int s){
    /* s点加入队列 */
    dis[s] =0;
    head =tail = -1;
    queue[++tail] =s;
    inQueue[s] = 1;

    int i,tmp;
    while( head != tail){ //队列非空
        tmp = queue[++head];  //取首点
        inQueue[tmp] = false;     //不在队列中

        for(i=first[tmp];i!=-1;i=next[i])   //更新周围的点
            if(dis[v[i]] > dis[tmp] + w[i]){
                dis[v[i]] = dis[tmp] +w[i];
                pre[v[i]] = tmp;

                /* 被更新的点不在队列中,那就加入队列中 */
                if(!inQueue[v[i]]){
                    queue[++tail]=v[i];
                    inQueue[v[i]] = 1;
                }
            }
    }
}


int main(){
    int i,j,k;

    //初始化
    scanf("%d%d",&n,&e);
    scanf("%d%d",&s,&t);

    memset(dis,0x7f,sizeof(dis));

    /* 邻接表来存图 */
    memset(first,-1,sizeof(first));//初始化first
    for(i=1;i<=2*e;i+=2){
        scanf("%d%d%d",&u[i],&v[i],&w[i]);
        v[i+1] = u[i],u[i+1] =v[i],w[i+1]=w[i]; //无向图 一条边存两遍

        next[i] = first[u[i]];
        first[u[i]] = i;

        next[i+1] = first[u[i+1]];
        first[u[i+1]] =i+1;
    }

    spfa(s);

    /* 输出终点dis */
    printf("dis[%d] = %d\n",t,dis[t]);

    /* 输出路径 */
    for(i=t;i!=0;i=pre[i])
        printf("%d ",i);
    return 0;
}

```
