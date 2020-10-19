#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
/* ======= 全局变量 =======*/
int n; //  点 数量
int a[maxn]; // 每个点的数值
int root; // 根结点的编号
/* ======= 全局变量 END=======*/

/* ======= 树结点与操作 =======*/
int tn_cnt = 0; // 结点编号计数
struct tree_node{ int val,l,r; } tn[maxn*10];
/* 设置对应结点的值 */
inline void tn_set(int idx,int val){
    tn[idx].val = val;
}
/* 得到结点 */
inline int get_node_idx(){ return ++tn_cnt;}

/* ======= 树结点与操作 END=======*/

/* 插入 */
void insert(int val,int &root){
    if( root == 0){
        root = get_node_idx();
        tn_set(root,val);
        return ;
    }
    int uv = tn[root].val;
    if( uv == val) return ; // 相等直接返回
    if( val > uv) // 右子树
        insert(val,tn[root].r);
    else // 左子树
        insert(val,tn[root].l);
}

int tn_find(int u,int val,int * &fa){
    if( u == 0) return 0;

    // 找到
    if( tn[u].val == val)  return u; 
    if(val > tn[u].val){ // 右子树
        fa = &tn[u].r;
        return tn_find(tn[u].r, val, fa);
    }
    else{        //左子树
        fa = &tn[u].l;
        return tn_find(tn[u].l, val, fa);
    }
}

/* 删除 */
bool del(int val){
    int *fa = &root; // 初始指向根
    int idx = tn_find(root,val,fa);

    /* 没有这个点 */
    if( idx == 0) return 0;

    if( tn[idx].l  == 0) { // 左子树为空,右子树可能不空
        *fa = tn[idx].r;
    }
    else if( tn[idx].r == 0){//右子树不空 左子树空
        *fa = tn[idx].l;
    }
    else { // 左右子树都不空
        int pre = idx ; //前驱
        int ul = tn[idx].l; // 左孩子

        while( tn[ul].r ){ // 最右点
            pre = ul;
            ul = tn[ul].r;
        }

        tn[idx].val = tn[ul].val;
        if( pre == idx)// 要删除的点的左孩子没有右子树
            tn[idx].l = tn[ul].l;
        else
            tn[pre].r = tn[ul].l;
    }
    return 1;
}

/* 中序输出 */
void middle_print(int root){
    if (root == 0)  return ; //边界
    middle_print(tn[root].l);
    printf("%d ",tn[root].val);
    middle_print(tn[root].r);
}

/* 数据读取 */
void init(){
    scanf("%d",&n);
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        insert(a[i],root); //建树
    }
}


int main(){
    init();
    /* 中序输出*/
    middle_print(root);
    printf("\n");
    del(3); //删除3
    middle_print(root);
    printf("\n");
    del(1); //删除1
    middle_print(root);
    printf("\n");
    return 0;
}
