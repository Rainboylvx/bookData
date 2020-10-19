/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 14日 星期一 17:53:55 CST
* problem:  luogu-3834
*----------------*/
#include <bits/stdc++.h> 
using namespace std;

const int maxn = 2e5+5; int n,m;

int a[maxn]; //原数组
int b[maxn]; //原数组

int root[maxn]; 
struct Node {
    int l,r,sum;
};

int cnt=0;
Node tree_node[maxn*40];
inline int get_tree_node(){
    return ++cnt;
}

namespace LSH { //离散化
    int idx=1,i;
    //使用一个数组进行离散化
    int lsh(int arr[],int len){
        for(i=2;i<=len;i++){
            if( arr[i] != arr[idx]){
                arr[++idx] = arr[i];
            }
        }
        return idx;
    }

    int get_id(int arr[],int val){
        return lower_bound(arr+1, arr+idx+1, val)-arr;
    }
}


/* 插入一个点,建立一个线段树 */
/* l,r, pre 前一个对应的点,现在这个位置对应的点,插入的值 */
void insert(int l,int r,int pre,int &now,int val){
    /* 复制 */
    now = get_tree_node();
    tree_node[now] = tree_node[pre];
    tree_node[now].sum++;
    if( l == r ) return;
     int m = (l+r)>>1;
     if( val <= m)
         insert(l, m, tree_node[pre].l, tree_node[now].l, val);
     else
         insert(m+1, r, tree_node[pre].r,tree_node[now].r,val);
}

/* 区间查询 */
/* l,r 当前结点的区间,L,R 结点的编号 */
int query(int l,int r,int L,int R,int k){
    if( l == r ) return l;
    int m = (l+r)>>1;
    // tmp 区间
    int tmp = tree_node[tree_node[R].l].sum - tree_node[tree_node[L].l].sum;
    if( k <=tmp) //在左区间
        return query(l, m, tree_node[L].l, tree_node[R].l, k);
    else
        return query(m+1, r, tree_node[L].r,tree_node[R].r,k-tmp);
}

void init(){ 
    scanf("%d%d",&n,&m);
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i] = a[i];

    }
    sort(b+1,b+n+1);
    LSH::lsh(b,n); //离散化
}

int main(){
    init();
    /* 建立树 */
    int i;
    for(i=1;i<=n;i++){
        insert(1, n, root[i-1], root[i], LSH::get_id(b,a[i]) );
    }
    for(i=1;i<=m;i++){
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        int ans = query(1,n,root[l-1],root[r],k);
        printf("%d\n",b[ans]);
    }
    return 0;
}
