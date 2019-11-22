#include <cstdio>


typedef long long ll;

ll a[200];

int main(){
    int i;
    for(i=1;i<=200;i++)
    {
        scanf("%lld",&a[i]);
        if( a[i] ==0)
            break;
    }

    for(i=i-1;i>=1;i--)
        printf("%lld ",a[i]);

    return 0;
}
