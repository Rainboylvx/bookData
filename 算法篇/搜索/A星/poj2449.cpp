/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 01日 星期二 13:24:59 CST
* problem: poj-2249
*----------------*/
#include <queue>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
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
const int maxm = 500005;
int dis[maxn];
bool vis[maxn];
int n,m;
int s,t,k;


/* ================= 向量星 =================*/
int head[maxn];
int head2[maxn];
int edge_cnt = 0;
int edge_cnt2 = 0;
struct _e{
    int u,v,w,next;
}e[maxm],e2[maxm];

void inline xlx_init(){
    edge_cnt = 0;
    edge_cnt2 = 0;
    memset(head,-1,sizeof(head));
    memset(head2,-1,sizeof(head2));
}

void addEdge(int u,int v,int w){
    edge_cnt++;
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].w=w;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

void addEdge2(int u,int v,int w){
    edge_cnt2++;
    e2[edge_cnt].u = u;
    e2[edge_cnt].v= v;
    e2[edge_cnt].w=w;
    e2[edge_cnt].next = head2[u];
    head2[u] = edge_cnt2;
}
/* ================= 向量星 end =================*/

void dijkstra(int s){
    typedef pair<int,int> pairI;
    priority_queue<pairI, vector<pairI>, greater<pairI> > q;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis)); 
    dis[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty()){
        int now=q.top().second;
        q.pop();
        if(vis[now])continue;
        vis[now]=1;
        for(int i=head2[now];i!=-1;i=e2[i].next){
            if(dis[e2[i].v]>dis[now]+e2[i].w){
                dis[e2[i].v]=dis[now]+e2[i].w;
                q.push(make_pair(dis[e2[i].v],e2[i].v));
            }
        }
    }
}

void spfa(int src)
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis, 0, sizeof(vis)); 
    vis[src] = 1;
    queue<int> q;

    q.push(src);
    dis[src] = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        int i;
        for(int i=head2[u];i!=-1;i=e2[i].next){
            {
                int v = e2[i].v;
                int w = e2[i].w;
                if(dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    if(!vis[v])
                    {
                        q.push(v);
                        vis[v] = 1;
                    }
                }
            }
        }
    }
}

void init(){
    xlx_init();
    int i;
    for(i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge2(v,u,w);
    }
    scanf("%d%d%d",&s,&t,&k);
}

struct qnode {
    int v,w;
    qnode(int v,int w):v(v),w(w){}
    bool operator<(const qnode &b)const  {
        return w+dis[v] > b.w+dis[b.v];
    }

};

int astar_Kshort_path(int s,int t){
    int cnt = 0;
    priority_queue<qnode> q;
    if( s == t){
        k++;
    }

    q.push(qnode(s,0));
    while(!q.empty()){

        qnode h = q.top();
        q.pop();

        int now = h.v;
        if( now ==t){
            cnt++;
            if( cnt == k ) return h.w;
        }
    
        int i;
        for(i = head[now]; i!= -1;i = e[i].next){
            int &v = e[i].v;
            int &w = e[i].w;
            q.push(qnode(v,w+h.w));
        }

    }

    return -1;
}
int main(){
    while(scanf("%d%d",&n,&m) != EOF){
        init();
        //dijkstra(t);
        spfa(t);
        if( dis[s] == inf3f)
            printf("%d\n",-1);
        else{
            int ans = astar_Kshort_path(s,t);
            printf("%d\n",ans);
        }
    }
    return 0;
}
