/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 02日 星期三 14:44:38 CST
* problem:  hdu-2757
*----------------*/
#include <bits/stdc++.h>
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
const int maxm = 1e6+5;

int r,c;
int n;
char lake[maxn][maxn];
bool vis[maxn][maxn];
int rs,cs,rd,cd;

int fx[][2] = {
    {-1,0}, // 0
    {-1,1}, // 1
    {0,1}, // 2
    {1,1}, // 3
    {1,0}, // 4
    {1,-1}, // 5
    {0,-1}, // 6
    {-1,-1}, // 7
};

bool in_map(int x,int y){
    if( x >= 1 && x <= r && y >=1 && y <= c)
        return 1;
    return 0;
}


void init(){
    int i,j;
    for(i=1;i<=r;i++){
        scanf("%s",lake[i]+1);
    }
    scanf("%d",&n);
}


int _01bfs(){
    memset(vis,0,sizeof(vis));
    typedef struct {
        int x,y,step;
    } node;
    deque<node> q;
    q.push_back({rs,cs,0});

    while( !q.empty()){
        node h = q.front();
        q.pop_front();
        if( vis[h.x][h.y])
            continue;
        vis[h.x][h.y] = 1;


        if( h.x == rd && h.y == cd){
            return h.step;
        }

        int i;
        for(i=0;i<8;i++){
            int nx = h.x + fx[i][0];
            int ny = h.y + fx[i][1];
            if( in_map(nx,ny) && !vis[nx][ny]){
                if((lake[h.x][h.y]-'0') != i)
                    q.push_back({nx,ny,h.step+1});
                else
                    q.push_front({nx,ny,h.step});
            }
        }
    }

    return 0;
}


int main(){
    while (scanf("%d%d",&r,&c) !=EOF) {
        init();
        int i;
        for(i=1;i<=n;i++){
            scanf("%d%d%d%d",&rs,&cs,&rd,&cd);
            if( rs == rd && cs == cd){
                printf("0\n");
                continue;
            }
            int ans = _01bfs();
            printf("%d\n",ans);
        }
    }
    return 0;
}
