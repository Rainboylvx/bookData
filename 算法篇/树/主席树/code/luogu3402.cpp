/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 17日 星期四 15:04:23 CST
* problem: luogu-3402
*----------------*/
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
int n,m;
const int maxn = 2e5+5;
struct Node {
    int l,r,val;
};
    //== 结点池
    int cnt = 0;
    Node tree_nodes[maxn*40*2+5];
    inline int get_node_idx(){ return ++cnt; }

int rootfa[maxn],rootdep[maxn],tot;// father,dep
/* ======= 全局变量 END =======*/


void build(int l,int r,int &now){
    now = get_node_idx();
    if( l == r){
        tree_nodes[now].val = ++tot;
        return;
    }
    int m = (l+r)>>1;
    build(l, m, tree_nodes[now].l);
    build(m+1, r, tree_nodes[now].r);
}

/* 修改操作 */
void modify(int l,int r,int ver,int &now,int pos,int val){
    now = get_node_idx();
    tree_nodes[now] = tree_nodes[ver];
    if( l == r){
        tree_nodes[now].val  =val;
        return;
    }
    int m =(l+r) >>1;
    if( pos <=m)
        modify(l, m, tree_nodes[ver].l, tree_nodes[now].l, pos, val);
    else
        modify(m+1, r, tree_nodes[ver].r, tree_nodes[now].r, pos, val);
}

int query(int l,int r,int now,int pos){
    if( l == r) return tree_nodes[now].val;
    int m = (l+r) >> 1;
    if( pos <=m)
        return query(l, m, tree_nodes[now].l, pos);
    else
        return query(m+1, r, tree_nodes[now].r, pos);
}

/* 查询 ver版本  */
int find(int ver,int x){
    int fx = query(1, n, rootfa[ver], x);
    if( fx == x)
        return x;
    return find(ver,fx);
}

/* 合并操作 */
void _merge(int ver,int x,int y){
    x = find(ver-1,x);
    y = find(ver-1,y);
    if( x == y){
        rootfa[ver] = rootfa[ver-1];
        rootdep[ver] = rootdep[ver-1];
    }
    else {
        int depx = query(1, n, rootdep[ver-1], x);
        int depy = query(1, n, rootdep[ver-1], y);
        if(depx < depy){
            modify(1, n, rootfa[ver-1], rootfa[ver], x, y);
            rootdep[ver] = rootdep[ver-1];
        }
        else if(depx > depy){
            modify(1, n, rootfa[ver-1], rootfa[ver], y, x);
            rootdep[ver] = rootdep[ver-1];
        }
        else{
            modify(1, n, rootfa[ver-1], rootfa[ver], x, y);
            modify(1, n, rootdep[ver-1], rootdep[ver], y,depy+1);
        }
    }


}


int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    scanf("%d%d",&n,&m);

    //dep数组不需要建树
    //因为只有根结点的时候认为高度为1
    build(1, n, rootfa[0]); //建树 fa
    int i;
    int opt,x,y;
    for(i=1;i<=m;i++){
        scanf("%d",&opt);
        if( opt == 1){
            scanf("%d%d",&x,&y);
            _merge(i, x, y);
        }
        else if (opt == 2){ // 回到 x 的状态
            scanf("%d",&x);
            rootfa[i] = rootfa[x];
            rootdep[i] = rootdep[x];
        }
        else { // 查询
            scanf("%d%d",&x,&y);
            rootfa[i] = rootfa[i-1];
            rootdep[i] = rootdep[i-1];
            int fx = find(i,x);
            int fy = find(i,y);
            printf("%d\n", fx == fy ? 1 : 0);
        }

    }

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
