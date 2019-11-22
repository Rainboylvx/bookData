#include <cstdio>
#include <cmath>


int a,b;
bool isPrime(int a){
    int i,j;
    for(i=2;i<= sqrt(a)+0.5;i++){
        if( a % i == 0  )
            return 0;
    }
    return 1;
}

int num[100];

/*dep 深度  */
void dfs(int dep,int len){
    if( dep > (len+1)/2){
        int i,j;
        int sum = 0;
        int base = 1;
        for(i=1;i<=(len+1)/2;i++){
            sum += num[i]*base;
            base *= 10;
        }
        for(i=(len)/2;i>=1;i--){
            sum += num[i]*base;
            base *= 10;
        }
        if( sum >=a && sum <=b && isPrime(sum))
            printf("%d\n",sum);
        return ;
    }
    int i,j;
    int step = dep ==1 ? 2  : 1;
    int start = dep ==1 ? 1  : 0;
    for(i=start;i<=9;i+=step){
        num[dep] = i;
        dfs(dep+1,len);
    }
}

int num_len(int a){
    int cnt = 0;
    while( a ){
        cnt++;
        a /= 10;
    }
    return cnt;
}

int main(){
    scanf("%d%d",&a,&b);
    int i;
    int la = num_len(a);
    int lb = num_len(b);
    for(i=la;i<=lb;i++){
        dfs(1,i);
    }
    return 0;
}

