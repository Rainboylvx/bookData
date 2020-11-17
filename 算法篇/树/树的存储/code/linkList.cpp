/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 11月 08日 星期日 16:16:54 CST */
#include <bits/stdc++.h>
using namespace std;

#ifndef DEBUG
#define debug(...)
#endif

const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量
int n,m,root;
int fa[maxn]; //记录每个点的父亲，父亲表示法

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }
    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }
    //下标访问
    edge& operator[](int i){ return e[i]; }
    //返回head[u]
    int operator()(int u){ return h[u]; }
} e;

void dfs(int u,int fa){
    printf("%d ",u);
    for(int i=e(u);~i;i=e[i].next){
        int &v = e[i].v;
        if( v == fa) continue;
        dfs(v, u);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        e.add2(u, v); //添加边，存两遍
        fa[v] = u;
    }
    root = 1;
    while( fa[root] != 0) root =fa[root];

    dfs(root,0);

    return 0;
}
