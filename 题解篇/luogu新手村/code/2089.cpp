#include <cstdio>

int n;
int cnt =0 ;
void dfs1(int dep,int sum){
    if(dep > 10){
        if( sum == n) cnt++;
        return;
    }

    int i;
    for(i=1;i<=3;i++){
        dfs1(dep+1,sum+i);
    }
}
int choose[11];
void dfs2(int dep,int sum){
    if(dep > 10){
        if( sum == n) {
            int i;
            for(i=1;i<=10;i++){
                printf("%d ",choose[i]);
            }
            printf("\n");
        }
        return;
    }
    int i;
    for(i=1;i<=3;i++){
        choose[dep] = i;
        dfs2(dep+1,sum+i);
    }
}
int main(){
    scanf("%d",&n);
    dfs1(1,0);
    printf("%d\n",cnt);
    dfs2(1,0);
    return 0;
}

