/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 08月 10日 星期六 17:46:31 GMT
* problem:  luogu-1083
*----------------*/

#include <bits/stdc++.h>
using namespace std;

#define debug
const int maxn = 1e6+5;
typedef long long ll;

int n,m;
ll a[maxn];
ll b[maxn];

struct JIE{
    int r,s,t;
}jie[maxn];


void init(){
    int i,j;
    scanf("%d%d",&n,&m);
    int t,pre;
    scanf("%d",&pre);
    a[1] = pre;
    for (i=2;i<=n;i++){
        scanf("%d",&t);
        a[i] = t-pre;
        pre = t;
    }
    for (i=1;i<=m;i++){
        scanf("%d%d%d",&jie[i].r,&jie[i].s,&jie[i].t);
    }
}

/* 到第day天是不是有 变成负数的教室 */
bool check(int day){
    int i,j;
    memcpy(b,a,sizeof(a));
    for (i=1;i<=day;i++){
        int &r = jie[i].r;
        int &s = jie[i].s;
        int &t = jie[i].t;

        b[s] -=r;
        b[t+1] +=r;
    }
    ll s = 0;
    for (i=1;i<=n;i++){
        s += b[i];
        if( s < 0 )
            return 0;
    }
    return 1;
}

#ifdef debug
void print_every_val(){
    ll s= 0,i;
    for (i=1;i<=n;i++){
        s += b[i];
        printf("%lld ",s);
    }
    printf("\n");
}
#endif


int first_g(int l,int r){
    int m;
    while( l != r  ) //表示l和r没有重合
    {
        m = (l+r) >>1; // 取中间位置
        if( check(m)) //表示 m day 成立
            l = m+1;
        else
            r = m;
    }
    return l;
}

int main(){
    init();
    
    int ans = first_g(1,m+1);
    if( ans == m+1)
        printf("0");
    else
        printf("-1\n%d\n",ans);
    return 0;
}
