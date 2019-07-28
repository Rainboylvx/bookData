#include <cstdio>

int main(){
    double a,b;
    scanf("%lf%lf",&a,&b);
    double c = a / b;
    int k = (int)c;
    double r = a - k*b;
    printf("%g",r);
    return 0;
}

