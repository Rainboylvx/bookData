/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 16日 星期三 23:25:25 CST
* problem:  luogu-3919
*----------------*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
/* ======= 全局变量 =======*/
int n,m;
int a[maxn];
int root[maxn];

void init(){
    scanf("%d%d",&n,&m);
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
}
/* ======= 全局变量 END =======*/

/* ======= 持久化数组/主席树 =======*/
struct Node {
    int l,r,val;
};
Node tree_nodes[maxn*40];
int cnt = 0;
inline int get_tree_node_idx(){
    return ++cnt;
}
/* 建树 */
void build(int l,int r,int &now){
    now = get_tree_node_idx();
    if( l == r){ //叶子结点
        tree_nodes[now].val =a[l];
        return;
    }
    int m = (l+r) >>1;
    build(l , m, tree_nodes[now].l);
    build(m+1 , r, tree_nodes[now].r);
}

/* 修改 */
void modify(int l,int r,int ver,int &now,int pos,int num){
    now = get_tree_node_idx();
    tree_nodes[now] = tree_nodes[ver];
    if( l == r){
        tree_nodes[now].val = num;
        return;
    }
    int m = (l+r) >>1;
    if( pos <=m )
        modify(l, m, tree_nodes[ver].l, tree_nodes[now].l, pos, num);
    else
        modify(m+1, r, tree_nodes[ver].r, tree_nodes[now].r, pos, num);
}

/* 查询 */
int query(int l,int r,int now,int pos){
    if( l == r)
        return tree_nodes[now].val;
    int m = (l+r) >>1;
    if( pos <=m)
        return query(l, m, tree_nodes[now].l, pos);
    else
        return query(m+1, r, tree_nodes[now].r, pos);
}
/* ======= 持久化数组/主席树 END =======*/


int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    init();
    build(1, n, root[0]);
    int i,ver,opt,pos,val;
    for(i=1;i<=m;i++){
        scanf("%d%d",&ver,&opt);
        if( opt == 1){
            scanf("%d%d",&pos,&val);
            modify(1, n, root[ver], root[i], pos, val);
        }
        else{
            scanf("%d",&pos);
            int ans = query(1, n, root[ver], pos);
            printf("%d\n",ans);
            root[i] = root[ver];
        }
    }

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
