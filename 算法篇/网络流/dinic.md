## 连续最短增广路算法-Dinic
https://www.cnblogs.com/LUO77/p/6115057.html
http://cnblogs.com/SYCstudio/p/7260613.html
https://blog.csdn.net/u012914220/article/details/23865829


为了解决我们上面遇到的低效方法，Dinic算法引入了一个叫做**分层图**的概念。具体就是对于每一个点，我们根据从源点开始的$$bfs$$序列，为每一个点分配一个深度，然后我们进行若干遍$$dfs$$寻找增广路，每一次由$$u$$推出$$v$$必须保证$$v$$的深度必须是$$u$$的深度$$+1$$。下面给出代码




层次图上的任意一条路径都是从s到层次1到层次2……直到t，可以发现，每一条这样的路径都是一条s-t最短路，这样求，不会出现走多余的边的情况。ps ???? 为什么不会走多余边?


## 分层
顶点的层次：在残留网络中，把从源点到顶点u的最短路径长度（该长度仅仅是值路径上边的数目，与容量无关），称为顶点u的层次，记为level(u)。源点Vs的层次为0。


将残留网络中所有的顶点的层次标注出来的过程称为分层。



根据层次网络定义，层次网络中任意的一条弧<u,v>，有满足level(u)+1 == level(v)，这条弧也叫允许弧。直观的说，层次网络是建立在残留网络基础之上的一张“最短路径图”。从源点开始，在层次网络中沿着边不管怎么走，到达一个终点之后，经过的路径一定是终点在残留网络中的最短路径。

## Dinic 算法过程

（1）初始化容量网络和网络流。

（2）构造残留网络和层次网络，若汇点不再层次网络中，则算法结束。

（3）在层次网络中用一次DFS过程进行增广，DFS执行完毕，该阶段的增广也执行完毕。

（4）转步骤（2）。

## Dinic算法复杂度分析

与最短增广路算法一样，Dinic算法最多被分为n个阶段，每个阶段包括建层次网络和寻找增广路两部分，其中建立层次网络的复杂度仍是O（n*m)。

现在来分析DFS过程的总复杂度。在每一阶段，将DFS分成两部分分析。

（1）修改增广路的流量并后退的花费。在每一阶段，最多增广m次，每次修改流量的费用为O（n）。而一次增广后在增广路中后退的费用也为O(n)。所以在每一阶段中，修改增广路以及后退的复杂度为O(m*n)。

（2）DFS遍历时的前进与后退。在DFS遍历时，如果当前路径的最后一个顶点能够继续扩展，则一定是沿着第i层的顶点指向第i+1层顶点的边向汇点前进了一步。因为增广路经长度最长为n，所以最坏的情况下前进n步就会遇到汇点。在前进的过程中，可能会遇到没有边能够沿着继续前进的情况，这时将路径中的最后一个点在层次图中删除。

注意到每后退一次必定会删除一个顶点，所以后退的次数最多为n次。在每一阶段中，后退的复杂度为O（n）。

假设在最坏的情况下，所有的点最后均被退了回来，一共共后退了n次，这也就意味着，有n次的前进被“无情”地退了回来，这n次前进操作都没有起到“寻找增广路”的作用。除去这n次前进和n次后退，其余的前进都对最后找到增广路做了贡献。增广路最多找到m次。每次最多前进n个点。所以所有前进操作最多为n+m*n次，复杂度为O（n*m）。

于是得到，在每一阶段中，DFS遍历时前进与后退的花费为O（m*n）。

综合以上两点，一次DFS的复杂度为O（n*m）。因此，Dinic算法的总复杂度即O（m*n*n）。

## 朴素Dinic

