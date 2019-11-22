#include <cstdio>

int tree[20];
int tt;

int main(){
    int i;
    for (i=1;i<=10;i++){
        scanf("%d",&tree[i]);
    }
    scanf("%d",&tt);
    int cnt =0;
    for (i=1;i<=10;i++){
        if( 30+tt >= tree[i])
            cnt++;
    }
    printf("%d",cnt);
    return 0;
}

