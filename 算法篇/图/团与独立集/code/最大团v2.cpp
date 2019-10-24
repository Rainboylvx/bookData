//version2
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 1e3+5;
int n,m;
int _map[maxn][maxn];
int dp[maxn];
int con_sta[maxn]; // 剩下的点是否和已经选的点连接

int bstb = 0; //下界

void init(){
    scanf("%d%d",&n,&m);
    int i,u,v;
    for(i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        _map[u][v] = _map[v][u] = 1;
    }
}
/* ======= 全局变量 END =======*/



void dfs(int u,int sum){
    //更新下界
    if( sum > bstb)  bstb = sum; 
    int able = 0;
    int i,j;

    //只能放到dfs里
    int con_sta_bak[maxn]; // 剩下的点是否和已经选的点连接
    for(i=u+1;i<=n;i++){
        //保留上一层的状态
        con_sta_bak[i] = con_sta[i]; 
        if( con_sta[i]) able++;
    }
    if( able + sum <= bstb) return;
    for(i=u+1;i<=n;i++){
        //
        if( !con_sta_bak[i]) continue;
        //
        if(dp[i] + sum <= bstb) continue;

        for(j=i+1;j<=n;j++){
            //下一层的状态
            con_sta[j] = con_sta_bak[j] & _map[i][j];
        }
        dfs(i,sum+1);
    }
}

int max_tuan(){
    bstb = dp[n] = 1;
    int i,j;
    for(i=n-1;i>=1;i--){ // 倒过来
        
        //[i+1,n]中的和 i 的连接状态
        for(j=i+1;j<=n;j++){
            con_sta[j] = _map[i][j];
        }
        dfs(i,1);
        dp[i] = bstb;
    }
    return bstb;
}


int main(){
    init();
    int ans = max_tuan();
    printf("%d\n",ans);

    return 0;
}
