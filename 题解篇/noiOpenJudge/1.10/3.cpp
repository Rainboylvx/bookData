#include <cstdio>
#include <cstring>

char name[50][200];
int n;
struct _stu {
    int n_idx;
    int fen;
};
_stu stu[50];

void xchg( _stu &a,_stu &b){
    _stu t = a;
    a = b;
    b = t;
}

void init(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%s%d",name[i],&stu[i].fen);
        stu[i].n_idx = i;
    }
}

void bubble_sort(){
    int i,j;
    for (i=1;i<=n-1;i++){
        for (j=1;j<=n-i;j++){
            
            if( stu[j].fen > stu[j+1].fen){
                xchg(stu[j],stu[j+1]);
            }
            else if ( stu[j].fen == stu[j+1].fen ){
                int x = stu[j].n_idx;
                int y = stu[j+1].n_idx;
                if( strcmp(name[x],name[y]) <0)
                    xchg(stu[j],stu[j+1]);
            }
        }
    }
}

int main(){
    init();
    bubble_sort();
    int i;
    for (i=n;i>=1;i--){
        int x = stu[i].n_idx;
        printf("%s %d\n",name[x],stu[i].fen);
    }
    return 0;

}
