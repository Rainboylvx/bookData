/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 07月 03日 星期三 10:16:16 GMT
* problem: luogu-1540
*----------------*/
#include <bits/stdc++.h>
using namespace std;

bool inq[1005];
queue<int> q;
int n,m;
int cnt = 0;

void _push(int x){
    if(inq[x]){ return; }
    q.push(x);
    cnt++;
    inq[x] = 1;
    if( q.size() > m){
        int ans = q.front();
        inq[ans] = 0;
        q.pop();
    }
}

int main(){
    scanf("%d%d",&m,&n);
    int i,t;
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        _push(t);
    }
    printf("%d\n",cnt);
    return 0;
}