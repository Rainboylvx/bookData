# 图的存储


## 练习题目

 - luogu P3916 图的遍历 
 - luogu P1983 车站分级


no_open_judge: http://noi.openjudge.cn/ch0308/

## luogu P3916 图的遍历

**解析1**

使用记忆化搜索的思想,$$f[i]$$表示从$$i$$开始走的,能达到的最大点

```math
f[i] = max{f[i],f[j]},i \rightarrow j
```

代码如下,提交后发面不能全部通过

```c
#include <cstdio>
#include <cstring>

#define N 100005

int max(int a,int b){
    if(a>b) return a;
    return b;
}

int n,m;
int f[N];
int vis[N] = {0};


int first[N];
int edge_cnt = 0;
struct _e{
    int v,next;
}e[N<<1];

void addEdge(int u,int v){
    edge_cnt++;
    e[edge_cnt].v= v;
    e[edge_cnt].next = first[u];
    first[u] = edge_cnt;
}

void dfs(int x){

    vis[x] =1;
    int i;
    for(i=first[x];i!=-1;i=e[i].next){
        int v = e[i].v;
        
        if(vis[v] ==1){
            f[x] = max(f[x],f[v]);
        }
        else {
            dfs(v);
            f[x] = max(f[x],f[v]);
        }
    }

}
int main(){
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    int i,j,k;
    for (i=1;i<=n;i++){
        f[i] = i;
    }
    int t1,t2;
    for (i=1;i<=m;i++){
        scanf("%d%d",&t1,&t2);
        addEdge(t1,t2);
    }
    
    for (i=1;i<=n;i++){
        if( vis[i] == 0){
            dfs(i);
            printf("%d ",f[i]);
        }
        else
            printf("%d ",f[i]);
    }

    return 0;
}
```

然后发现,面对下面的数据是错误的

```
4 4
2 3
2 4
1 2
4 1
```

**错误的主要原因是有环.**,不符合DP的原则

**解析2:**

反向建边,从大点到小点开始遍历,已经遍历的点不用

*正确代码**

```c
#include <cstdio>
#include <cstring>

#define N 100005

int max(int a,int b){
    if(a>b) return a;
    return b;
}

int n,m;
int f[N];
int vis[N] = {0};


int first[N];
int edge_cnt = 0;
struct _e{
    int v,next;
}e[N<<1];

void addEdge(int u,int v){
    edge_cnt++;
    e[edge_cnt].v= v;
    e[edge_cnt].next = first[u];
    first[u] = edge_cnt;
}

void dfs(int x,int sf){

    vis[x] =1;
    f[x] = sf;
    int i;
    for(i=first[x];i!=-1;i=e[i].next){
        int v = e[i].v;
        if(vis[v]) continue;
        dfs(v,sf);
    }

}
int main(){
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    int i,j,k;
    int t1,t2;
    for (i=1;i<=m;i++){
        scanf("%d%d",&t1,&t2);
        addEdge(t2,t1);  //反向建立边
    }
    
    for (i=n;i>=1;i--){ //从大到小
        if( vis[i] == 0)
            dfs(i,i);
    }
    
    for (i=1;i<=n;i++)
        printf("%d ",f[i]);

    return 0;
}
```
