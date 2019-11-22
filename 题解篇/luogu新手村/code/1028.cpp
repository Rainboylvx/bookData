#include <cstdio>
#include <cstring>

int a[1010];

int main(){
    int n;
    scanf("%d",&n);
    a[1] = 1;
    int i,j,k;
    
    for (i=2;i<=n;i++){
        for (j=1;j<=(i>>1);j++){
            a[i] +=a[j];
        }
        a[i]++;
    }
    printf("%d",a[n]);
    
    return 0;
}
