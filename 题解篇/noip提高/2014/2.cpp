/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 08月 11日 星期日 15:05:17 GMT
* problem:  luogu-1351
*----------------*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e6+5;
int n;
#define mod 10007


ll a[maxn];
ll sum[maxn] = {0}; //距离这个点距离为1的数字和.
bool vis[maxn] = {0};
int _max_ = -1;
ll ans_sum = 0;

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
    int i,t1,t2;
    for (i=1;i<n;i++){
        scanf("%d%d",&t1,&t2);
        addEdge(t1,t2);
        addEdge(t2, t1);
    }
    for (i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
}

void get_max_2(int x[],int val){
    x[2] = val;
    int i;
    for(i=2;i>=1;i--){
        if( x[i] > x[i-1]){
            swap( x[i],x[i-1]);
        }
    }
}

void dfs(int u,int fa_val){
    vis[u] = 1;
    int i;
    int max_2[3] = {0};
    ll sum = 0; //孩子的和
    ll sum2 = 0; //孩子平方和
    for(i = head[u];i != -1 ;i= e[i].next){
        int v = e[i].v;
        if(  !vis[v]  ){
            get_max_2(max_2,a[v]);
            dfs(v,a[u]);
            sum += a[v];
            sum2 += a[v]*a[v];
        }
    }
    _max_ = max(_max_,max_2[0] * max_2[1]);
    _max_ = max(_max_,max_2[0] * fa_val);

    ans_sum =  (ans_sum +((sum * sum - sum2)%mod + fa_val*sum*2 % mod ) )% mod;
}


int main(){
    init();
    dfs(1,0);
    printf("%d %lld",_max_,ans_sum);
    return 0;
}
