/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 10月 09日 星期三 22:25:19 CST
* problem: hdu-1754
*----------------*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;

int a[maxn],c[maxn];
int n,m;


inline int lowbit(int x){
    return x &(-x);
}

/* pos 位置,v 数值 */
void update(int pos){
    int i,lb;
    //更新c[pos]
    c[pos] = a[pos];
    lb = lowbit(pos);
    for(i=1;i<lb;i <<=1){ //利用孩子更新自己
        c[pos] = max(c[pos],c[pos-i]);
    }

    //记录
    int pre = c[pos];
    pos+=lowbit(pos);

    /* 更新父亲 */
    while(pos <= n){
        c[pos] = max(pre,c[pos]);
        pre = c[pos];
        pos +=lowbit(pos);
    }
}

void push(int pos){
    int i,lb = lowbit(pos);
    c[pos] = a[pos];
    for(i=1;i<lb;i <<=1){
        c[pos] = max(c[pos],c[pos-i]);
    }

}
int query(int x,int y){

    int res = -1;
    while(x <= y){
        int nx = y - lowbit(y)+1;
        if(nx >= x ){
            res = res < c[y] ? c[y] :res;
            y = nx-1; // 下一个求解区间
        }
        else { // nx < x
            res = res < a[y] ? a[y] :res;
            y--;
        }
    }
    return res;
}

void init(){
    int i,t;
    for(i=1;i<=n;i++){
        scanf("%d",&t);
        a[i] = t;
        push(i);
    }

}

int main(){
    while (scanf("%d%d",&n,&m)!= EOF) {
        init();
        char tmp[3];
        int t1,t2;
        int i;
        for(i=1;i<=m;i++){
            scanf("%s",tmp);
            scanf("%d%d",&t1,&t2);
            if( tmp[0] == 'U'){
                a[t1] = t2;
                update(t1);
            }
            else {
                int ans = query(t1, t2);
                printf("%d\n",ans);
            }
        }
    }
}
