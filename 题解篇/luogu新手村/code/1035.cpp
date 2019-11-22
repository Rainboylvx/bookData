#include <cstdio>              

int main(){
    double sn =0;

    double k ;
    scanf("%lf",&k);
    int n;
    for(n=1; true ; n++){
        sn  =  sn + 1.0/ n;

        if( sn > k){
            printf("%d",n);
            break;
        }

    }

    return 0;
}
