/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 12月 12日 星期日 15:19:44 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){	//构造函数
        edge_cnt=0;
        memset(h,-1,sizeof(h));
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
} e;

template<int N>
struct Kahn {
    int indgree[N]; //存点的入度的
    int seq[N]; //排序好的序列
    int idx=0; //下标
    stack<int> sta;

    /**
     * n : 最大的那个点的编号
     * 最小点的编号默认是1
     */
    void work(int n,linkList& e){
        for(int i=1;i<=n;i++)
            if( indgree[i] == 0) 
                sta.push(i);
        while ( !sta.empty()) {
            int u = sta.top();
            seq[++idx] = u; //排序
            sta.pop();
            for(int i = e.h[u]; i!=-1;i = e[i].next){
                int v = e[i].v;
                if( --indgree[v] == 0)
                    sta.push(v);
            }
        }
    }
};
Kahn<100> kahn;

int main(int argc,char * argv[]){
    std::cin >> n >> m;
    for(int i=1;i<=m;++i){
        int u,v;
        std::cin >> u >> v;
        e.add(u, v);
        kahn.indgree[v]++;
    }
    kahn.work(n,e);
    for(int i=1;i<=n;++i){
        std::cout << kahn.seq[i] << " " ;
    }

    return 0;
}
