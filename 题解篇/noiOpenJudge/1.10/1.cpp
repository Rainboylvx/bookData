#include <cstdio>

int n,k;
char str[200][200];
struct _stu {
    int xh;
    double jc;
};

_stu stu[200];

void init(){
    scanf("%d%d",&n,&k);
     int i;
     for (i=1;i<=n;i++){
         scanf("%s%lf",str[i] , &stu[i].jc);
         stu[i].xh = i;
     }
}

void xchg(_stu &a,_stu &b){
    _stu t = a;
    a = b;
    b = t;
}

void bubble_sort(){
    int i,j;
    for (i=1;i<=n-1;i++){
        for (j=1;j<=n-i;j++){
            if( stu[j].jc > stu[j+1].jc){
                xchg(stu[j],stu[j+1]);
            }
        }
    }
}

int main(){
    init();
    bubble_sort();
    int p = n-k+1;
    printf("%s %g\n",str[stu[p].xh],stu[p].jc);
     //int i;
     //for (i=1;i<=n;i++){
         //printf("%g\n",stu[i].jc);
     //}

    return 0;
}
