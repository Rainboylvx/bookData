#include <cstdio>

#define m 110

int a[m];
bool vis[m]  =  {0};
int sum[m][m] = {0};
int n;

int main(){
    scanf("%d",&n);

    int i,j;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }

    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            if( i== j) continue;
            sum[i][j] = a[i]+a[j];
        }
    }
    int cnt= 0;

    int k;
    for(i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            for (k=j+1;k<=n;k++){

                if( a[i] == sum[j][k] && vis[i] == 0){
                    //printf("%d i=%d, %d %d %d\n",a[i],i,sum[j][k],j,k);
                    cnt++;
                    vis[i] = 1;
                    break;
                }
            }
        }
    }

    printf("%d",cnt);
    return 0;
}
