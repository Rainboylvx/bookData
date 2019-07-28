#include<iostream>
#include<cmath>
using namespace std;
int main(){
    double a,b,c,x;
    scanf("%lf%lf%lf",&a,&b,&c);
    if(b*b-4*a*c>0){
        printf("x1=");
        printf("%.5f",(-b+sqrt(b*b-4*a*c))/(2*a));
        printf(";x2=");
        printf("%.5f",(-b-sqrt(b*b-4*a*c))/(2*a));
    }
    else if(b*b-4*a*c==0){
        printf("x1=x2=");
        printf("%.5f",(-b+sqrt(b*b-4*a*c))/(2*a));	
    }
    else{
        x=-b/(2*a);
        if(x==0.0){
            x= -x;
        }
        printf("x1=");
        printf("%.5f+%.5fi;",x,sqrt(4*a*c-b*b)/(2*a));
        printf("x2=");
        printf("%.5f-%.5fi",x,sqrt(4*a*c-b*b)/(2*a));	
    }
    return 0;
}
