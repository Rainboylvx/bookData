/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 11月 23日 星期六 16:16:57 CST
* problem:  luogu-5018
*----------------*/
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 1e6+5;
int n,m;
int v[maxn];
int fa[maxn];
int lson[maxn],rson[maxn];
int ans,max_ans;
int root;

void init(){
    scanf("%d",&n);
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&v[i]);
    }
    for(i=1;i<=n;i++){
        scanf("%d%d",&lson[i],&rson[i]);
        fa[ lson[i]]= fa[ rson[i]]= i;
    }
    /* 找root */
    root = 1;
    while( fa[root] != 0) root =fa[root];
}
/* ======= 全局变量 END =======*/

bool check(int l,int r){
    if( l == -1 && r == -1) return 1;
    if( l == -1 ||  r == -1) return 0;
    if( v[r] != v[l])  return 0;
    return check(lson[l],rson[r]) && check(rson[l],lson[r]);
}

int dfs(int u){
    if( u == -1) return 0;
    int size = 1;
    int ls = dfs(lson[u]);
    int rs = dfs(rson[u]);
    size += ls+rs;
    if( check(lson[u], rson[u])){
        if( size > max_ans)
            max_ans = size;
    }
    return size;
}


int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    init();
    dfs(root);
    printf("%d\n",max_ans);

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
