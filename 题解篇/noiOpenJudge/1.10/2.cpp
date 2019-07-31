#include <cstdio>
int n;
int cnt = 0;
int a[1200] = {0};

void xchg(int &x,int &y){
    int t = x;
    x = y;
    y = t;
}

void bubble_sort(){
    int i,j;
    for (i=1;i<=cnt-1;i++){
        for (j=1;j<=cnt-i;j++){
            if( a[j] > a[j+1])
                xchg(a[j],a[j+1]);
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int i,t;
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        if( t % 2 == 1){
            cnt++;
            a[cnt] = t;
        }
    }
    bubble_sort();
    printf("%d",a[1]);
    for (i=2;i<=cnt;i++){
        printf(",%d",a[i]);
    }
    return 0;
}
