/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 08月 07日 星期三 12:39:53 GMT
* problem:  luogu-1080
*----------------*/
#include <bits/stdc++.h>
using namespace std;

#define maxn 10005

int a[maxn];
int c[maxn];
int ans[maxn];
char king_left[10005];
int len_a,len_c;

int n;
struct Node{
    int l,r,mul;
    bool operator<(Node &b){
        return mul < b.mul;
    }

};
Node p[1005];
void init(){
    scanf("%d",&n);
    scanf("%s",king_left); //读取国王的左手
    int i;
    scanf("%d",&i); // 略过国王的右手
    for (i=1;i<=n;i++){
        scanf("%d%d",&p[i].l,&p[i].r);
        p[i].mul = p[i].l * p[i].r;
    }
    sort(p+1,p+1+n);
}

/* ========== 高精度 ==========  */

const int base = 4;
const int base2 =10000;

int str2num(char x[],int y[]){
    int i,j=1,k=1;
    int lenx= strlen(x);
    for(i=lenx-1;i>=0;i--){
        if(k==base2) j++,k=1;
        y[j] += k*(x[i]-'0');
        k*=10;
    }
    return j;
}

//万进制高精乘
int mul(int a[],int len,int b,int c[]){
    int i;
    for(i=1;i<=len;i++){
        c[i] = a[i] *b;
    }

    for(i=1;i<=len;i++){
        c[i+1] += c[i] / base2;
        c[i] %= base2;
    }
    if( c[len+1] != 0)
        len++;
    return len;
}

void _div(int len,int b){
    int i,mod, x = 0;
    for(i=len;i>=1;--i){//从高位到低位
        c[i] = (x*base2+a[i]) /b;
        x = (x*base2+a[i]) % b;
    }
}

/* 高精比较 */
void compare_save_ans(int a[]){
    int i;
    bool bigger = false;
    for(i = len_a ;i >=1; --i){
        if( a[i] > ans[i]){
            bigger = true;
            break;
        }
    }
    if( bigger)
        memcpy(ans, a, sizeof(ans));
}

void print(int a[],int len){
    while( len >=1 && a[len] == 0) len--;

    printf("%d",a[len]);
    for(--len ; len >= 1 ; --len){
        printf("%04d",a[len]);
    }
}

/* ========== 高精度 END==========  */

int main(){
    init();
    len_a = str2num(king_left, a);
    int i;
    for(i=1;i<=n;i++){
        _div(len_a,p[i].r);

        //print(c,len_a);
        //printf("\n");
        compare_save_ans(c);

        memset(c,0,sizeof(c));
        len_a = mul(a,len_a,p[i].l,c);
        memcpy(a,c,sizeof(a));
    }
    print(ans, len_a);
    return 0;
}
