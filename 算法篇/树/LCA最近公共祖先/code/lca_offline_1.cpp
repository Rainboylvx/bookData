/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 11月 23日 星期一 17:23:17 CST */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量
int n,m;

//链式前向星存树
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
        add(u,v,w); add(v,u,w);
    }
    edge& operator[](int i) {
        return e[i];
    }
} e;

struct Lca {
    int N,d[maxn],f[maxn][50]; //f[i][j] i点的2^j祖先

    // 初始化，算出的理论跳的最远可能，与f[][]
    inline void init(){
        for(N=0; (1<<(N+1)) < n ;N++);
        dfs(1,0,1);
    }

    //树上的遍历来求 f[][] 与d[]每个点的深度
    void dfs(int u,int fa,int dep){
        d[u] = dep;
        f[u][0] = fa;
        // 显示u点到root路径上的点都已经求出来f[][]
        for(int j=1;j<=N;++j) f[u][j] = f[ f[u][j-1] ][j-1];
        for(int i=e.h[u];~i;i=e[i].next){
            int &v = e[i].v;
            if( v == fa) continue; //是父亲 就什么也不做
            dfs(v,u,dep+1);
        }
    }

    //重载(),找到两个点的lca
    int operator()(int a,int b){
        if( d[a] > d[b]) swap(a,b); //保证b是深的点
        for(int i=N;i>=0;--i){ // b 跳到和a一样深
            if( d[ f[b][i] ] >= d[a]) // a深度以下是可行区域,包括a
                b = f[b][i];
        }
        if( a == b) return a; //在同一条链上

        for(int i=N;i>=0;--i){ // 同时跳
            if( f[a][i] != f[b][i] ){ //不相同就跳
                a = f[a][i];
                b = f[b][i];
            }
        }
        return f[a][0]; //返回停下来时候的父亲，就是lca
    }

} lca;

void init(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        e.add2(u,v);
    }
    lca.init();     //初始化
}

int main(){
    init();
    for(int i=1;i<=m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        printf("%d\n",lca(u,v));
    }
    return 0;
}
