/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 12月 19日 星期日 15:06:03 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){	//构造函数
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }
    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }
    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }
    edge& operator[](int i){
        return e[i];
    }
    void sort(){
        std::sort(e,e+edge_cnt,[](edge &e1,edge& e2){ return e1.w < e2.w; });
    }
} e;

template<int size>
struct DisjointSet {
    int fa[size+5];
    DisjointSet() { 
        for(int i=0;i<=size+4;++i)
            fa[i] = i;
    }
    int find(int u){
        if( u  == fa[u]) return u;
        return fa[u] = find(fa[u]);
    }
    inline void un(int u,int v){
        fa[find(u)] = find(v);
    }
};

template<int size = maxn>
struct Kruskal {
    int work(linkList & e){
        e.sort();
        int ans = 0,cnt = 0;//答案，选边的数量
        for(int i =0 ;i< e.edge_cnt ;i++){ //遍历每条边
            int u =e[i].u, v =e[i].v, w =e[i].w; 
            int f1 =joinSet.find(u),f2 = joinSet.find(v);
            if( f1 != f2){ //不再同一个集合
                ans+=w;
                cnt++;
                std::cout << u <<" "<< v <<" "<< w << std::endl;
                joinSet.fa[f2] = f1;
            }
            if( cnt == n-1) break;
        }
        if( cnt < n -1) return -1; //表明不可能形成一个生成树
        return ans;
    }
    DisjointSet<size> joinSet;
} ;
Kruskal<maxn> krus;

int main(int argc,char * argv[]){
    std::cin >> n;
    std::cin >> m;
    for(int i=1;i<=m;++i){
        int u,v,w;
        std::cin >> u >> v >> w;
        e.add(u,v,w); //只要加一次
    }
    //建完图
    int ans = krus.work(e);
    std::cout << ans ;



    return 0;
}
