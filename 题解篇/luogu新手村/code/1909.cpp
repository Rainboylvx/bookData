#include <cstdio>

int main(){
    int n;
    scanf("%d",&n);
    int a,b;
    int i;
    int money = 9999999;
    for(i=1;i<=3;i++){
        scanf("%d %d",&a,&b);
        int shang = n / a;
        if( n % a != 0){
            shang++;
        }
        if( money > shang*b)
            money = shang*b;
    }
    printf("%d\n",money);
    return 0;
}

