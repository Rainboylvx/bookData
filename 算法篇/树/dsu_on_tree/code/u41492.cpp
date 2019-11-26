/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 11月 27日 星期三 01:19:41 CST
* problem:  luogu-u42492
*----------------*/
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 1e5+5;
int n,m;
int color[maxn]; //每个点的颜色
bool col_ext[maxn]; //每个颜色是否出现过
int sum_color_cnt; //颜色的数量和
int ans[maxn];   //每个子树的答案

int size[maxn],son[maxn]; //重儿子

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
     int i,u,v;
     for(i=1;i<n;i++){
         scanf("%d%d",&u,&v);
         addEdge(u, v);
         addEdge(v, u);
     }
     for(i=1;i<=n;i++){
         scanf("%d",&color[i]);
     }
}

// 更新 size[i],son[i]
void dfs1(int u,int fa){
    int i;
    size[u] = 1;
    for(i = head[u]; ~i ; i = e[i].next){
        int &v = e[i].v;
        if( v == fa ) continue;
        dfs1(v,u);
        size[u] += size[v];
        if( size[ son[u] ] < size[v])
            son[u] = v;
    }
}

int flag_hson;
/* 暴力计算 */
// val 0/1 是否把信息贡献上
void dfs_count(int u,int fa,int val){
    int col = color[u];
    if(col_ext[col] == 0) //原来这个颜色不存在
        sum_color_cnt += 1;

    if( !col_ext[col]){
        col_ext[col] += val;
    }

    int i;
    for(i = head[u]; ~i ; i = e[i].next){
        int &v = e[i].v;
        if( v == fa || v == flag_hson) continue;
        dfs_count(v, u, val);
    }
}

void dsu_on_tree(int u,int fa,bool keep){
    //1. 先递归轻儿子
    int i;
    for(i = head[u]; ~i ; i = e[i].next){
        int &v = e[i].v;
        if( v == fa || v == son[u]) continue;
        dsu_on_tree(v,u,false);
    }
    //2. 递归重儿子
    if( son[u])
        dsu_on_tree(son[u],u,true);
    flag_hson = son[u];
    //3. 暴力统计
    dfs_count(u, fa,1);
    ans[u] = sum_color_cnt;
    flag_hson = 0;
    if( !keep){
        memset(col_ext,0,sizeof(col_ext));
        sum_color_cnt = 0;
    }
}

int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    init();
    dfs1(1,0);
    dsu_on_tree(1,0,0);
    scanf("%d",&m);
    int i,t;
    for(i=1;i<=m;i++){
        scanf("%d",&t);
        printf("%d\n",ans[t]);
    }

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
