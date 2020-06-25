---
title: Flip Game
date: 2019-02-28 11:00
update: 2019-02-28 11:00
author: Rainboy
---

## 题目地址

  - [poj 1753 Flip Game](https://vjudge.net/problem/POJ-1753#author=zmyhh)

题目大意:

有4*4的正方形，每个格子要么是黑色，要么是白色，当把一个格子的颜色改变(黑->白或者白->黑)时，其周围上下左右(如果存在的话)的格子的颜色也被反转，问至少反转几个格子可以使4*4的正方形变为纯白或者纯黑？


## 思路2：最好的思路

 - 操作顺序不影响结果
 - 每个棋子最多翻一次！

!子集枚举,神奇 🐮🍺

 - [POJ 1753 Flip Game (递归枚举)](https://www.cnblogs.com/shuaiwhu/archive/2012/04/27/2474041.html)


## 解析


把棋盘的状态用`<bitset>`保存下来,然用利用`BFS`进行查找,直到找到目标状态为止,输出答案.如果找不到,输出`Impossible`

**注意:**有可能刚开始的时候,颜色就是全部一样的.

## 代码

```c
#include <iostream>
#include <bitset>
#include <string>
#include <queue>
using namespace std;

/* 四个方向 */
int x[] = {0,1,0,-1};
int y[] = {1,0,-1,0};
int vis[1<<16] = {0};

typedef bitset<4> sta;
sta _map[4];

void init(){
    string s;
    int i,j;
    for(i=0;i<4;i++){
        cin >> s;
        for(j=0;j<4;j++)
            if( s[j] == 'b')
                s[j] = '1';
            else
                s[j] = '0';
        _map[i] = sta(s);
    }
}

unsigned long state_num( sta arr[]){
    int left = 12;
    int i;
    int ans = 0;
    for(i=0;i<4;i++){
        ans |= ((arr[i].to_ulong()) << left);
        left -=4;
    }
    return ans;
}



struct s{
    sta state[4];
    int step;

    /* 构造函数 */
    s(sta arr[],int _step){
        int i =0;
        for(i=0;i<4;i++)
            state[i] = arr[i];
        step = _step;
    }

};
queue<s> q;

bool inline in_map(int px,int py){
    if( px >= 0 && px <4  && py >=0 && py <4)
        return true;
    return false;
}
/* 进行操作,并进行判断*/
bool opt(sta arr[],int px,int py){

    int i;
    arr[px].flip(py);
    for(i = 0;i< 4;i++){
        int nx = px+x[i];
        int ny = py+y[i];
        if( in_map(nx,ny)){
            arr[nx].flip(ny); //取反
        }
    }

    return ( 
            ( arr[0].all() &&  arr[1].all() &&  arr[2].all() &&  arr[3].all()  )
                ||
            (arr[0].none() && arr[1].none() && arr[2].none() && arr[3].none())
            );
}

void bfs(){
    /* 特殊判断 */
    
    int start = state_num(_map) ;
    if( start == 0 || start == ((1<<16)-1)){
        cout << "0" <<endl;
        return ;
    }
    q.push({ _map,0});
    vis[start] = 1;

    while( !q.empty() ){

        s u = q.front(); q.pop();
    
        int i,j,k;
        for(i=0;i<4;i++)
            for(k=0;k<4;k++){
                sta bak[4];     //复制一个新的
                for (j=0;j<4;j++){
                    bak[j] = u.state[j];
                }
                bool res = opt(bak,i,k);
                if( res){
                    cout << u.step + 1<<endl;
                    return;
                }
                if( vis[state_num(bak)] == 0){
                    vis[state_num(bak)] = 1;
                    q.push({bak,u.step+1});
                }
            }
    }
    cout << "Impossible"<<endl;
}



int main(){
    init();
    bfs();
    return 0;
}



```

