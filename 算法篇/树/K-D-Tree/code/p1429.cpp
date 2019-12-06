/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 12月 05日 星期四 09:38:24 CST
* problem:  luogu-1429
*----------------*/
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 2e5+5;
int n;
double ans = 2e18;
// 每个点的划分,左右孩子的结点编号
int d[maxn],lc[maxn],rc[maxn];
struct node {
    double x,y;
} v[maxn];
//子树上的点 左,右,下,上的最值
double L[maxn], R[maxn], D[maxn], U[maxn];
/* ======= 全局变量 END =======*/
//计算两个点之间的欧拉距离
double dist(int a,int b){ 
  return (v[a].x - v[b].x) * (v[a].x - v[b].x) +
         (v[a].y - v[b].y) * (v[a].y - v[b].y);
}
bool cmp1(node a, node b) { return a.x < b.x; }
bool cmp2(node a, node b) { return a.y < b.y; }

//维护 L,R,D,U
void maintain(int x) {
  L[x] = R[x] = v[x].x;
  D[x] = U[x] = v[x].y;
  if (lc[x])
    L[x] = min(L[x], L[lc[x]]), R[x] = max(R[x], R[lc[x]]),
    D[x] = min(D[x], D[lc[x]]), U[x] = max(U[x], U[lc[x]]);
  if (rc[x])
    L[x] = min(L[x], L[rc[x]]), R[x] = max(R[x], R[rc[x]]),
    D[x] = min(D[x], D[rc[x]]), U[x] = max(U[x], U[rc[x]]);
}



/* 建树 */
int build(int l,int r){
    if ( l > r) return 0;
    int mid = (l+r) >> 1;
    double avx = 0, avy = 0, vax = 0, vay = 0;  // average variance
    int i;
    for(i=l;i<=r;i++){
        avx += v[i].x;
        avy += v[i].y;
    }
    avx /= (r-l+1);
    avy /= (r-l+1);
    for(i=l;i<=r;i++){ //方差
        vax += (v[i].x - avx) * (v[i].x - avx);
        vay += (v[i].y - avy) * (v[i].y - avy);
    }
    if( vax >=vay){
        d[mid] = 1, nth_element(v + l, v + mid, v + r + 1, cmp1);
    }
    else{
        d[mid] = 2, nth_element(v + l, v + mid, v + r + 1, cmp2);
    }
    lc[mid] = build(l, mid-1);
    rc[mid] = build(mid+1, r);
    maintain(mid);
    return mid;
}

double f(int a, int b) {
  double ret = 0;
  if (L[b] > v[a].x) ret += (L[b] - v[a].x) * (L[b] - v[a].x);
  if (R[b] < v[a].x) ret += (v[a].x - R[b]) * (v[a].x - R[b]);
  if (D[b] > v[a].y) ret += (D[b] - v[a].y) * (D[b] - v[a].y);
  if (U[b] < v[a].y) ret += (v[a].y - U[b]) * (v[a].y - U[b]);
  return ret;
}

/* 查询,x在[l,r]范围内的最小距离值 */
void query(int l,int r,int x){
    if( l > r ) return ;
    int mid = (l+r) >>1;
    if( mid != x ) ans = min(ans,dist(x,mid));
    if( l == r) return;
    double distl = f(x,lc[mid]);
    double distr = f(x,rc[mid]);
    //if (distl < ans && distr < ans) {
        //if (distl < distr) {
        //query(l, mid - 1, x);
        //if (distr < ans) query(mid + 1, r, x);
        //} else {
        //query(mid + 1, r, x);
        //if (distl < ans) query(l, mid - 1, x);
        //}
    //} else {
        //if (distl < ans) query(l, mid - 1, x);
        //if (distr < ans) query(mid + 1, r, x);
    //}
    if (distl < ans) query(l, mid - 1, x);
    if (distr < ans) query(mid + 1, r, x);
}



int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    scanf("%d",&n);
    int i;
    for(i=1;i<=n;i++){
        scanf("%lf%lf",&v[i].x,&v[i].y);
    }
    build(1, n);
    for(i=1;i<=n;i++){
        query(1, n, i);
    }
    printf("%.4lf\n",sqrt(ans));

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
