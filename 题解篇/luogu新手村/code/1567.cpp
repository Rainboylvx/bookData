#include <cstdio>

int n;

int a[1000010];
int main(){
    int i,j,k;
    scanf("%d",&n);

    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }

    int max = -1; //存最大值
    int t = 1; //前面那个值 长度
    for (i=2;i<=n;i++){
        if( a[i] > a[i-1]){
            t++;
            if( t > max)
                max = t;
        }
        else
            t = 1;
    }
    printf("%d",max);

    return 0;
}
