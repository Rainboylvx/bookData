#include <cstdio>

#define pi 3.14159

int main(){
    int h,r;
    scanf("%d%d",&h,&r);
    double a = pi*r*r*h/1000;
    int ans  = (int)(20 /a);
    if(20/a > ans*1.0)
        ans++;
    printf("%d\n",ans);
    return 0;
}

