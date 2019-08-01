/*  这个题目应该可以用DP来做 (̿▀̿ ̿Ĺ̯̿̿▀̿ ̿)̄ [] (๑•̀ㅂ•́)و✧
 * */
#include <cstdio>
int n,MM;
int _max=0;
int max_yue = 0;
int a[1000005];
#define inf 0x7f7f7f7f


/* 在cost 话费下可以连续多少个月 */
int check(int cost){
    int i,cnt = 0,sum = 0;
    for(i=1;i<=n;i++){
        if( sum + a[i] > cost){
            cnt++;
            sum = a[i];
        }
        else
            sum += a[i];
    }
    cnt++;
    return cnt;
}

void init(){
    scanf("%d%d",&n,&MM);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
        _max += a[i];
        if( max_yue < a[i])
            max_yue = a[i];
    }
    a[n+1]  =inf;
}

//查找范围是[l,r), a[r] 永远 > key
template <typename T>
int first_g(T key,T a[],int l,int r){
    int m;
    while( l != r  ) //表示l和r没有重合
    {
        m = (l+r) >>1; // 取中间位置
        int cnt = check(m);
        if(cnt > MM) //表示 [m+1,r) 满足条件
            l = m+1;
        else
            r = m;
    }
    return l;
}

int main(){
    init();
    int ans = first_g(0, a, max_yue, _max);
    printf("%d\n",ans);

    return 0;
}
