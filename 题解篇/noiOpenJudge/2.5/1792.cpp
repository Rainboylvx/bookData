#include <cstdio>
#include <cstring>
int n,m;
char g[105][105];
bool vis[105][105];
int fx[4][2] = {0,1,1,0,0,-1,-1,0};
int sx,sy,tx,ty;

bool in_map(int x,int y){
    return (x >=1 && x <=n && y >=1 && y <=n);
}

void init(){
    memset(g,0,sizeof(g));
    memset(vis,0,sizeof(vis));
    scanf("%d",&n);
    int i,j;
    for(i=1;i<=n;i++){
        scanf("%s",g[i]+1);
    }
    scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
    sx++;
    sy++;
    tx++;
    ty++;
}
bool dfs(int x,int y){
    if( x == tx && y == ty)
        return 1;
    vis[x][y] = 1;

    int i;
    for(i=0;i<4;i++){
        int nx = x +fx[i][0];
        int ny = y +fx[i][1];
        if( in_map(nx,ny) && g[nx][ny] !='#' && !vis[nx][ny]){
            if( dfs(nx,ny))
                return 1;
            //vis[nx][ny] = 0; 不要回溯
        }
    }
    return 0;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        init();
        /* 特判: 起点 终点 是不是 墙壁 */
        if(g[sx][sy] == '#' || g[tx][ty] == '#')
        {
            printf("NO\n");
            continue;
        }
        bool res = dfs(sx,sy);
        if( res)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
