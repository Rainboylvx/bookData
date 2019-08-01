#include <cstdio>
#include <cmath>

int n;
int a[100005];
int first_ge(int l,int r,int key){
    while( l < r){
        int m = (l+r) >>1;
        if( a[m] < key)
            l = m+1;
        else 
            r = m;
    }
    return l;
}
int main(){
    int i;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int m,t;
    scanf("%d",&m);
    for (i=1;i<=m;i++){
        scanf("%d",&t);
        int p = first_ge(1,n+1,t);
        if( p == 1){
            printf("%d\n",a[p]);
            continue;
        }
        if( p== n+1){
            printf("%d\n",a[n]);
            continue;
        }

        int left = t - a[p-1];
        int right = a[p] -t;
        if( right < left)
            printf("%d\n",a[p]);
        else 
            printf("%d\n",a[p-1]);
    }
    return 0;
}

