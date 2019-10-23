/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 23日 星期三 15:17:14 CST
* problem: poj-2889
*----------------*/
#include <cstdio>
#include <cstring>

using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 130;
int n,m;
int __SET__NOW[maxn][maxn]={0}; //集合
int __SET__MAY[maxn][maxn]={0}; //集合
int __SET__USED[maxn][maxn]={0}; //集合
int g[maxn][maxn] = {0}; // 邻接表
/* ======= 全局变量 END =======*/

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


int max_clique_cnt = 0;
bool dfs(int dep){
    if( !set_opt::count(__SET__MAY[dep])  &&  !set_opt::count(__SET__USED[dep])){
        ++max_clique_cnt;
        if( max_clique_cnt > 1000)
            return 1;
        return 0;

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
        if( dfs(dep+1))
            return 1;
        __SET__MAY[dep][i] = 0; //剔除这个点
        set_opt::push(__SET__USED[dep], v);
    }
    return 0;
}


void init(){
     int i,u,v;
     max_clique_cnt = 0;
     memset(g,0,sizeof(g));
     memset(__SET__USED,0,sizeof(__SET__USED));
     memset(__SET__MAY,0,sizeof(__SET__MAY));
     memset(__SET__NOW,0,sizeof(__SET__NOW));
     for(i=1;i<=n;i++){
         set_opt::push(__SET__MAY[1],i);
     }

     for(i=1;i<=m;i++){
         scanf("%d%d",&u,&v);
         g[u][v] = g[v][u] = 1;
     }
}

int main(){
    //===================
    while( ~scanf("%d%d",&n,&m)){
        init();
        bool flag = dfs(1);
        if (flag) 
            printf("Too many maximal sets of friends.\n");
        else
            printf("%d\n",max_clique_cnt);
    }


    //=================== 
    return 0;
}
