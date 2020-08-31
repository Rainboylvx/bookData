/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 12月 11日 星期三 08:42:40 CST
* problem:  luogu-2324
*----------------*/
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
int dst[6][6] = {
    0,0,0,0,0,0,
    0,1,1,1,1,1,
    0,0,1,1,1,1,
    0,0,0,2,1,1,
    0,0,0,0,0,1,
    0,0,0,0,0,0
};
int state[6][6],x,y;
/* ======= 全局变量 END =======*/
int fx[8][2] = { 1,2,1,-2,-1,2,-1,-2,2,1,2,-1,-2,-1,-2,1};

bool in_map(int x,int y){
    if( x >= 1 && x <= 5 && y >=1 && y<=5)
        return 1;
    return 0;
}
/* 检查当前状态,到dst的步数*/
int need_step(){
    int i,j,cnt = 0;
    for(i=1;i<=5;i++){
        for(j=1;j<=5;j++){
            if( dst[i][j] != state[i][j])
                cnt++;
        }
    }
    return cnt;
}

void init(){
    int i,j;
    char str[10];
    for(i=1;i<=5;i++){
        scanf("%s",str+1);
        for(j=1;j<=5;j++){
            state[i][j] = str[j] == '*' ? 2 : str[j]- '0';
            if( str[j] == '*')
                x = i, y = j;
        }
    }
}

void p_state(){
    int i,j;
    for(i=1;i<=5;i++){
        for(j=1;j<=5;j++){
            printf("%d",state[i][j]);
        }
        printf("\n");
    }
}

bool iddfs(int maxd,int d,int x,int y){
    //printf("=========\n");
    //p_state();
    //printf("=========\n");
    if(d > maxd) {
        if( need_step() == 0 ) return 1;
        return 0;
    }
    
    int i;
    for(i=0;i<8;i++){
        int nx = x + fx[i][0];
        int ny = y + fx[i][1];
        int ii,jj;
        if( !in_map(nx, ny) ) continue;
        swap(state[nx][ny], state[x][y]);
        int s  = need_step();
        if( s + d <= maxd+1 )
            if( iddfs(maxd, d+1,nx,ny) )return 1;
        //交换回来
        swap(state[x][y],state[nx][ny]);
    }
    return 0;
}

void work(){
    int i;
    if( need_step() == 0) { printf("0\n"); return ; }
    for(i=1;i<=15;i++){
        if( iddfs(i,1,x,y)) {
            printf("%d\n",i);
            return ;
        }
    }
    printf("%d\n",-1);
}

int main(){
    //===================
    int t;
    scanf("%d",&t);
    while (t--) {
        init();
        work();
    }

    return 0;
}
