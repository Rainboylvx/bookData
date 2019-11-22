#include <cstdio>

int main(){
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    int e = (c*60 +d) - (a*60 +b);

    printf("%d %d",e /60 ,e %60);
    return 0;
}
