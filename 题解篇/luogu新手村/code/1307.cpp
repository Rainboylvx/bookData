#include <cstdio>

int main(){
    int n;
    scanf("%d",&n);

    if( n == 0){
        printf("0");
        return 0;
    }
    else if(n <0){
        printf("-");
        n = -n;
    }

    bool flag = false;

    while( n != 0){
        
        int g = n % 10;
        n = n /10;

        if( g != 0 ){
            flag = true;
            printf("%d",g);
        }

        if( g == 0 && flag == true){
            printf("%d",g);
        }
    }
    return 0;
}