题目地址：[luogu P3376 【模板】网络最大流](https://www.luogu.org/problemnew/show/P3376)

**代码:**

```c
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define maxn 10005
#define maxe 200005

int n,m,s,t;
int dep[maxn]; //分层,点i的层数


//向量星
struct _e {
    int u,v,next,cap;
};
_e e[maxe];
int head[maxn];
int cnt = 0;

//边的编号从0开始
void addEdge(int u,int v,int cap){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].cap = cap;
    e[cnt].next = head[u];
    head[u] = cnt++;
}


//返回值表示是否能达到t点
bool bfs(){ //给各个点分层
    memset(dep,-1,sizeof(dep)); //初始化
    queue<int> q;
    dep[s] = 1; //起点的 层
    q.push(s);
    
    while(q.empty() == false){
        int now = q.front(); q.pop();
        int i;
        for(i=head[now];i!=-1;i=e[i].next){
            int v = e[i].v;
            //v没有访问过 且 容量可通行
            if(dep[v] == -1 && e[i].cap >0){ 
                dep[v] = dep[now] +1;
                q.push(v);
            }
        }
    }

    return dep[t] != -1; // !=-1 表示能分层到汇点
}

// u 当前点,low u前面的路径上的最小容量
int dfs(int u,int low){
    if( u == t) return low;
    int i;
    for(i=head[u]; i !=-1;i=e[i].next){
        int v = e[i].v;
        // 是下一层的点 且 可通行
        if(dep[v] == dep[u]+1 && e[i].cap > 0){
            int flow = dfs(v,min(low,e[i].cap));
            if( flow > 0){ //从v开始可以走到汇点
                e[i].cap -=flow;    //同向容量 缩小
                e[i^1].cap += flow; //反向容量 加大
                return flow;        //回溯
            }

        }
    }
    
    return 0; //从u点到不了汇点
}

int dinic(){
    int tmp  = 0;
    while( bfs()){ //分层
        int f ; 
        while( f  = dfs(s,0x7f7f7f7f)){ //多次dfs,直到找不到路
            tmp +=f;
        }
    }
    return tmp;
}


int main(){
    
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);
    int t1,t2,t3;
    int i,j,k;
    memset(head,-1,sizeof(head));
    for (i=1;i<=m;i++){
        scanf("%d%d%d",&t1,&t2,&t3);
        addEdge(t1,t2,t3); //正向边
        addEdge(t2,t1,0);  //反向边
    }
    int maxflow =dinic();
    printf("%d\n",maxflow);
    return 0;
}
```

## 当前弧优化

每次增广一条路后可以看做“榨干”了这条路，既然榨干了就没有再增广的可能了。但如果每次都扫描这些“枯萎的”边是很浪费时间的。那我们就记录一下“榨取”到那条边了，然后下一次直接从这条边开始增广，就可以节省大量的时间。这就是 当前弧优化 。

具体怎么实现呢，先把链式前向星的head数组复制一份，存进cur数组，然后在cur数组中每次记录“榨取”到哪条边了。

我们知道dinic算法中的dfs是为了在可行增广路中找到最小容量。而找增广路需要遍历每个点所连接的边，直至找到一条可到达终点的路。例如，我们在第一次dfs时找到了一条增广路：顶点1中的第3条边，顶点2中的第4条边，顶点3中的第4条边，顶点5中的第2条边。这四条边是我们在第一次dfs寻找到的可行路，我们可以看到，每次找增广路时都是从某个顶点所连接的第一条边开始，那也就是说从顶点1中的第1条边接着去找没找到，从而遍历到顶点1中的第3条边，接着去找发现顶点2中的前三条边也没找到。。。这样下去直到找到终点。那么，我们可以知道下次dfs时，顶点1的前两条边没用（下次bfs或者几次bfs后可能会有用），直接从顶点1的第三条边开始去找。

当我们将当前图的所有增广路都找到后，再次bfs分层，当前图的层次会发生变化，然后我们在从顶点1开始去找，所以我们每次bfs，都要清一下数组cur。


修改代码风格 todo
```c
bool bfs(){ //给各个点分层
    //拷贝head
    int i;
    for(i=1;i<=n;i++) cur[i] = head[i];

    ....
}

// u 当前点,low u前面的路径上的最小容量
int dfs(int u,int low){
    if( u == t ) return low;
    int i;
    for(i=cur[u]; i !=-1;i=e[i].next){
        cur[u] = i;

        ...

    }
    
    return 0; //从u点到不了汇点
}

int dinic(){
    int tmp = 0,f;
    while( bfs()){ //分层
        while( f  = dfs(s,0x7f7f7f7f)){ //多次dfs,直到找不到路
            tmp +=f;
        }
    }
    return tmp;
}
```

题目地址：[luogu P3376 【模板】网络最大流](https://www.luogu.org/problemnew/show/P3376)

**代码:**

```c
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define maxn 10005
#define maxe 200005

int n,m,s,t;
int dep[maxn]; //分层,点i的层数


//向量星
struct _e {
    int u,v,next,cap;
};
_e e[maxe];
int head[maxn];
int cur[maxn]; //存当前边
int cnt = 0;

//边的编号从0开始
void addEdge(int u,int v,int cap){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].cap = cap;
    e[cnt].next = head[u];
    head[u] = cnt++;
}


//返回值表示是否能达到t点
bool bfs(){ //给各个点分层
    //拷贝head
    int i;
    for(i=1;i<=n;i++) cur[i] = head[i];

    memset(dep,-1,sizeof(dep)); //初始化
    queue<int> q;
    dep[s] = 1; //起点的 层
    q.push(s);
    
    while(q.empty() == false){
        int now = q.front(); q.pop();
        int i;
        for(i=head[now];i!=-1;i=e[i].next){
            int v = e[i].v;
            //v没有访问过 且 容量可通行
            if(dep[v] == -1 && e[i].cap >0){ 
                dep[v] = dep[now] +1;
                q.push(v);
            }
        }
    }

    return dep[t] != -1; // !=-1 表示能分层到汇点
}

// u 当前点,low u前面的路径上的最小容量
int dfs(int u,int low){
    if( u == t ) return low;
    int i;
    for(i=cur[u]; i !=-1;i=e[i].next){
        cur[u] = i;
        int v = e[i].v;
        // 是下一层的点 且 可通行
        if(dep[v] == dep[u]+1 && e[i].cap > 0){
            int flow = dfs(v,min(low,e[i].cap));
            if( flow > 0){ //从v开始可以走到汇点
                e[i].cap -=flow;    //同向容量 缩小
                e[i^1].cap += flow; //反向容量 加大
                return flow;        //回溯
            }

        }
    }
    
    return 0; //从u点到不了汇点
}

int dinic(){
    int tmp  = 0;
    while( bfs()){ //分层
        int f ; 
        while( f  = dfs(s,0x7f7f7f7f)){ //多次dfs,直到找不到路
            tmp +=f;
        }
    }
    return tmp;
}


int main(){
    
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);
    int t1,t2,t3;
    int i,j,k;
    memset(head,-1,sizeof(head));
    for (i=1;i<=m;i++){
        scanf("%d%d%d",&t1,&t2,&t3);
        addEdge(t1,t2,t3); //正向边
        addEdge(t2,t1,0);  //反向边
    }
    int maxflow =dinic();
    printf("%d\n",maxflow);
    return 0;
}
```


## 引用/资料

 - [Dinic算法详解及实现](https://www.cnblogs.com/LUO77/p/6115057.html)
