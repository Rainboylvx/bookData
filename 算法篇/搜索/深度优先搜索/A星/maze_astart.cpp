#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;

int _map[maxn][maxn];
int n,m;
int sx,sy,tx,ty;

struct node {
    int x,y;
    int f,g; //h 通过计算得到

    friend bool operator<(const node &a,const node &b){
        //if( a.f == b.f){
            //if( a.x != b.x)
                //return a.x < b.x;
            //return a.y < b.y;
        //}
        return a.f > b.f;
    }
};
/* 8个方向 */
struct _fx { int x,y,val; };
_fx fx[] ={
    {-1,0,10},
    {1,0,10},
    {0,1,10},
    {0,-1,10},
    {1,-1,14},
    {1,1,14},
    {-1,1,14},
    {-1,-1,14}
};

priority_queue<node> open_list;
bool close_list[maxn][maxn] = { 0 };
node father[maxn][maxn];

void init(){
    scanf("%d%d",&n,&m);
    scanf("%d%d%d%d",&sx,&sy,&tx,&ty);

    memset(father,-1,sizeof(father)); //初始化

    int i,j;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%d",&_map[i][j]);
        }
    }
}

bool in_map(int x,int y){
    if( x >=1 && x <=n && y >= 1 && y <= m)
        return 1;
    return 0;
}

/* 特殊情况 不能走斜线 */
bool can_reach(int prex,int prey,int x,int y,int dir){
    if(dir <4) 
        return 1;
    int nx,ny;

    ny  = prey + fx[dir].y;
    if( _map[prex][ny] == 0 )
        return 0;

    ny = y - fx[dir].y;
    if( _map[x][ny] == 0)
        return 0;
    return 1;
}

/* (x,y) 到终点的曼哈顿距离 */
int manhattan_dis(int x,int y){
    return (abs(tx-x) + abs(ty-y) ) *10;
}

void print_close_list(){
    int i,j;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            printf("%d ",close_list[i][j]);
            //printf("%d ",father[i][j].f);
        }
        printf("\n");
    }
}


bool A_start(int x,int y){
    node start = { .x = sx, .y= sy, .f =0 ,.g =0 };
    open_list.push(start);

    while( !open_list.empty()){
        node u = open_list.top();
        open_list.pop();
        int &x = u.x, &y = u.y;
        if( x == tx && y == ty)
            return 1;

        /* 已经在 close_list 中,略过 */
        if( close_list[x][y] ) continue;

        close_list[x][y] = 1;

        int i;
        for(i=0;i<8;i++){
            int x = u.x + fx[i].x;
            int y = u.y + fx[i].y;

            if( !in_map(x,y) ||  close_list[x][y] || _map[x][y] == 0 || can_reach(u.x, u.y, x, y, i) == 0)
                continue;
            int g = u.g + fx[i].val;
            int h = manhattan_dis(x, y);
            open_list.push({.x = x,.y = y,.f=h+g,.g= g});

            /* 更新father */
            if(father[x][y].f == -1 ||  father[x][y].f > g+h){
                father[x][y] = {.x = u.x,.y = u.y,.f = g+h};
            }

        }
        //print_close_list();
        //printf("========================\n");
    }
    return 0;
}


int main(){
    init();
    bool ans = A_start(sx, sy);
    vector<node> path;

    int x=tx,y = ty;
    for( ; x != sx || y != sy ;){
        path.push_back({x,y});
        int xx = father[x][y].x;
        int yy = father[x][y].y;
        x = xx;
        y = yy;
    }
    path.push_back({sx,sy});
    
    reverse(path.begin(), path.end());
    path.pop_back();
    for (const auto& e : path) {
        printf("(%d,%d) ==> ",e.x,e.y);
    }
    printf("(%d,%d)",tx,ty);
    printf("\n");
    //print_close_list();
    int i,j;
    path.push_back({tx,ty});
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            bool flag = 0;
            for (const auto& e : path) {
                if( e.x == i && e.y == j){
                    flag = 1;
                    printf("1 ");
                }
            }
            if( !flag)
                printf("0 ");
        }
        printf("\n");
    }
    return 0;
}
