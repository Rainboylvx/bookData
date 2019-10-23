//  version 2 
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 1e3+5;
int n,m;
int __SET__NOW[maxn][maxn]={0}; //集合
int __SET__MAY[maxn][maxn]={0}; //集合
int __SET__USED[maxn][maxn]={0}; //集合
int g[maxn][maxn] = {0}; // 邻接表



/* ================= 集合操作 =================*/
namespace set_opt {

    //集合数量
    int count(int set_name[]){ 
        return set_name[0];
    }


    //合并
    //将原来的数据复制一遍,再加入一个新的点
    void U(int src[],int dst[],int v) { 
        int cnt = count(src);
        int i;
        for(i=1;i<=cnt;i++){
            dst[i] = src[i];
        }
        dst[0] = src[0]+1;
        dst[cnt+1] = v;
    }

    void push(int src[],int v){ //加入
        src[ ++src[0] ] = v;
    }

    void V(int src[],int dst[],int v){   //交集
        int cnt = count(src);
        int i,j;
        dst[0] = 0;
        for(i=1;i<=cnt;i++){
            if( g[v][src[i]])
                dst[++dst[0]] = src[i];
        }
    }
}
/* ================= 集合操作 end =================*/
#ifdef DEBUG
void print_max_clique(int src[]){
    int i;
    for(i=1;i<=src[0];i++){
        printf("%d ",src[i]);
    }
    printf("\n");
}
#endif


int max_clique_cnt = 0;
void dfs(int dep){
    if( !set_opt::count(__SET__MAY[dep])  &&  !set_opt::count(__SET__USED[dep])){
        ++max_clique_cnt;
        #ifdef DEBUG
            print_max_clique(__SET__NOW[dep]);
        #endif
        return;
    }
    int i,j;
    int may_count = set_opt::count(__SET__MAY[dep]);
    int u = __SET__MAY[dep][1]; //支点
    for(i=1;i<=may_count;i++){
        int v = __SET__MAY[dep][i];//当前可能点 v

        //如果是邻居结点，就直接跳过下面的程序，
        //进行下一轮的循环。显然能让程序运行下去的，只有两种，
        //一种是v就是u结点本身，另一种是v不是u的邻居结点。
        if( g[u][v]) continue;
        /* 下一层的now点 */
        set_opt::U(__SET__NOW[dep],__SET__NOW[dep+1],v);
        /* 下一层的may点 */
        set_opt::V(__SET__MAY[dep],__SET__MAY[dep+1] , v);
        /* 下一层的used点 */
        set_opt::V(__SET__USED[dep], __SET__USED[dep+1], v);
        dfs(dep+1);
        __SET__MAY[dep][i] = 0; //剔除这个点
        set_opt::push(__SET__USED[dep], v);
    }
}


void init(){
     scanf("%d%d",&n,&m); //读入点,边的个数
     int i,u,v;
     for(i=1;i<=m;i++){
         scanf("%d%d",&u,&v);
         g[u][v] = g[v][u] = 1;
     }
}
/* ======= 全局变量 END =======*/


int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    init();
    int i;
    for(i=1;i<=n;i++){
        set_opt::push(__SET__MAY[1],i);
    }
    dfs(1);
    printf("%d\n",max_clique_cnt);

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
