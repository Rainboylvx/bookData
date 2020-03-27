#include <bits/stdc++.h>
#define For(i,start,end) for(i = start ;i <= end; ++i)
#define Rof(i,start,end) for(i = start ;i >= end; --i)
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 1e5+5;
const int maxe = 1e6+5;
int n,m;
int dfn[maxn],low[maxn];
int idx,bcc_cnt;
stack<int> sta; //栈,存边的编号

//点的颜色,就是点属于哪个bcc
//防止bbc含有一个点多次
int color[maxn]; 
vector<int> bcc[maxn];//属于某个bcc的点有哪些

/* ========= 向量星 1 =========*/
namespace xlx1 {
    int head[maxn],edge_cnt = 0;
    struct _e{ int u,v,w,next; }e[maxe];
    void inline init(){ edge_cnt = 0; memset(head,-1,sizeof(head)); } 
    void addEdge(int u,int v,int w=0){ e[++edge_cnt] = { .u = u,.v=v,.w=w,.next =head[u]}; head[u] = edge_cnt; }
}
/* ========= 向量星 1 END =========*/

/* ======= 全局变量 END =======*/
void init(){
     xlx1::init(); 
     scanf("%d%d",&n,&m);
     int i,u,v;
     For(i,1,m){
         scanf("%d%d",&u,&v);
         xlx1::addEdge(u, v);
        xlx1::addEdge(v, u);
     }

}

void tarjan(int u){
    dfn[u]=low[u] = ++idx;
    int i;
    for(int i=xlx1::head[u];~i;i=xlx1::e[i].next){
        int v=  xlx1::e[i].v;
        if( !dfn[v]){ //没有访问过
            sta.push(i); //存边入栈
            tarjan(v);
            low[u] = min(low[u],low[v]);
            //!!!!注意:
            //这里没有判断u!=root
            if( low[v] >=dfn[u]){
                bcc_cnt++;
                while(1){
                    int i = sta.top(); sta.pop();
                    int uu = xlx1::e[i].u,vv = xlx1::e[i].v;
                    if(color[uu] != bcc_cnt){
                        bcc[bcc_cnt].push_back(uu);
                        color[uu] = bcc_cnt;
                    }
                    if(color[vv] != bcc_cnt){
                        bcc[bcc_cnt].push_back(vv);
                        color[vv] = bcc_cnt;
                    }
                    if( uu == u && vv == v) break;
                }
            }
        }
        else low[u] = min(low[u],dfn[v]);
    }

}
void find_bcc(){

}

int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    init();
    root=1;
    tarjan(1);
    printf("%d\n",bcc_cnt);
    int i;
    For(i,1,bcc_cnt){
        printf("bcc %d: ",i);
        for (const auto& e : bcc[i]) {
            printf("%d ",e);
        }
        printf("\n");
    }

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
