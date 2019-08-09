/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 05月 10日 星期五 09:22:18 CST
* problem: noip2011-Day2T1
*----------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


typedef long long LL;
const int mod = 10007;

int a,b,k,n,m;
int f[10005];

void get_yang_hui(int dep){
    int i,j;
    for(i=0;i<=dep;i++){
        f[i+1] = 1;
        for(j=i;j>1;j--){
            f[j] = (f[j] + f[j-1]) % mod;
            //printf("%d ",f[j]);
        }
        //printf("\n");
    }
}

/* 求 a^n */
LL pow(LL a,LL n,LL p){
	LL base = a;
	LL ret =1;
	
	for( ;n ;n=n >> 1){
		if(n & 1)//取最低位, 是不是很像判断奇偶
			ret = ret * base % p;
		base = base*base % p;
	}

	return ret % p;
}

int main(){
    scanf("%d%d%d%d%d",&a,&b,&k,&n,&m);
    get_yang_hui(k);
    int pos = m+1;

    int x_1 = pow(a,n,mod);
    int x_2 = pow(b,m,mod);

    int ans = (( x_1 * x_2) % mod) * (f[pos] % mod ) %mod;

    printf("%d\n",ans);
    return 0;
}
