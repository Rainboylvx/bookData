#include <cstdio>


int main(){
    int n,k;
    scanf("%d%d",&n,&k);

    int i;
    int ans = 0;
    for(i=1;i<=n;i++){

        int  t= i;
        while(t != 0){
            int g = t %10;
            t = t /10;
            if( g == k){
                ans++;
            }
        }
    }


    printf("%d",ans);

    return 0;
}
