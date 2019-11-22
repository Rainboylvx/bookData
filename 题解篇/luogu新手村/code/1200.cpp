#include <cstdio>
#include <cstring>


char a[100];
char b[100];

int main(){
    //freopen("ride.in","r",stdin);
    //freopen("ride.out","w",stdout);

    scanf("%s",a);
    scanf("%s",b);

    int len = strlen(a);
    int i,j;
    int sum =1;
    int xa,xb;
    for (i=0;i<len;i++){
        sum *= a[i]-'A'+1;
    }
    xa = sum % 47;

    len = strlen(b);
    sum =1;
    for (i=0;i<len;i++){
        sum *= b[i]-'A'+1;
    }
    xb = sum % 47;

    if(xa == xb)
        printf("GO");
    else
        printf("STAY");

    return 0;
}
