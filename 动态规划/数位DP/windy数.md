# windy数

题目地址:[luogu P2657 windy数](https://www.luogu.org/problemnew/show/P2657)

## 解析



如何求$$[0,a]$$中的windy数的个数??

## 解法1: DP + 枚举


```c
/*-------------------------------------------------
*  windy 数
*  Author:Rainboy
*  2018-07-08 08:52
*-------------------------------------------------*/
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;


int a,b;

int f[12][10] = {0};
int str[100];
int cnt; //拆解出来的数字有多少位

//拆数字成 str
void div(int n){
    cnt = 1; //最低位 为 1
    if( n == 0) str[cnt] =0,cnt++; //当这个数字就是0的时候
    while( n > 0){
        str[cnt++] = n % 10;
        n = n / 10;
    }
}

void init(){

    int i,j,k;

    //边界
    for(i=0;i<=9;i++) f[1][i] = 1; 

    //位数
    for(i=2;i<=11;i++)
        for(j=0;j<=9;j++)//第i位选的数字
            for(k=0;k<=9;k++) //第i-1位选的数字
                if( abs(j-k) >=2)
                    f[i][j] += f[i-1][k];

}


// 计算[0,n] 之间有多少windy数
int calc(int n){
    div(n); // 拆分

    int i,j,k,res = 0;

    //所有位数 小于 n 方案数
    for(i=1;i<cnt-1;i++) 
        for(j=1;j<=9;j++)
            res += f[i][j];

    //位数 等于 n, 但小于n的方案数
    for(i=1;i<str[cnt-1];i++)
        res+= f[cnt-1][i];

    //高位相等的 方案数
    for(i=cnt-2;i>=1;i--) //从倒数第2位开始
    {
        for(j=0;j<str[i];j++)
            if( abs(j-str[i+1]) >=2 )
                res += f[i][j];

        if( abs(str[i] - str[i+1]) < 2) //不能达到 str[i]
            break;
        if( i== 1)
            res+=1;
    }

    //if(i==0) 放在这里是错的 想一想为什么
        //res+=1;
    return res;

}

int main(){
    init();
    scanf("%d%d",&a,&b);
    int ans;
    ans = calc(b) - calc(a-1);
    printf("%d\n",ans);
    return 0;
}

