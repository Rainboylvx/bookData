//version 1
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 1e3+5;
int n,m;
int _map[maxn][maxn]={0}; //存图
/* ======= 全局变量 END =======*/

int bstb = 0; //下界
int node_set[maxn]; //那些结点选了

/* u点和前面一选的的点,都相连 */
bool all_connect(int u){
    int i;
    for(i=1;i<u;i++){
        if( node_set[i]  && _map[u][i]!=1)
            return 0;
    }
    return 1;
}


//dep 深度, sum 前面选了多少点,F 期望,上界
void dfs(int dep,int sum,int F){
    if( F <= bstb) // 上界 <= 下界
        return;

    /* 选这个点 */
    if( all_connect(dep)){
        node_set[dep] = 1;
        bstb = max(bstb,sum+1);
        dfs(dep+1,sum+1,F);
        node_set[dep] = 0;
    }

    /* 不选这个点 */
    if( F-1 > bstb){ // 上界-1 > 下界
        dfs(dep+1,sum,F-1);
    }
}



void init(){
     scanf("%d%d",&n,&m);
     int u,v;
     int i;
     for(i=1;i<=m;i++){ //读图
         scanf("%d%d",&u,&v);
         _map[u][v]  = _map[v][u] =1;
     }
}


int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    init();
    dfs(1,0,n);
    printf("%d\n",bstb);

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
