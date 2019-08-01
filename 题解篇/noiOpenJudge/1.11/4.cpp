#include <bits/stdc++.h>
using namespace std;

int n,m,_max_len = -1;
int a[10005];

void init(){
    scanf("%d%d",&n,&m);
    int i;
    double t;
    for (i=1;i<=n;i++){
        scanf("%lf",&t);
        a[i] = (int)( t*100);
        if( _max_len < a[i])
            _max_len = a[i];
    }
}

// <=
bool check(int num){
    int i,cnt = 0;
    for (i=1;i<=n;i++){
        cnt += a[i] / num;
    }

    if( cnt >= m)
        return 1;
    return 0;
}

//查找范围是[l,r), a[r] 永远 > key
int first_g(int l,int r){
    int m;
    while( l != r  ) //表示l和r没有重合
    {
        m = (l+r) >>1; // 取中间位置
        if(check(m)) //表示 [m+1,r) 满足条件
            l = m+1;
        else
            r = m;
    }
    return l;
}

int main(){
    init();
    int i;
    int ans = first_g(1,_max_len+1);
    printf("%.2lf\n",(ans-1)/100.0);
    return 0;
}
