/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 08月 08日 星期四 08:34:12 GMT
* problem: luogu-1081
* *----------------*/
#include <bits/stdc++.h>
using namespace std;
//#define debug
typedef long long ll;
const ll inf = 0x7f7f7f7f;
const ll maxn = 1e5+5;
ll n,X,m;
ll xi,si;

typedef pair<int,int> _city;
#define MP make_pair

struct temp {
    ll dis;
    ll h;
    ll id;
    bool operator<(const temp &b){
        if( dis < b.dis )
            return 1;
        else if ( dis == b.dis)
            return h < b.h;
        return 0;
    }
};

struct _dis{
    ll dis,id;
} ;
ll a[maxn];
_dis disa[maxn]; 
_dis disb[maxn];

struct _ans {
    double ratio;
    int h,id;

    /* 构造函数 */
    _ans(){}
    _ans(double a,ll b,ll c):ratio(a),h(b),id(c){}

    bool operator<(const _ans &b){
        if( ratio< b.ratio)
            return 1;
        else if (ratio== b.ratio&& h > b.h)
            return 1;
        return 0;
    }
};


set<_city> _set;

/* 倍增数据 */
ll f_dis[maxn][21];    //f[i][j] i 走2^j轮的距离
ll f_id[maxn][21]; // f_id[i][j] i 走2^j轮的到达的点
// f_id[i][j] = 0 表示不行

ll f_dis_a[maxn][21]; // 在2^j轮后,小A走的距离

/* 找到最接近的值,次接近的值 */
void _find(ll idx){
    auto iter = _set.find(MP(a[idx],idx));
    auto h = iter->first;
    vector<temp> tmp;
    /* 左右的4个值 */
    auto it0 = iter;
    if(iter != _set.begin() ){
        --iter;
        tmp.push_back({h-iter->first,iter->first,iter->second});
    }
    if(iter != _set.begin() ){
        --iter;
        tmp.push_back({h-iter->first,iter->first,iter->second});
    }
    if((++it0) != _set.end()){
        tmp.push_back({it0->first-h,it0->first,it0->second});

        if((++it0) != _set.end()){
            tmp.push_back({it0->first-h,it0->first,it0->second});
        }
    }
    sort(tmp.begin(),tmp.end());
    if( tmp.size() > 0){    // 小B开车
        disb[idx].dis = tmp.front().dis;
        disb[idx].id= tmp.front().id;
    }
    if( tmp.size() > 1){ // 小A开车
        disa[idx].dis = tmp[1].dis;
        disa[idx].id= tmp[1].id;
    }
}

/* 创建ST表/倍增初始化 */
void make_st(){
    int i,j;
    /* 倍增初始化 */
    for(i=1;i<=n-2;i++){
        ll a = disa[i].id;
        f_id[i][0] = disb[a].id;
        if( f_id[i][0] !=0){
            f_dis[i][0] = disa[i].dis + disb[a].dis;
            f_dis_a[i][0] = disa[i].dis;
        }
    }


    /* 创建ST表 */
    for(j=1;j<=20;j++)
        for(i=1;i<=n-2;i++){
            ll next_id = f_id[i][j-1];
            if(next_id !=0 && f_id[next_id][j-1] != 0){
                f_id[i][j] = f_id[next_id][j-1];
                f_dis[i][j] = f_dis[i][j-1] +f_dis[next_id][j-1];
                f_dis_a[i][j] = f_dis_a[i][j-1] + f_dis_a[next_id][j-1];
            }
        }
}

/* 得到 小A 小B 从城市city出发后,不超过DIS,分别走的距离 */
void get_disA_disB(int city,ll DIS,ll &dis_a,ll &dis_b){
    int i,j=20;

    ll now = city;
    ll t_x = DIS;
    ll dis_all = 0; //小A走的距离
    dis_a = 0; //小B走的距离
    while(j >= 0){
        if( f_id[now][j] !=0 &&  f_dis[now][j] <= t_x){
            t_x -= f_dis[now][j];
            dis_a += f_dis_a[now][j];
            dis_all += f_dis[now][j];
            now = f_id[now][j];
        }
        j--;
    }
    
    /* 小B走的距离 */
    dis_b = dis_all-dis_a;
    /* 再看一下 小A能走吗 */
    if( disa[now].dis > 0 && t_x >= disa[now].dis){
        dis_a += disa[now].dis;
    }
}

void init(){
    scanf("%lld",&n);
    ll i;
    for (i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    for(i=n;i>=1;i--){
        _set.insert(MP(a[i],i));
        _find(i);
    }
    scanf("%lld",&X);
    scanf("%lld",&m);
}

/* debug Function*/

/* output dis a/b */
void output_dis(_dis a[]){
    ll i;
    for (i=1;i<=n;i++){
        //printf("%lld:(dis: %lld,id: %lld )\n",i,a[i].dis,a[i].id);
        printf("%lld \n",a[i].dis);
    }
    printf("\n");
}
/* debug end */

int main(){
    init();
    ll i,j;

#ifdef debug
    output_dis(disa);
    output_dis(disb);
#endif
    
    make_st();

#ifdef debug
    /* 输出st 查看是否正确*/
    for(i=0;i<=2;i++){
        for (j=1;j<=4;j++){
            printf("f_id[%d][%d]: %d\n",j,i,f_id[j][i]);
            printf("f_dis[%d][%d]: %d\n",j,i,f_dis[j][i]);
            printf("f_dis_a[%d][%d]: %d\n",j,i,f_dis_a[j][i]);
            printf("==========================================\n");
        }
    }
#endif

    /* 计算第一个问题 */
    _ans ans_1; //存答案
    ans_1.ratio = 1<<30;
    _ans ans_2;
    for(i=1;i<=n-2;i++){// 第n-1个城市 明显小B开车的距离为0
        ll dis_a,dis_b;
        get_disA_disB(i, X, dis_a, dis_b);

        if(dis_b!=0){
            _ans ans_2(dis_a*1.0/dis_b,a[i],i);
            if(ans_2 < ans_1)
                ans_1 = ans_2;
        }
    }
    printf("%d\n",ans_1.id);


    for (i=1;i<=m;i++){
        scanf("%lld%lld",&si,&xi);
        ll dis_a,dis_b;
        get_disA_disB(si, xi, dis_a, dis_b);
        printf("%lld %lld\n",dis_a,dis_b);
    }
    return 0;
}
