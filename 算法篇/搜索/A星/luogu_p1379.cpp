#include <bits/stdc++.h>
using namespace std;

/* 目标状态 */
const char dst[] = "123804765";
int dst_int=123804765;
int dis[10][10];
int fx[][2] = { {0,-1}, {0,1}, {1,0}, {-1,0} };


set<int> vis; //close_list

bool in_map(int x,int y){
    if( x>= 0 && x <= 2 && y >=0 && y<=2)
        return 1;
    return 0;
}

struct node {
    char sta[3][3];
    int step; //  g;
    int f;

    int to_int(){
        int sum = 0;
        int i,j;
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                sum= sum*10 + (sta[i][j] - '0');
            }
        }
        return sum;
    }

    friend bool operator<(const node &a,const node &b){
        return a.step + a.f > b.step + b.f;
    }
};

/* 得到估价 */
int get_f(node &a){
    int val = 0;
    int i,j,k;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            char &c = a.sta[i][j];
            int dis_pos = find(dst,dst+9,c)-dst;
            val += dis[i*3+j][dis_pos];
        }
    }
    return val;
}

void init(){
    int i,j;
    auto calc = [](int i,int j){
        return abs( i /3 - j/3) + abs(i % 3 - j %3);
    };
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            dis[i][j] = calc(i,j);
            #ifdef DEBUG
                printf("%d ",dis[i][j]);
            #endif
        }
        #ifdef DEBUG
            printf("\n");
        #endif
    }
}

int astart(){
    node start;
    scanf("%s",start.sta);
    start.f = get_f(start);
    start.step = 0;
    priority_queue<node> q;
    q.push(start);

    while( !q.empty()){
        node h = q.top();
        q.pop();
        int h_int = h.to_int();
        if( h_int == dst_int){
            return h.step;
        }

        if( vis.find(h_int) != vis.end() )
            continue;
        vis.insert(h_int);

        int x,y;
        /* 找到 0 的位置 */
        [&h](int &x,int &y){
            int i,j;
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if( h.sta[i][j] == '0'){
                        x = i,y=j;
                        return;
                    }
                }
            }
        }(x,y);

        node tmp;

        int i;
        for(i=0;i<4;i++){
            int nx = x + fx[i][0];
            int ny = y + fx[i][1];
            if( in_map(nx,ny)){
                memcpy(tmp.sta,h.sta,sizeof(tmp.sta));
                swap(tmp.sta[x][y],tmp.sta[nx][ny]);
                tmp.step = h.step+1;
                tmp.f = get_f(tmp);
                q.push(tmp);
            }
        }
    }
    return -1;
}

int main(){
    init();
    int ans = astart();
    printf("%d\n",ans);
    return 0;
}
