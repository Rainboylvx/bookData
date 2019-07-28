#include <cstdio>
int main(){
    double a,sum = 0;
    int i,n;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%lf",&a);
        sum += a;
    }
    printf("%0.4lf",sum / n);
    return 0;
}

