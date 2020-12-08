/* author: Rainboy email: rainboylvx@qq.com  time: 2020年 12月 07日 星期一 16:52:11 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

ll n,m;
vector<ll> v;

int main(){
    v.push_back(0); //占位
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=n;++i){
        ll t;
        scanf("%lld",&t);
        v.push_back(t);
    }
    for(ll i=1;i<=m;++i){
        ll o,x,y,z;
        scanf("%lld",&o);
        if( o ==1 ) {
            scanf("%lld%lld%lld",&x,&y,&z);
            for(ll i=x;i<=y;++i) v[i]+=z;
        }
        else {
            scanf("%lld",&x);
            printf("%lld\n",v[x]);
        }
    }
    return 0;
}
