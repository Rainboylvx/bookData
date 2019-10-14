#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int n,root; //点的个数,根结点
int seq_1[maxn],seq_2[maxn<<1]; //序列1,2
int dfs_clock_1 = 0 ,dfs_clock_2 = 0; // 标记值

int st[maxn],ed[maxn];  //seq_1 用
int first[maxn]; // 每个点第一次的seq_2中出现的位置
int dep[maxn],fa[maxn];

/* ================= 向量星 =================*/
int head[maxn];
int edge_cnt = 0;
struct _e{
    int u,v,w,next;
}e[maxn<<1];

void inline xlx_init(){
    edge_cnt = 0;
    memset(head,-1,sizeof(head));
}

void addEdge(int u,int v,int w){
    edge_cnt++;
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].w=w;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

/* 函数重载 */
void addEdge(int u,int v){
    edge_cnt++;
    e[edge_cnt].u = u;
    e[edge_cnt].v= v;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}
/* ================= 向量星 end =================*/

void init(){
    xlx_init();
    scanf("%d",&n);
    scanf("%d",&root);
    int i,t1,t2;
    for(i=1;i<n;i++){
        scanf("%d%d",&t1,&t2);
        addEdge(t1,t2);
        addEdge(t2,t1);
    }
}

void dfs(int d,int u,int pre){
    int i;
    dfs_clock_1++;  //计数时钟 1
    dfs_clock_2++;  //计数时钟 2

    dep[u] = d;     //深度
    fa[u] = pre;    //父亲

    st[u] = dfs_clock_1;    //点的start
    seq_1[dfs_clock_1] = u; //序列1, 具体题目中,可以不用生成

    seq_2[dfs_clock_2]  =u; //序列2
    first[u] = dfs_clock_2; //序列2 中点u的第一次出现的位置

    for(i= head[u]; ~i ;i= e[i].next){
        int &v = e[i].v;
        if( v != pre){
            dfs(d+1,v,u);
            seq_2[++dfs_clock_2] = u; //又回到点u,添加到seq_2中
        }
    }
    ed[u] = dfs_clock_1; //点的end
}

void print_array(int array[],int len,const char name[]){
    int i;
    printf("%8s: ",name);
    for(i=1;i<=len;i++){
        printf("%2d ",array==NULL ? i:array[i]);
    }
    printf("\n");
}


int main(){
    init();
    dfs(1,root,root);
    int i;
    printf("============ seq_1 info ============\n");
    print_array(seq_1, dfs_clock_1 , "seq_2");
    print_array(st, dfs_clock_1 , "start");
    print_array(ed, dfs_clock_1 , "end");
    printf("============ seq_2 info ============\n");
    print_array(seq_2, dfs_clock_2 , "seq_2");
    print_array(NULL, n, "idx");
    print_array(first, n, "first");
    print_array(dep, n, "dep");
    return 0;
}
