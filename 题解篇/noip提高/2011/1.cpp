#include <cstdio>

//const int N = 100001;
#define N 100001
int n;
int a[N],b[N],g[N],k[N];

int main(){
    scanf("%d",&n);
    int q1,q2;
    int i,j;
    
    for (i=1;i<=n;i++){
        scanf("%d%d%d%d",&a[i],&b[i],&g[i],&k[i]);
    }
    scanf("%d%d",&q1,&q2);

    for (i=n;i>=1;i--){ //从后向前查找
        if ( q1 >= a[i] && q2>=b[i] && (a[i]+g[i]) >= q1 && (b[i] + k[i]) >= q2){
            printf("%d",i);
            return 0;
        }
    }

    printf("-1");


    return 0;
}
