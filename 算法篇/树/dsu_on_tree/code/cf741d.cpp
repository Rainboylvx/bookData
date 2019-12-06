/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 11月 27日 星期三 08:35:06 CST
* problem:  codeforce-741d
*----------------*/
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 5e5+5;
int n;

int size[maxn],son[maxn];

int ans[maxn]; //每个子树的答案
int right_ans_23[25]; // [0]->[22]
int dis[maxn]; // 到1根的异或
int dep[maxn]; //每个点的深度
int max_sta_dep[(1<<23)]; // 每种状态下的最深dep的值
int max_ans;

//dfs序用
int dfn;
int ds[maxn],de[maxn];
int dfs_list[maxn];

#define get_len(u,v,lca) (dep[u]+max_sta_dep[v]-2*dep[lca])
/* ======= 全局变量 END =======*/

/* ================= 向量星 =================*/
int head[maxn];
int edge_cnt = 0;
struct _e{
    int u,v,w,next;
}e[maxn<<1];

void inline xlx_init(){
    edge_cnt = 0;
    memset(head,-1,sizeof(head));
}

void addEdge(int u,int v,int w){
    edge_cnt++;
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].w=w;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

/* 函数重载 */
void addEdge(int u,int v){
    edge_cnt++;
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}
/* ================= 向量星 end =================*/

void init(){
     xlx_init(); 
     scanf("%d",&n);
     int i,u;
     char c;
     for(i=1;i<=22;i++){
         right_ans_23[i]  = (1<<(i-1));
     }
     for(i=1;i<n;i++){
         scanf("%d %c",&u,&c);
         addEdge(u, i+1,c-'a');
         addEdge(i+1,u,c-'a');
     }
}
void dfs1(int u,int fa,int edge_char,int d){
    dep[u] = d+1; //点的深度
    dfs_list[++dfn] = u;
    ds[u] = dfn;
    if( fa != 0){
        dis[u] = dis[fa] ^ (1<<edge_char);
    }
    size[u] = 1;
    int i;
    for(i = head[u]; ~i ; i = e[i].next){
        int &v = e[i].v;
        if( v == fa) continue;
        dfs1(v,u,e[i].w,d+1);
        size[u] += size[v];
        if( size[son[u]] < size[v])
            son[u] = v;
    }
    de[u] = dfn;
}

int flag_hson;

int get_max_len(int u,int lca){
    int max_ans = 0;
    int o = dis[u] ^ 0;
    if( max_sta_dep[o])
        max_ans = max(max_ans, get_len(u, o, lca));
    int i;
    for(i=0;i<22;i++){
        o = dis[u] ^ (1<<i);
        if( max_sta_dep[o])
            max_ans = max(max_ans, get_len(u, o, lca));
    }

    return max_ans;
}

void dfs_count(int u,int fa){
    int i,j,k;
    ans[u] = max(ans[u],get_max_len(u, u));
    max_sta_dep[dis[u]] = max( max_sta_dep[dis[u]], dep[u]);

    // 遍历轻儿子 子树 上的点
    for(i = head[u]; ~i ; i = e[i].next){
        int &v = e[i].v;
        if( v == fa || v == flag_hson) continue;
        for( j = ds[v] ;j <= de[v];j++){
            int x = dfs_list[j];
            ans[u] = max(ans[u],get_max_len(x, u));
        }
        for( j = ds[v] ;j <= de[v];j++){
            int x = dfs_list[j];
            max_sta_dep[dis[x]] = max( max_sta_dep[dis[x]] , dep[x]);
        }
    }

}

// dsu on tree
void dsu(int u,int fa,bool keep){
    int i;
    //1. 递归 轻儿子
    for(i = head[u]; ~i ; i = e[i].next){
        int &v = e[i].v;
        if( v == son[u] || v == fa) continue;
        dsu(v,u,0);
        // 路径在子树上
        ans[u] = max(ans[u],ans[v]);
    }
    //2. 递归重儿子
    if( son[u]){
        dsu(son[u],u,1);
        ans[u] = max(ans[u],ans[son[u]]);
    }
    flag_hson = son[u];
    //3. 暴力u及轻儿子子树
    dfs_count(u, fa);
    flag_hson = 0;
    if( !keep){
        // 下面这样写会超时, 想想为为什么
        // memset(max_sta_dep,0,sizeof(max_sta_dep));
        for(i = ds[u];i <= de[u];i++){
            max_sta_dep[dis[dfs_list[i]]] = 0;
        }
        max_ans = 0;
    }
}

int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    init();
    dfs1(1,0,0,0);
    dsu(1, 0, 0);
    int i;
    for(i=1;i<=n;i++){
        printf("%d ",ans[i]);
    }

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
