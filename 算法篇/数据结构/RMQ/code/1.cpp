/* author: Rainboy email: rainboylvx@qq.com  time: 2020年 12月 04日 星期五 23:07:24 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */
int a[maxn];

template<typename T,int N = maxn,typename Comp = greater<T>> //long long or int
struct Rmq {
    T f[N][50]; //f[i][j] --> i+2^j-1
    int logn[N] = {0,0,1};
    Comp comp;
    Rmq(){ memset(f,0,sizeof(f)); }
    

    inline T good(const T &a,const T &b) {
        return comp(a,b) ? a : b;
    }
    void init(int n){ //得到f[i][j]
        for(int i=3;i<=n;++i) logn[i] = logn[i/2] +1;
        for(int j=1; (1<<j) <= n ;j++)
            for(int i=1; i+(1<<j)-1 <=n;i++) //i+(1<<j)-1<=n 表示所求的范围的最后一个值在原数组范围内
                f[i][j] = good(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    }

    T query(int l,int r){ //查询区间最值
        int k = logn[r-l+1];
        return good(f[l][k],f[r-(1<<k)+1][k]);
    }
};
Rmq<int> rmq;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d",&rmq.f[i][0]);
    }
    rmq.init(n);
    for(int i=1;i<=m;++i){
        int l,r;
        scanf("%d%d",&l,&r);
        int ans = rmq.query(l, r);
        printf("%d\n",ans);
    }
    return 0;
}
