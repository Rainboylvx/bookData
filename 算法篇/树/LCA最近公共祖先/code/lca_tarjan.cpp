/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 11月 24日 星期二 15:32:47 CST */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量
int n,m;

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
    edge& operator[](int i){
        return e[i];
    }
} e,query;

/* ================= 并查集 =================*/
struct UnionFind {
    int fa[maxn];
    UnionFind(int len = maxn){
        for(int i=1;i<=len;++i) fa[i] =i;
    }

    int find(int u){
        if ( u==fa[u]) return u;
        return fa[u] = find(fa[u]);
    }

    inline void un(int u,int v){
        fa[find(u)] = find(v);
    }
} uset;


struct tarjan {
    bool vis[maxn];
    int  ans[maxn];

    void dfs(int u,int f){
        for(int i=e.h[u];~i;i=e[i].next){
            int &v = e[i].v, &w = e[i].w;
            if( v == f) continue;
            dfs(v,u);
            uset.un(v,u);
        }
        vis[u] = 1; //即将退出时设已访问，注意这求lca(6,6)的这种情况
        for(int i=query.h[u];~i;i=query[i].next){
            int &v = query[i].v, &w = query[i].w;
            if(vis[v]) 
                ans[w] = uset.find(v);
        }
    }

    inline void operator()(){
        dfs(1,0); //dfs(root,root);
    }
} tar;


void init(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        e.add2(u,v);
    }
    for(int i=1;i<=m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        query.add2(u,v,i); //记录所有的询问,w代表第几个询问
                            //离线
    }
}

int main(){
    init();
    tar();
    for(int i =1;i<=m;i++){
        printf("%d\n",tar.ans[i]);
    }
    return 0;
}
