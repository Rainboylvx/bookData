#include <cstdio>

int main(){
    int n;
    scanf("%d",&n);
    int i,t,sum=0;
    for(i=1;i<=n;i++){
        scanf("%d",&t);
        sum = sum + t;
    }
    double ans = sum*1.0 / n;
    printf("%0.2lf",ans);
    return 0;
}
