/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 01月 16日 星期六 22:50:26 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
int s,t;

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){	//构造函数
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
} e;

const int inf = 0x7f7f7f7f;

struct Dijkstra {
    int dis[maxn];
    bool vis[maxn];
    Dijkstra(){ //格构函数
        memset(dis,0x7f,sizeof(dis)); //所有的点都是0x7f7f7f7f 代表无穷大
        memset(vis,0,sizeof(vis));    //所有点都是没有标记的
        //注意这里起点也未标记的
    }

    void work(int s){
        dis[s] = 0; 
        for(int i=1;i<=n;++i){ //进行ｎ次循环，每次标记一个点

            int m = inf,u = -1;//记录最小值，与对应的点
            for(int j =1;j<=n;++j){
                //未标记与 >最小值
                if( vis[j] == 0 && m > dis[j])
                    u = j,m = dis[j];
            }
            if( u == -1)//证明m没有被更新
                return; //也就是有可能还存在末标记点
                        //但是它的值是无穷，证明从起点到达不了这个点
                        //那就不要再进行算法了
            vis[u] = 1; //标记这个点
            
            //用新标记的点去更新它周围的末标记点
            for(int j=e.h[u];~j;j=e[j].next){
                int &v = e[j].v, &w = e[j].w;
                if( vis[v] == 0 && dis[v] > dis[u]+w)
                    dis[v] = dis[u] + w;
            }
        }
    }
} dijkstra;

int main(){
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);
    for(int i=1;i<=m;++i){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        e.add2(u, v,w);
    }
    dijkstra.work(s);
    printf("%d",dijkstra.dis[t]);

    return 0;
}
