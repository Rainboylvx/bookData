#include <cstdio>
int m,n,r,s;
int a[105][105];
int b[105][105];
int _abs(int n){
    if( n < 0)
        n = -n;
    return n;
}

int calc(int x,int y){
    int sum = 0;
    int i,j;
    for (i=1;i<=r;i++){
        for (j=1;j<=s;j++){
            int t= b[i][j]- a[x+i-1][y+j-1];
            sum += _abs(t);
        }
    }
    return sum;
}


void init(){
    int i,j;
    scanf("%d%d",&m,&n);
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    scanf("%d%d",&r,&s);
    for (i=1;i<=r;i++){
        for (j=1;j<=s;j++){
            scanf("%d",&b[i][j]);
        }
    }
}
int main(){
    init();
    int i,j;
    int x,y,_min = 999999;
    for(i=1;i<=m-r+1;i++)
        for (j=1;j<=n-s+1;j++){
            int ans = calc(i,j);
            if( _min > ans){
                _min = ans;
                x = i;
                y = j;
            }
        }
    for(i=x;i<=x+r-1;i++){
        for (j=y;j<=y+s-1;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
