#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int maxn = 1e3+5;

ll ans[maxn],v[maxn];

int maxd,kcase;

ll gcd(ll a,ll b){
    if( b == 0) return  a;
    return gcd( b , a %b);
}

ll get_first( ll a,ll b){
    return  b/a+1;
}

bool better(int d){
    int i;
    for(i=d;i>=1;i--){
        if(v[i] != ans[i])
            return ans[i] == -1 || v[i] < ans[i];
    }
    return false;
}

bool iddfs(int d,int from,ll aa,ll bb){
    if( d == maxd){
        if(bb % aa ) return false; //aa/bb必须是埃及分数
        v[d] = bb/aa; //保存分母
        if( better(d)) 
            memcpy(ans, v, sizeof(ll)*(d+1));
        return true;
    }
    bool ok = false;
    from = max( (ll)from,get_first(aa, bb));
    int i;
    for( i = from ; ; i++){
        // 估价函数，剪枝
        // 如果剩下的maxd+1-d个分数全部都是1/i，加起来仍然不超过aa/bb，则无解！ (maxd+1-d)/i <= aa/bb
        if(bb * (maxd - d + 1) <= i*aa) break;
        v[d] = i;
        //计算aa/bb - 1/i，设结果为a2/b2
        ll b2 = bb*i;
        ll a2 = aa*i - bb;
        ll g = gcd(a2,b2);
        if( iddfs(d+1, i+1, a2/g, b2/g)) ok = true;
    }
    return ok;
}

void solve(int a,int b){
    int ok = 0;
    for( maxd = 1 ; ; maxd++){
        memset(ans,-1,sizeof(ans));
        if( iddfs(0,get_first(a, b),a,b)){
            ok = 1; break;
        }
    }
    if(ok) {
        for(int i=0;i<maxd;i++) 
            printf("%lld ",ans[i]);
        printf("%lld\n",ans[maxd]);
    }
    else printf("%d/%d\n",a,b);
}

int main(){
    int a,b;
    while( scanf("%d%d",&a,&b)!=EOF){
        solve(a,b);
    }
    return 0;
}

