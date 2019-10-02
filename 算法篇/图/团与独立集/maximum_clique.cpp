/* 
 *  1-----2-----3
 *  |\    |    /
 *  | \   |   /
 *  |  \  |  /
 *  |   \ | /
 *  |    \|/
 *  4-----5
 *  5 7
 *  1 2
 *  1 4
 *  1 5
 *  4 5
 *  2 5
 *  2 3
 *  3 5
 * */
#include <bits/stdc++.h>
using namespace std;

int n,m;
int bstb=0; //下界
int g[100][100];

struct node {
    bitset<10> sta;
    int f,dep; // f= sta.count() + n-dep 

    friend bool operator<(const node &a,const node &b){
        return a.f < b.f;
    }

};
priority_queue<node> pq;

bool is_all_connect(bitset<10> sta,int n){
    int i;
    for(i=0;i<n;i++){
        if( sta[i]  && !g[i+1][n])
            return 0;
    }
    return 1;
}

void bfs(){

    /* 加入一个虚拟0点 */
    node v_0;
    v_0.f=n;
    v_0.dep=0;
    pq.push(v_0);

    while( !pq.empty()){
        node h = pq.top(); pq.pop(); // 取对顶
        
        /* 加入左右结点 */
        int now = h.dep +1;
        /* 选 */
        if( is_all_connect(h.sta, now)){
            bstb = std::max(bstb,(int)h.sta.count()+1);
            if( bstb == n) break;
            pq.push({ h.sta.set(now-1), h.f, h.dep+1, });
        }

        /* 不选 */
        if(h.f-1 >= bstb){
            pq.push({ h.sta, h.f-1, h.dep+1 });
        }
    }
}

void init(){
    scanf("%d%d",&n,&m);
    int i,j;
    int t1,t2;
    for (i=1;i<=m;i++){
        scanf("%d%d",&t1,&t2);
        g[t1][t2] = g[t2][t1] = 1;
    }
}

int main(){
    init();
    bfs();
    printf("%d\n",bstb);
    return 0;
}
