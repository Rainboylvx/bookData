/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 17日 星期四 17:16:53 CST
* problem: luogu-1196
*----------------*/
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
int n,m;
const int maxn = 3e4+5;
int fa[maxn]; //每个点的父亲
int dep[maxn]; // 每个点到根的深度
int sum[maxn]; // 队列的数量

void init(){
    int i;
    for(i=1;i<maxn;i++){
        fa[i] = i;
        dep[i] = 0;
        sum[i] = 1;
    }
    scanf("%d",&m);
}
/* ======= 全局变量 END =======*/

/* ================= 并查集 =================*/
namespace BCJ {
    int find(int x){ //查找 and 压缩
        if( x == fa[x]) return x;
        int t = find(fa[x]);
        dep[x] += dep[fa[x]];
        fa[x] = t;
        return fa[x];
    }
    
    void merge(int x,int y){ //合并
        int fx = find(x);
        int fy = find(y);
        fa[fx] = fy;
        dep[fx] = sum[fy];
        sum[fy] += sum[fx];
    }

    int query(int x,int y){
        int fx = find(x);
        int fy = find(y);
        if( fx == fy){
            //int a =max(dep[x],dep[y]);
            return abs(dep[x]-dep[y])-1;
        }
        return -1;
        
    }
}
/* ================= 并查集 end =================*/




int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    init();
    int i;
    char opt[5]; int x,y;
    for(i=1;i<=m;i++){
        scanf("%s",opt);
        scanf("%d%d",&x,&y);
        if( opt[0] == 'M'){ //合并
            BCJ::merge(x, y);
        }
        else {
            int ans = BCJ::query(x, y);
            printf("%d\n",ans);
        }
    }

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
