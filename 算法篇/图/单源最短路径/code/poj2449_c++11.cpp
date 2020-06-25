/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 01日 星期二 13:24:59 CST
* problem: poj-2249
*----------------*/
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

#define ee exp(1)
#define pi acos(-1)
#define mod 1000000007
#define inf7f 0x7f7f7f7f
#define inf3f 0x3f3f3f3f
#define inf in3f
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 1e3+5;
const int maxm = 1e5+5;

struct xlx{
    typedef struct  { int u,v,w,next;} node;
    int edge_cnt;
    vector<int> head;
    vector<node> e;

    /* 构造函数,点的数量 */
    xlx(int n){
        edge_cnt = 0;
        head = vector<int> (n,-1);
    }

    void add_edge(int u,int v,int w){
        e.push_back({.u = u ,.v = v ,.w = w ,.next = head[u]});
        head[u] = edge_cnt;
        edge_cnt++;
    }

    void add_edge(int u,int v){
        e.push_back({.u = u ,.v = v ,.w = 0 ,.next = head[u]});
        head[u] = edge_cnt;
        edge_cnt++;
    }

    template<class UnaryPredicate>
    void forEach(int u,UnaryPredicate p){
        int i;
        for(i = head[u];i!=-1;i = e[i].next){
            p(e[i].u,e[i].v,e[i].w);
        }
    }
};

int n,m;
int s,t,k;
xlx x1(maxn*2),x2(maxn*2);
int dis[maxn];


void init(){
    scanf("%d%d",&n,&m);
    int i;
    for(i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        x1.add_edge(u,v,w);
        x2.add_edge(v, u,w); // 反向存
    }
    scanf("%d%d%d",&s,&t,&k);
}

bool vis[maxn] = {0};
void dijkstra(int s){
    typedef pair<int,int> pairI;
    priority_queue<pairI, vector<pairI>, greater<pairI> > q;
    memset(dis,0x3f,sizeof(dis));
    /* memset(vis,0,sizeof(vis)); */
    dis[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty()){
        int now=q.top().second;
        q.pop();
        if(vis[now])continue;
        vis[now]=1;
        auto job =  [&q](int u,int v,int w){
            if( dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                q.push(make_pair(dis[v], v));
            }
        };
        x2.forEach(now,job);
    }
}

struct qnode{
    int v; ll w;
    qnode(int v,ll w):v(v),w(w){};
    friend bool operator< (const qnode &x, const qnode &y ){
        if( x.w+dis[x.v] > y.w+dis[y.v])
            return 1;
        return 0;
    }
};
ll astar_Kshort_path(){
    if( dis[s] == inf3f) return -1;
    priority_queue< qnode> q;
    q.push(qnode(s,0));

    if( s == t ) k++;

    int cnt = 0;
    while( !q.empty()){

        qnode h = q.top();
        q.pop();
        if( h.v == t){
            cnt++;
            if( cnt == k)
                return h.w;
        }

        auto job =[&q,&h](int u,int v,int w){
            q.push(qnode(v,w+h.w));
        };

        x1.forEach(h.v, job);
    }
    return -1;
}


int main(){
    init();
    dijkstra(t);
    ll ans = astar_Kshort_path();
    printf("%lld\n",ans);

    return 0;
}
