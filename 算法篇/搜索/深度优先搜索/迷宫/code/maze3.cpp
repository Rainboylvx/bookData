#include <cstdio>
#include <bits/stdc++.h>
using namespace std;

#define ms 100 //迷宫最大大小

int n; //迷宫大小
int cnt = 0; //记录结果数
int sx,sy,zx,zy;// 起点与终点
int fx[4][2] = {  {-1,0},{0,1},{1,0},{0,-1}};
int mg[ms][ms]; //存迷宫
bool visted[ms][ms] = {0};

struct node { int x,y; };
vector<node> sta;


//x,y是不是在迷宫内
bool in_mg(int x,int y){
    if(x <= n && x>=1 && y <=n && y >=1)
        return true;
    return false;
}

//调用了 dfs 相当于进入了x,y这个点
bool dfs(int x,int y){

    visted[x][y] =1; //设这个点走过
    sta.push_back({x,y});

    if(x == zx && y == zy) //表示已经到了终点
    {
        cnt++;
        printf("%d :",cnt); //输出这是第几个解

        for(int i=0;i<=sta.size()-2;++i){
            printf("{%d,%d}->",sta[i].x,sta[i].y);
        }

        //最后一点单独输出
        printf("{%d,%d}\n",sta.back().x,sta.back().y);
        return true;
    }

    int i;
    for(i=0;i<4;i++){
        
        int tx = x+fx[i][0];
        int ty = y+fx[i][1]; //tx,ty 下一个格子的坐标

        //判断tx,ty 是不是可以走的格子
        if( in_mg(tx,ty) && mg[tx][ty]!=1 && visted[tx][ty] !=1){ 
            dfs(tx,ty);
            visted[tx][ty] = 0; //回溯时,把这个点设为 未访问
                                //注意,这个时候你已经从tx,ty回到父亲结点,x,y了
            sta.pop_back();
        }

    }

    return false;
}

int main(){
    scanf("%d",&n);
    scanf("%d%d%d%d",&sx,&sy,&zx,&zy);
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            scanf("%d",&mg[i][j]);

    dfs(sx,sy);
    printf("total %d",cnt);
    return 0;
}
