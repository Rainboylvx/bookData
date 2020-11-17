#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量
int n,root;// 节点数量，根的编号

const int m = 100; //树的度，也就是节点最多有多少孩子
struct node {
    int v;        //节点本身带有的值
    int fa,ch[m]; //父亲与孩子的下标
} tree[maxe];

//遍历树
void dfs(int u,int fa){
    printf("%d ",u);
    for(int i=1;i<=tree[u].ch[0];++i){
        int v =  tree[u].ch[i];
        if( v == fa )  continue;
        dfs(v,u);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        tree[u].ch[ ++tree[u].ch[0] ]  = v; //存孩子
        tree[v].fa = u; // 存父亲
    }
    
    //显然根的父亲为0
    //找到根节点
    root = 1;
    while (tree[root].fa != 0)  root = tree[root].fa;
    dfs(root,0);

    return 0;
}
