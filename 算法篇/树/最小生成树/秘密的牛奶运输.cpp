/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 09月 13日 星期五 13:07:04 CST
* problem: slimeoj-1490
*----------------*/
#include <bits/stdc++.h>
using namespace std;

int n,m;
#define maxn 505
#define maxm 10005
const long long INF = 0x7fffffffffffffff;
long long  second_min_ans = INF;
int maxd[maxn][maxn]; // 最小生成树上的i->j两点的最大值
vector<int> G[maxn]; // G[i] 并查集和 和 点i想连的点

/* ================= 向量星 =================*/
int head[maxn];
int edge_cnt = 0;
struct _e{
    long long u,v,w,vis;
    bool operator<(const _e &b){
        if( w == b.w){
            if( u == b.u)
                return v < b.v;
            return u < b.u;
        }
        return  w < b.w;
    }
    bool operator==(const _e &b){
        if( w == b.w && b.v == v && u == b.u)
            return 1;
        return 0;
    }
}e[maxm<<1];

/* 函数重载 */
void addEdge(int u,int v,int w){
    edge_cnt++;
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].w= w;
}
/* ================= 向量星 end =================*/


/* ================= 并查集 =================*/
int fa_bcj[maxn];

inline void bcj_init(int x){ //并查集 初始化
    int i;
    for(i=1;i<=x;i++) fa_bcj[i] = i;
}
int find(int x){ //查找 and 压缩
    if( x == fa_bcj[x]) return x;
    fa_bcj[x] = find(fa_bcj[x]);
    return fa_bcj[x];
}

void bcj_union(int x,int y){
    int fx = find(x);
    int fy = find(y);
    fa_bcj[fx] = fy;
}
/* ================= 并查集 end =================*/


//============== kruskal算法
int kruskal(){ //
    long long  ans = 0;
    int i,j;
    int k=0 ;
    for(i=1;i<=n;i++) {
        fa_bcj[i] = i; //并查集初始化
        G[i].push_back(i);
    }

    for(i=1;i<=m;i++){
        int f1 = find(e[i].u);
        int f2 = find(e[i].v);
        if( f1 != f2){
            ans += e[i].w;
            fa_bcj[f1] = f2;
            e[i].vis = 1; // 这条边在 MST 上

            /* 求maxd*/
            long long &u = e[i].u,&v = e[i].v,&w = e[i].w;

            for( auto x1 : G[f1]){
                for( auto x2 : G[f2]){
                    maxd[x1][x2] = maxd[x2][x1] = w;
                }
            }
            for( auto x1 : G[f1]){
                G[f2].push_back(x1);
            }

            k++;
            if( k == n-1) break; //选n-1条边
        }
    }
    if( k < n-1)
        return -1; //返回不可能
    else {
        //printf("%d\n",ans);
        for( i =1;i<=m;i++)
            if( !e[i].vis){
                long long  t = ans+e[i].w - maxd[e[i].u][e[i].v];
                if( t > ans)
                    second_min_ans = min( second_min_ans,t);
            }
        return second_min_ans;
    }
}
//============== kruskal算法 END

void init(){
    scanf("%d%d",&n,&m);
    int i,j;
    long long u,v,w;
    for (i=1;i<=m;i++){
        scanf("%lld%lld%lld",&u,&v,&w);
        addEdge(u, v,w);
    }
    sort(e+1,e+m+1);
    /* 需要去重边 */
    m = unique(e+1,e+m+1)-(e+1);
}


int main(){
    init();
    //printf("%d\n",m);
    /* 求出最小生成树 */
    kruskal();
    printf("%lld\n",second_min_ans);

    return 0;
}
