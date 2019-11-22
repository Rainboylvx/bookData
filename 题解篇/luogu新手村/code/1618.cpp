#include <cstdio>
#include <cstring>


int a,b,c;

bool zhan[10];

void chai(int a){
    while( a){
        int g = a % 10;;
        a /= 10;
        zhan[g] = 1;
    }
}

bool all_zhan(){
    int i;
    for(i=1;i<=9;i++){
        if( !zhan[i]) return 0;
    }
    return 1;
}

int gcd(int a,int b){
    if( b == 0) return  a;
    return gcd( b , a %b);
}

bool cmp_eq(int a,int b,int c,int d){
    int g1 = gcd(a,b);
    int g2 = gcd(c,d);
    if( a / g1  == c / g2 && b / g1 == d / g2)
        return 1;
    return 0;
}

int main(){
    scanf("%d%d%d",&a,&b,&c);
    int i,j,k;
    int cnt=0;
    for(i=123;i<=987;i++){
        for(j=i+1;j<=987;j++){
            if( !cmp_eq(a,b,i,j) ) continue;
            for(k=j+1;k<=987;k++){
                if( cmp_eq(a,c,i,k) ){
                    memset(zhan,0,sizeof(zhan));
                    chai(i);chai(j);chai(k);
                    if( all_zhan() ){
                        cnt++;
                        printf("%d %d %d\n",i,j,k);
                    }
                }

            }
        }
    }
    if( !cnt){
        printf("No!!!");
    }
    return 0;
}

