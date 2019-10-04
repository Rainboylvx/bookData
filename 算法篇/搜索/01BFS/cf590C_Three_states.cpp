/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 03日 星期四 10:27:41 CST
* problem: codeforces-590c
*----------------*/
#include <bits/stdc++.h>
using namespace std;
#define ee exp(1)
#define pi acos(-1)
#define mod 1000000007
#define inf7f 0x7f7f7f7f
#define inf3f 0x3f3f3f3f
#define inf inf3f
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 1e3+5;
const int maxm = 1e6+5;

/* dis[k][i][j] state k 到点(i,j)的最短距离 */
int dis[3][maxn][maxn];


int n,m;
char _map[maxn][maxn];
bool vis[maxn][maxn];
int xy[4][2];

class fx {
    int fx4[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
    int fx8[8][2] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
    
    template<class UnaryPredicate>
        void forEach(int fx[][2],int len,int sx,int sy,UnaryPredicate p){
            int i;
            for(i=0;i<len;i++){
                p(fx[i][0]+sx,fx[i][1]+sy);
            }
        }
    public:
    /* 遍历u周围的点 */
    template<class UnaryPredicate>
        void forEach_fx4(int sx,int sy,UnaryPredicate p){
            forEach(fx4, 4, sx,sy,p);
        }

    template<class UnaryPredicate>
        void forEach_fx8(int sx,int sy,UnaryPredicate p){
            forEach(fx8, 8, sx,sy,p);
        }
};

fx _fx;

/* 仿函数 */
struct in_map {
    int min_x,max_x,min_y,max_y;

    in_map(){ min_x=max_x=min_y=max_y=0;}
    in_map( int x0, int y0,int x1, int y1 ): min_x(x0),max_x(x1),min_y(y0),max_y(y1){}

    /* 设置边界*/
    void set( int x0,int y0, int x1,  int y1 ){
        min_x = x0 , max_x = x1 ,min_y = y0 ,max_y = y1;
    }

    bool operator()(int x,int y){
        if( x >= min_x && x<=max_x && y >= min_y && y <=max_y)
            return 1;
        return 0;
    }
};
 

void _01bfs(int state,int sx,int sy){
    /* 清空标记 */
    memset(vis,0,sizeof(vis));
    typedef struct { int x,y,step; } node;
    deque<node> q;
    q.push_back({sx,sy,0}); //加入起点

    in_map isIn(1,1,n,m);

    while( !q.empty()){
        node h = q.front();
        q.pop_front();
        if( vis[h.x][h.y])
            continue;
        vis[h.x][h.y] = 1; //标记

        dis[state][h.x][h.y] = h.step;

        auto job  = [&](int x,int y){
            if( isIn(x,y) && !vis[x][y] && _map[x][y] != '#'){
                //#ifdef DEBUG
                    //printf("(%d,%d) %c\n",x,y,_map[x][y]);
                //#endif

                if(_map[x][y] >='1'&&_map[x][y] <='3')
                    q.push_front({x,y,h.step});
                else
                    q.push_back({x,y,h.step+1});
            }
        };
        _fx.forEach_fx4(h.x, h.y, job);
    }
}


void init(){
    scanf("%d%d",&n,&m);
    memset(dis,0x1f,sizeof(dis));
    int i,j;
    for(i=1;i<=n;i++){
        scanf("%s",_map[i]+1);
        for(j=1;j<=m;j++){
            if( _map[i][j] >='1' && _map[i][j] <='3'){
                char &c = _map[i][j];
                xy[c-'1' ][0] = i;
                xy[c-'1' ][1] = j;
            }
        }

    }
}

int main(){
    init();

    _01bfs(0,xy[0][0],xy[0][1]);
    _01bfs(1,xy[1][0],xy[1][1]);
    _01bfs(2,xy[2][0],xy[2][1]);

    /* 遍历 */
    int i,j;
    int ans=0x1f1f1f1f;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            int f = 0;
            if( _map[i][j] == '.') f = 2;
            ans = min(ans, dis[0][i][j] + dis[1][i][j] + dis[2][i][j] -f);
        }
    }
    if( ans == 0x1f1f1f1f)
        printf("-1");
    else
        printf("%d\n",ans);
    return 0;
}
