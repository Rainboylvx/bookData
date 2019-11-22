#include <cstdio>

int main(){
    int sy=0,cun=0;
    int i;
    int tmp;
    for(i=1;i<=12;i++){
        scanf("%d",&tmp);
        sy += 300;
        sy -= tmp;
        if( sy < 0){
            printf("%d",-i);
            return 0;
        }
        cun += sy /100;
        sy = sy % 100;
    }

    printf("%d",cun*120+sy);
    return 0;
}

