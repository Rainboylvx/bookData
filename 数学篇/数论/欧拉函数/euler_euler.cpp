/* 欧拉函数 */
#include <cstdio>
const int maxn = 1e5+5;

bool flag[maxn]; //不是素数的标记
int prime[maxn]; //存素数
int phi[maxn]; // 存每一个数的欧拉值
int n;


void euler(int n){
    phi[1] = 1; // 特判
    int i,j;
    for(i=2;i<=n;++i){
        if(flag[i] == 0){ //i 是素数
            prime[++prime[0]] = i;
            phi[i] = i-1;
        }
        for(j = 1;j<=prime[0] && i*prime[j]<=n;j++){
            flag[i*prime[j]] = 1; //标记 删除
            if( i % prime[j] == 0){ //最小素因数
                //若prime[j]是i的质因子，则根据计算公式，i已经包括i*prime[j]的所有质因子 
                phi[i *prime[j]] = phi[i] * prime[j];

                //经典欧拉筛的核心语句，这样能保证每个数只会被自己最小的因子筛掉一次 
                break;
            }
            else phi[i*prime[j]]=phi[i]*phi[prime[j]];
            //利用了欧拉函数是个积性函数的性质 
        }
    }
}

int main(){
    scanf("%d",&n);
    euler(n);
    int i;
    for(i=1;i<=n;++i){
        printf("phi(%d) = %d\n",i,phi[i]);
    }
    return 0;
}
