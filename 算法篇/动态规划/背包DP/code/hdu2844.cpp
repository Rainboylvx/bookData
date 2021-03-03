/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 03月 03日 星期三 10:36:59 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;

int f[maxn]; // f[v] 在容量v的条件能否达到
int w[maxn],c[maxn]; //金额 数量
int cut_w[maxn]; //分出来的物品,的重量

void _01_pack(int v){ // v是消耗
    for(int i=m;i>=v;--i){
        if( f[i-v] == 1) f[i] = 1;
    }
}

void full_pack(int v){ // v是消耗
    for(int i=v;i<=m;++i) {
        if( f[i-v] == 1) f[i] = 1;
    }
}

int cut(int w,int c){
    int cnt = 0;
    for(int i =1; i<= c ;i<<=1){
        cut_w[++cnt] = i*w;
        c -=i;
    }
    if( c!= 0) cut_w[++cnt] = c*w;
    return cnt;
}

void many_pack(){
    for(int i=1;i<=n;++i){
        if(c[i] == 1){ //当成01背包来做
            _01_pack(w[i]);
        }
        else if(m / w[i] <= c[i]){ //当成完全背包
            full_pack(w[i]);
        }
        else { //分割物品,多重背包
            int cnt = cut(w[i],c[i]);
            //每份当成01背包来做
            for(int j=1;j<=cnt;++j) _01_pack(cut_w[j]);
        }
    }
}

int main(){
    while ( 1 ) {
        scanf("%d%d",&n,&m);
        if( n==0 && m ==0 )  break;
        memset(f,0,sizeof(f));
        f[0] = 1;
        int cnt=0;
        //核心
        for(int i=1;i<=n;++i) scanf("%d",&w[i]);
        for(int i=1;i<=n;++i) scanf("%d",&c[i]);
        many_pack();
        //核心 end
        for(int i=1;i<=m;++i) cnt+=f[i];
        printf("%d\n",cnt);
    }
    return 0;
}
