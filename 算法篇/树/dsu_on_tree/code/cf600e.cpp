/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 11月 24日 星期日 14:14:50 CST
* problem:  codeforce-600e
*----------------*/

#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 1e5+5;
int n;
int size[maxn],son[maxn];// 子树结点数量,重儿子

long long ans[maxn];      // ans[i],以结点i为根的子树的答案
int color[maxn];    //每个点的颜色值
long long color_cnt[maxn]; //当前子树下的每个颜色的数量
long long max_color_cnt;  //数量最多的颜色是的数量
long long max_color_sum;  //数量最多的颜色的数量和
int flag_hson;
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
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&color[i]);
    }
    int u,v;
    for(i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v, u);
    }
}
// 与树链剖分找重儿子一样
void dfs1(int u,int f){
    size[u] = 1;
    int i;
    for(i = head[u]; ~i ; i = e[i].next){
        int v = e[i].v;
        if( v == f) continue;
        dfs1(v,u);
        size[u] += size[v];
        if( size[v] > size[son[u]])
            son[u] = v;
    }
}

void dfs_count(int u,int fa,int add){
    color_cnt[ color[u] ] += add; //颜色数量 +1/-1

    // 计算 max_color_sum
    if( color_cnt[ color[u] ] > max_color_cnt){
        max_color_cnt =  color_cnt[ color[u] ] ;
        max_color_sum = color[u];
    }
    else if ( color_cnt[ color[u] ] == max_color_cnt){
        max_color_sum += color[u];
    }

    int i;
    for(i = head[u]; ~i; i = e[i].next){
        int v = e[i].v;
        if( v == fa || v == flag_hson) continue;
        dfs_count(v, u, add);
    }
}

void dsu_on_tree(int u,int fa,bool keep){
    int i;
    // 1. 递归算轻儿子树
    for( i= head[u]; ~i; i = e[i].next){
        int v = e[i].v;
        if( v == fa || v == son[u]) continue;
        dsu_on_tree(v,u,false);
    }

    // 2. 递归算重儿子树
    if( son[u] ){
        dsu_on_tree(son[u], u, true);
        flag_hson = son[u];
    }
    // 3. 暴力统计u,和u的轻儿子子树的贡献
    dfs_count(u, fa, 1);
    flag_hson = 0;          //删除重儿子标记
    ans[u] = max_color_sum; //得到u结点子树的答案
    if( !keep ){
        // 从u回溯,删除子树上的所有点的贡献
        dfs_count(u, fa, -1);
        // 清空 必须放这里,想一想,只有重儿子的情况
        max_color_sum = max_color_cnt = 0;
    }
}

int main(){
    init();
    dfs1(1,0);
    dsu_on_tree(1,0,0);
    int i;
    for(i=1;i<=n;i++){
        printf("%lld ",ans[i]);
    }
    return 0;
}
