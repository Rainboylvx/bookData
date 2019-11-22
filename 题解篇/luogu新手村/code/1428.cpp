#include <cstdio>

int n;
int a[105];
int main(){
    scanf("%d",&n);
    int i,j;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    
    for(i=1;i<=n;i++){
        int cnt = 0;
        for(j=1;j<i;j++){
            if( a[j]  < a[i])
                cnt++;
        }
        printf("%d ",cnt);
    }
    return 0;
}
