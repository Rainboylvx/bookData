#include <cstdio>


int n;
const int maxn = 2e4+5;

int a[maxn];
bool flag[maxn];
#define push(x) a[++a[0]] = x

/* 筛法选素数 */

void shai(){
    int i,j;
    for(i=2;i<=maxn;i++){
        if( !flag[i]) push(i);
        for(j=i+i;j<=maxn;j+=i){
            flag[j] = 1;
        }
    }
}

int main(){
    scanf("%d",&n);
    shai();
    int i,j,k;
    for(i=1;i<=a[0];i++){
        for(j=i;j<=a[0];j++){
            for(k=j;k<=a[0];k++){
                if( a[i]+ a[j]+a[k] == n){
                    printf("%d %d %d\n",a[i],a[j],a[k]);
                    return 0;
                }

            }
        }
        
    }
    return 0;
}
