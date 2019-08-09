/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 08月 05日 星期一 16:50:22 GMT
* problem:  noip2011-Day2T2
*----------------*/
#include <bits/stdc++.h>
using namespace std;

typedef  long long ll;
#define maxn 200005



ll n,m,s;
int w[maxn];
int v[maxn];
int l[maxn],r[maxn];
int _max_w = -1;


ll cnt[maxn],sum[maxn]; //前缀和

void init(){
    scanf("%lld%lld%lld",&n,&m,&s);
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%d%d",&w[i],&v[i]);
        _max_w = max(_max_w,w[i]);
    }
    for (i=1;i<=m;i++){
        scanf("%d%d",&l[i],&r[i]);
    }
}

/*  得到Y*/
ll check(int weight){
    int i,j;
    cnt[0] = sum[0] = 0;
    for (i=1;i<=n;i++){
        if( w[i] >= weight){
            cnt[i] = cnt[i-1]+1;
            sum[i] = sum[i-1] +v[i];
        }
        else {
            cnt[i] = cnt[i-1];
            sum[i] = sum[i-1];
        }
    }
    ll ans = 0;
    for (i=1;i<=m;i++){
        int l1 = l[i];
        int r1 = r[i];
        ans += (cnt[r1] -cnt[l1-1]) * (sum[r1]-sum[l1-1]);
    }
    return ans;
}

//查找第一个 <=s123
int first_le(int l,int r){
    int m;
    int ret=0;
    while( l != r  ) //表示l和r没有重合
    {
        m = (l+r) >>1; // 取中间位置
        ll ans = check(m);
        if(ans > s) 
            l = m+1;
        else {
            r = m;
        }
    }
    return l;
}
int main(){
    init();
    int ans = first_le(0,_max_w+1);
    ll y1 = abs(check(ans) - s);
    ll y2 = abs(check(ans-1)-s);
    printf("%lld\n",min(y1,y2));
    return 0;
}
