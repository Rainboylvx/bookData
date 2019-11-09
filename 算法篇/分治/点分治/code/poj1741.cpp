#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int read(){ int x=0,f=1;char ch=getchar(); while(ch<'0'||ch>'9') ch=getchar(); while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x; }

const int maxn = 1e4+5;
int n,k;
bool del[maxn]; // 点,删除标记
int size[maxn]; // 子树的大小
int f[maxn]; // 最大孩子
int ans; // 答案记录
int tot;  // n - 删除的结点
int root; //重心
int dis[maxn];  //到根的距离


/* ================= 向量星 =================*/
int head[maxn];
int edge_cnt = 0;
struct _e{
    int v,w,next;
}e[maxn<<1];

void inline addEdge(int u,int v,int w){
    edge_cnt++;
    e[edge_cnt].v= v;
    e[edge_cnt].w=w;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}
/* ================= 向量星 end =================*/

void inline init(){ //初始化
    memset(head,0,sizeof(head));
    memset(del,0,sizeof(del));
    edge_cnt = root = ans = 0;
    f[0] = 0x7fffffff;
    tot = n;
    int i,u,v,w;
    for(i=1;i<n;i++){ //建图
        u = read(), v = read(), w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
}

/* 得到重心 */
void get_root(int u,int fa){
    size[u] = 1; f[u] = 0;
    int i;
    for(i= head[u]; i ;i= e[i].next){
        int v = e[i].v;
        if( v == fa || del[v]) continue;
        get_root(v, u);
        size[u] += size[v];
        f[u] = max(f[u],size[v]);
    }
    f[u] = max(f[u],tot - size[u]);
    if( f[u] < f[root]) root = u;
}

/* 得到每个点的深度 */
int dep[maxn];
void get_dep(int u,int fa){
    dep[ ++dep[0] ] = dis[u];
    int i;
    for(i = head[u];i ;i=e[i].next){
        int v = e[i].v;
        if( v == fa || del[v]) continue;
        dis[v] = dis[u]+e[i].w;
        get_dep(v, u);
    }
}

/* 计算 有几对*/
int calc(int u,int len ){
    dis[u] = len;
    dep[0] = 0; //清空
    get_dep(u, 0);
    sort(dep+1,dep+1+dep[0]);
    int cnt = 0, l = 1 ,r = dep[0];
    while( l < r){
        if( dep[l]+dep[r] <= k){
            cnt+= r-l; l++;
        }
        else r--;
    }
    return cnt;
}

/* 计算答案 */
void work(int u){
    ans += calc(u,0);
    del[u] = 1;
    int i;
    for(i = head[u];i ;i = e[i].next){
        int v = e[i].v;
        if( del[v] ) continue;
        ans -= calc(v, e[i].w);
        tot = size[v];
        root = 0;
        get_root(v, 0);
        work(root);
    }
}

int main(){
    while(1){
        n = read(),k = read();
        if( !n && !k ) break;
        init();
        get_root(1, 0);
        work(root);
        printf("%d\n",ans);
    }
    return 0;
}



